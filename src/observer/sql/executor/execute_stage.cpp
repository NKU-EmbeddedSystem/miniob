/* Copyright (c) 2021 Xie Meiyi(xiemeiyi@hust.edu.cn) and OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Longda on 2021/4/13.
//

#include <string>
#include <algorithm>

#include "execute_stage.h"

#include "common/seda/timer_stage.h"
#include "common/lang/string.h"
#include "session/session.h"
#include "event/storage_event.h"
#include "event/sql_event.h"
#include "event/session_event.h"
#include "event/execution_plan_event.h"
#include "sql/executor/aggregation_executor.h"
#include "sql/executor/execution_node.h"
#include "sql/executor/grouper.h"
#include "sql/executor/query_checker.h"
#include "sql/executor/single_relation_select_execution_node_creator.h"
#include "storage/default/default_handler.h"
#include <cstdlib>

using namespace common;

//! Constructor
ExecuteStage::ExecuteStage(const char *tag) : Stage(tag) {}

//! Destructor
ExecuteStage::~ExecuteStage() {}

//! Parse properties, instantiate a stage object
Stage *ExecuteStage::make_stage(const std::string &tag) {
  ExecuteStage *stage = new (std::nothrow) ExecuteStage(tag.c_str());
  if (stage == nullptr) {
    LOG_ERROR("new ExecuteStage failed");
    return nullptr;
  }
  stage->set_properties();
  return stage;
}

//! Set properties for this object set in stage specific properties
bool ExecuteStage::set_properties() {
  //  std::string stageNameStr(stageName);
  //  std::map<std::string, std::string> section = theGlobalProperties()->get(
  //    stageNameStr);
  //
  //  std::map<std::string, std::string>::iterator it;
  //
  //  std::string key;

  return true;
}

//! Initialize stage params and validate outputs
bool ExecuteStage::initialize() {
  LOG_TRACE("Enter");

  std::list<Stage *>::iterator stgp = next_stage_list_.begin();
  default_storage_stage_ = *(stgp++);
  mem_storage_stage_ = *(stgp++);

  LOG_TRACE("Exit");
  return true;
}

//! Cleanup after disconnection
void ExecuteStage::cleanup() {
  LOG_TRACE("Enter");

  LOG_TRACE("Exit");
}

void ExecuteStage::handle_event(StageEvent *event) {
  LOG_TRACE("Enter\n");

  handle_request(event);

  LOG_TRACE("Exit\n");
  return;
}

void ExecuteStage::callback_event(StageEvent *event, CallbackContext *context) {
  LOG_TRACE("Enter\n");

  // here finish read all data from disk or network, but do nothing here.
  ExecutionPlanEvent *exe_event = static_cast<ExecutionPlanEvent *>(event);
  SQLStageEvent *sql_event = exe_event->sql_event();
  sql_event->done_immediate();

  LOG_TRACE("Exit\n");
  return;
}

void ExecuteStage::handle_request(common::StageEvent *event) {
  ExecutionPlanEvent *exe_event = static_cast<ExecutionPlanEvent *>(event);
  SessionEvent *session_event = exe_event->sql_event()->session_event();
  Query *sql = exe_event->sqls();
  const char *current_db = session_event->get_client()->session->get_current_db().c_str();

  CompletionCallback *cb = new (std::nothrow) CompletionCallback(this, nullptr);
  if (cb == nullptr) {
    LOG_ERROR("Failed to new callback for ExecutionPlanEvent");
    exe_event->done_immediate();
    return;
  }
  exe_event->push_callback(cb);

  switch (sql->flag) {
    case SCF_SELECT: { // select
      RC rc = do_select(current_db, sql, exe_event->sql_event()->session_event());
      if (rc == SUCCESS) {
        exe_event->done_immediate();
      }
      else {
          event->done_immediate();
      }
    }
    break;

    case SCF_INSERT:
    case SCF_UPDATE:
    case SCF_DELETE:
    case SCF_CREATE_TABLE:
    case SCF_SHOW_TABLES:
    case SCF_DESC_TABLE:
    case SCF_DROP_TABLE:
    case SCF_CREATE_INDEX:
    case SCF_CREATE_UNIQUE_INDEX:
    case SCF_DROP_INDEX: 
    case SCF_LOAD_DATA: {
      StorageEvent *storage_event = new (std::nothrow) StorageEvent(exe_event);
      if (storage_event == nullptr) {
        LOG_ERROR("Failed to new StorageEvent");
        event->done_immediate();
        return;
      }

      default_storage_stage_->handle_event(storage_event);
    }
    break;
    case SCF_SYNC: {
      RC rc = DefaultHandler::get_default().sync();
      session_event->set_response(strrc(rc));
      exe_event->done_immediate();
    }
    break;
    case SCF_BEGIN: {
      session_event->get_client()->session->set_trx_multi_operation_mode(true);
      session_event->set_response(strrc(RC::SUCCESS));
      exe_event->done_immediate();
    }
    break;
    case SCF_COMMIT: {
      Trx *trx = session_event->get_client()->session->current_trx();
      RC rc = trx->commit();
      session_event->get_client()->session->set_trx_multi_operation_mode(false);
      session_event->set_response(strrc(rc));
      exe_event->done_immediate();
    }
    break;
    case SCF_ROLLBACK: {
      Trx *trx = session_event->get_client()->session->current_trx();
      RC rc = trx->rollback();
      session_event->get_client()->session->set_trx_multi_operation_mode(false);
      session_event->set_response(strrc(rc));
      exe_event->done_immediate();
    }
    break;
    case SCF_HELP: {
      const char *response = "show tables;\n"
          "desc `table name`;\n"
          "create table `table name` (`column name` `column type`, ...);\n"
          "create index `index name` on `table` (`column`);\n"
          "insert into `table` values(`value1`,`value2`);\n"
          "update `table` set column=value [where `column`=`value`];\n"
          "delete from `table` [where `column`=`value`];\n"
          "select [ * | `columns` ] from `table`;\n";
      session_event->set_response(response);
      exe_event->done_immediate();
    }
    break;
    case SCF_EXIT: {
      // do nothing
      const char *response = "Unsupported\n";
      session_event->set_response(response);
      exe_event->done_immediate();
    }
    break;
    default: {
      exe_event->done_immediate();
      LOG_ERROR("Unsupported command=%d\n", sql->flag);
    }
  }
}

void end_trx_if_need(Session *session, Trx *trx, bool all_right) {
  if (!session->is_trx_multi_operation_mode()) {
    if (all_right) {
      trx->commit();
    } else {
      trx->rollback();
    }
  }
}

RC create_multiple_selector(const Selects &selects, std::vector<Condition> &multiple_conditions);

bool filter(Tuple &cur, std::vector<Condition> &conditions, const TupleSchema &schema) {
  for (int i = 0; i < conditions.size(); ++i) {
    Condition &condition = conditions[i];
    char *left_attr_name = condition.left.attr.attribute_name;
    char *right_attr_name = condition.right.attr.attribute_name;
    int left_idx = schema.index_of_field(condition.left.attr.relation_name, left_attr_name);
    int right_idx = schema.index_of_field(condition.right.attr.relation_name, right_attr_name);
    if (left_idx == -1 || right_idx == -1) {
      LOG_ERROR("attribute name mismatch\n");
      return false;
    }

    const TupleValue &left_val = cur.get(left_idx);
    const TupleValue &right_val = cur.get(right_idx);

    bool left_isnull = left_val.is_null();
    bool right_isnull =right_val.is_null();

    auto comp_op_ = condition.comp;
    if (comp_op_ != IS_OP && comp_op_ != IS_NOT_OP) {
      if (left_isnull || right_isnull)
        return false;
    }
    if (comp_op_ == IS_NOT_OP) {
      if (!left_isnull)
        return true;
      return false;
    }
    if (comp_op_ == IS_OP) {
      if (left_isnull)
        return true;
      return false;
    }

    int cmp_result = left_val.compare(right_val);
    switch (condition.comp) {
      case EQUAL_TO:
        if (cmp_result != 0)
          return false;
        break;
      case LESS_EQUAL:
        if (cmp_result > 0)
          return false;
        break;
      case NOT_EQUAL:
        if (cmp_result == 0)
          return false;
        break;
      case LESS_THAN:
        if (cmp_result > 0)
          return false;
        break;
      case GREAT_EQUAL:
        if (cmp_result < 0)
          return false;
        break;
      case GREAT_THAN:
        if (cmp_result <= 0)
          return false;
        break;
      default:
        LOG_ERROR("error operation\n");
        return false;
    }
  }

  return true;
}

void add_result(TupleSet &res, const Tuple &cur, const TupleSchema &schema) {
  Tuple added;
  const auto& target_schema = res.schema();
  for (int i = 0; i < target_schema.fields().size(); ++i) {
    auto target = target_schema.fields()[i];
    for (int j = 0; j < schema.fields().size(); ++j) {
      auto origin = schema.fields()[j];
      if (strcmp(origin.field_name(), target.field_name()) == 0 && strcmp(origin.table_name(), target.table_name()) == 0) {
        auto value = cur.values()[j];
        added.add(value);
        break;
      }
    }
  }

  res.add(std::move(added));
}


void format_tuple(TupleSet &res, TupleSet &cur)
{
  for (int i = 0; i < cur.size(); ++i) {
    add_result(res, cur.get(i), cur.schema());
  }
}

void connect_table(TupleSet &res, TupleSet &left, TupleSet &right, std::vector<Condition> &conditions) {
  for (int i = 0; i < left.size(); ++i) {
    for (int j = 0; j < right.size(); ++j) {
      Tuple row;
      // insert left value
      row.raw_values().insert(row.raw_values().end(), left.get(i).values().begin(), left.get(i).values().end());
      // insert right value
      row.raw_values().insert(row.raw_values().end(), right.get(j).values().begin(), right.get(j).values().end());
      if (filter(row, conditions, res.get_schema())) {
        res.add(std::move(row));
      }
    }
  }
}

/**
 * hash join两个表
 * @param res
 * @param left
 * @param right
 * @param conditions
 */
void hash_join(TupleSet &res, TupleSet &left, TupleSet &right,
               std::vector<Condition> &conditions) {
  // 设置结果集的schema
  TupleSchema schema;
  schema.append(left.schema());
  schema.append(right.schema());
  res.set_schema(schema);

  // 把条件分为等号条件和非等号条件
  std::unordered_multimap<int, size_t> hash_map;
  std::vector<Condition> join_conditions;
  for (auto & condition : conditions) {
    if (condition.comp == EQUAL_TO) {
      join_conditions.emplace_back(condition);
      break;
    }
  }

  if (join_conditions.empty()) {
    // 如果没有等号的条件，那只能连接以后再筛选了
    connect_table(res, left, right, conditions);
    return;
  }

  // 找到左右连接所在的列
  Condition &condition = join_conditions.front();
  int left_index = left.schema().index_of_field(condition.left.attr.relation_name, condition.left.attr.attribute_name);
  int right_index = right.schema().index_of_field(condition.right.attr.relation_name, condition.right.attr.attribute_name);

  // hash
  for (int i = 0; i < left.size(); ++i) {
    hash_map.insert(std::make_pair(left.get(i).get(left_index).hash(), i));
  }

  // map
  for (int i = 0; i < right.size(); ++i) {
    auto range = hash_map.equal_range(right.get(i).get(right_index).hash());
    for (auto it = range.first; it != range.second; ++it) {
      Tuple row;
      row.raw_values().insert(row.raw_values().end(), left.get(it->second).values().begin(), left.get(it->second).values().end());
      row.raw_values().insert(row.raw_values().end(), right.get(i).values().begin(), right.get(i).values().end());
      // 加个filter过滤后面的条件
      if (filter(row, conditions, res.schema()))
        res.add(std::move(row));
    }
  }
}

TupleSet* join_tables(std::vector<TupleSet> &tuple_sets, std::vector<Condition> &multiple_conditions) {
  auto *left = new TupleSet(std::move(tuple_sets[0]));
  TupleSet *right;
  auto *res = new TupleSet();
  for (int i = 1; i < tuple_sets.size(); ++i) {
    right = &tuple_sets[i];
    std::vector<Condition> left_right_conditions;
    for (auto &condition : multiple_conditions) {
      int left_exist = left->schema().index_of_field(condition.left.attr.relation_name, condition.left.attr.attribute_name);
      int right_exist = right->schema().index_of_field(condition.right.attr.relation_name, condition.right.attr.attribute_name);
      if (left_exist >=0 && right_exist >= 0) {
        left_right_conditions.emplace_back(condition);
      }
    }
    hash_join(*res, *left, *right, left_right_conditions);
    std::swap(left, res);
    res->clear();
  }
  return left;
}

void free_subquery_helper(Subquery *subquery) {
  printf("\tfree subquery\n");
  for (int i = 0; i < subquery->condition_num; i++) {
    Condition &condition = subquery->conditions[i];
    if (is_subquery(&condition.left)) {
      free_subquery_helper(condition.left.subquery);
    }
    if (is_subquery(&condition.right)) {
      free_subquery_helper(condition.right.subquery);
    }
  }
  free(subquery);
}

void free_subquery(Selects &selects) {
  for (int i = 0; i < selects.condition_num; i++) {
    Condition &condition = selects.conditions[i];
    if (is_subquery(&condition.left)) {
      free_subquery_helper(condition.left.subquery);
    }
    if (is_subquery(&condition.right)) {
      free_subquery_helper(condition.right.subquery);
    }
  }
}

#define RETURN_FAILURE \
do {                  \
  char response[] = "FAILURE\n"; \
  session_event->set_response(response); \
  free_subquery(sql->sstr.selection); \
  return rc; \
} while(0)

#define ROLL_BACK_TRX \
do {                  \
  end_trx_if_need(session, trx, false); \
  RETURN_FAILURE;                      \
} while(0)

#define ROLL_BACK_SELECT_EXE_NODES \
do {                               \
  for (SelectExeNode *& tmp_node: select_nodes) { \
    delete tmp_node; \
  }                                \
  ROLL_BACK_TRX;                                   \
} while(0)


void set_multiple_schema(TupleSchema &schema, const Selects &selects, const char *db) {
  for (int i = selects.attr_num - 1; i >= 0; --i) {
    char *table_name = selects.attributes[i].relation_name;
    char *field_name = selects.attributes[i].attribute_name;
    if (strcmp("*", field_name) == 0) {
      for (int j = selects.relation_num - 1; j >= 0; --j) {
        char *relation_name = selects.relations[j];
        Table *table = DefaultHandler::get_default().find_table(db, relation_name);
        TupleSchema tmp;
        TupleSchema::from_table(table, tmp);
        schema.append(tmp);
      }
      break;
    }
    Table *table = DefaultHandler::get_default().find_table(db, table_name);
    AttrType type = table->table_meta().field(field_name)->type();
    schema.add(type, table_name, field_name);
  }
}

/**
 * 把orders放到数组里面去
 * @param selects 查询
 * @param orders 结果数组
 */
void push_orders(const Selects &selects, std::vector<Order> &orders) {
  for (int i = 0; i < selects.order_num; ++i) {
    orders.push_back(selects.orders[i]);
  }
}

void print_subquery(const std::string &prefix, const Condition conditions[], int num) {
  for (int i = 0; i < num; i++) {
    const Condition &cond = conditions[i];
    std::cout << prefix << "left: " << cond.left.type << std::endl;
    if (is_value(&cond.left)) {
      std::cout << prefix << "[value]" << std::endl;
    } else if (is_attr(&cond.left)) {
      std::cout << prefix << "(" << ((cond.left.attr.relation_name ==
              nullptr) ? "<nil>" : cond.left.attr.relation_name) << ", " << cond.left.attr.attribute_name << ")"<< std::endl;
    } else {
      print_subquery(prefix + "\t", cond.left.subquery->conditions, cond.left.subquery->condition_num);
    }

    std::cout << prefix << "right: " << cond.right.type << std::endl;
    if (is_value(&cond.right)) {
      std::cout << prefix << "[value]" << std::endl;
    } else if (is_attr(&cond.right)) {
      std::cout << prefix << "(" << ((cond.right.attr.relation_name ==
      nullptr) ? "<nil>" : cond.right.attr.relation_name) << ", "<< cond.right.attr.attribute_name << ")" << std::endl;
    } else {
      print_subquery(prefix + "\t", cond.right.subquery->conditions, cond.right.subquery->condition_num);
    }

    std::cout << std::endl;
  }
}

// 这里没有对输入的某些信息做合法性校验，比如查询的列名、where条件中的列名等，没有做必要的合法性校验
// 需要补充上这一部分. 校验部分也可以放在resolve，不过跟execution放一起也没有关系
RC ExecuteStage::do_select(const char *db, Query *sql, SessionEvent *session_event) {

  printf("\tstart do_select\n");
  RC rc = RC::SUCCESS;
  Session *session = session_event->get_client()->session;
  Trx *trx = session->current_trx();

  const Selects &selects = sql->sstr.selection;
  print_subquery("", selects.conditions, selects.condition_num);
  QueryChecker query_checker(db, selects);
  rc = query_checker.check_fields();
  if (rc != RC::SUCCESS) {
    RETURN_FAILURE;
  }

  vector<Order> orders;
  push_orders(selects, orders);
  std::reverse(orders.begin(), orders.end());

  vector<int> extra_counts;
  vector<SelectExeNode *> select_nodes;
  SingleRelationSelectExeNodeCreator node_creator(db, selects, trx);
  rc = node_creator.create(select_nodes, extra_counts);
  if (rc != RC::SUCCESS) {
    ROLL_BACK_TRX;
  }

  if (select_nodes.empty()) {
    LOG_ERROR("No table given");
    rc = RC::SQL_SYNTAX;
    ROLL_BACK_SELECT_EXE_NODES;
  }

  std::vector<TupleSet> tuple_sets;
  for (SelectExeNode *&node: select_nodes) {
    TupleSet tuple_set;
    rc = node->execute(tuple_set);
    if (rc != RC::SUCCESS) {
      ROLL_BACK_SELECT_EXE_NODES;
    } else {
      tuple_sets.push_back(std::move(tuple_set));
    }
  }

  // 多表查询结果集schema
  TupleSchema connect_schema;
  size_t length = tuple_sets.size();
  for (int i = length - 1; i >= 0; i--) {
    connect_schema.append(tuple_sets[i].schema());
  }

  TupleSchema res_schema;
  if (tuple_sets.size() > 1) {
    if (selects.agg_num > 0) {
      res_schema = connect_schema;
    } else {
      set_multiple_schema(res_schema, selects, db);
    }
  }

  if (tuple_sets.size() == 0) {
    LOG_ERROR("no data\n");
    rc = RC::SCHEMA_FIELD_TYPE_MISMATCH;
    ROLL_BACK_SELECT_EXE_NODES;
  }

  // 反转结果集, 因为写在后面的表会先查
  std::reverse(tuple_sets.begin(), tuple_sets.end());

  // 收集多表查询条件
  std::vector<Condition> multiple_conditions;
  rc = create_multiple_selector(selects, multiple_conditions);
  if (rc != RC::SUCCESS) {
    ROLL_BACK_SELECT_EXE_NODES;
  }

  std::stringstream ss;
  TupleSet *result_tuple_set;
  TupleSet *joined_tuple_set;
  if (tuple_sets.size() > 1) {
    // 本次查询了多张表，需要做join操作
    Tuple cur;
    // 表连接
    joined_tuple_set = join_tables(tuple_sets, multiple_conditions);
    // 筛列
    result_tuple_set = new TupleSet();
    result_tuple_set->set_schema(res_schema);
    format_tuple(*result_tuple_set, *joined_tuple_set);
  } else {
    // 当前只查询一张表，直接返回结果即可
    result_tuple_set = &tuple_sets.front();
  }

  // sort
  result_tuple_set->sort_by_orders(orders);

  if (selects.agg_num > 0) {
    if (selects.group_by_num > 0) {
      GroupByTupleSet group_by_tuple_set;
      Grouper grouper(selects, *result_tuple_set, db);
      rc = grouper.execute(group_by_tuple_set);
      if (rc != RC::SUCCESS) {
        ROLL_BACK_SELECT_EXE_NODES;
      }

      group_by_tuple_set.print(ss, selects);
    } else {
      AggTupleSet agg_tuple_set;
      AggregationExecutor executor(selects, *result_tuple_set);

      rc = executor.execute(agg_tuple_set);
      if (rc != RC::SUCCESS) {
        ROLL_BACK_SELECT_EXE_NODES;
      }

      agg_tuple_set.print(ss);
    }
  } else {
    if (tuple_sets.size() > 1) {
      result_tuple_set->mprint(ss);
    } else {
      result_tuple_set->print(ss);
    }
  }

  for (SelectExeNode *& tmp_node: select_nodes) {
    delete tmp_node;
  }
  session_event->set_response(ss.str());
  end_trx_if_need(session, trx, true);
  free_subquery(sql->sstr.selection);
  return rc;
}

/*
 * 选择两边是两个表的属性，并且类型可以匹配的条件
 */
RC create_multiple_selector(const Selects &selects, std::vector<Condition> &multiple_conditions) {
  for (size_t i = 0; i < selects.condition_num; i++) {
    const Condition &condition = selects.conditions[i];
    // 左右都是表名而且不一样
    if (is_attr(&condition.left) && is_attr(&condition.right) &&
      strcmp(condition.left.attr.relation_name, condition.right.attr.relation_name) != 0) {
      multiple_conditions.push_back(condition);
    }
  }
  return RC::SUCCESS;
}
