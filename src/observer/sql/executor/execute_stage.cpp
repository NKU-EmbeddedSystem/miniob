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
#include "sql/executor/query_checker.h"
#include "sql/executor/single_relation_select_execution_node_creator.h"
#include "storage/default/default_handler.h"
#include <cstdlib>

using namespace common;

RC create_selection_executor(Trx *trx, const Selects &selects, const char *db, const char *table_name, SelectExeNode **select_node, int &extra_count);

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

bool filter(TupleSet &res, Tuple &cur, std::vector<Condition> &conditions, const TupleSchema &schema) {
  for (int i = 0; i < conditions.size(); ++i) {
    Condition &condition = conditions[i];
    char *left_attr_name = condition.left_attr.attribute_name;
    char *right_attr_name = condition.right_attr.attribute_name;
    int left_idx = schema.index_of_field(condition.left_attr.relation_name, left_attr_name);
    int right_idx = schema.index_of_field(condition.right_attr.relation_name, right_attr_name);
    if (left_idx == -1 || right_idx == -1) {
      LOG_ERROR("attribute name mismatch\n");
      return false;
    }

    const TupleValue &left_val = cur.get(left_idx);
    const TupleValue &right_val = cur.get(right_idx);

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
      case NO_OP:
        LOG_ERROR("error operation\n");
        return false;
        break;
    }
  }

  return true;
}

void add_result(TupleSet &res, Tuple &cur, const TupleSchema &schema) {
  Tuple added;
  const auto& target_schema = res.schema();
  int j = 0;
  int i = 0;

  while (j < target_schema.fields().size() && i < schema.fields().size()) {
    auto target = target_schema.fields()[j];
    auto origin = schema.fields()[i];
    while ((strcmp(origin.field_name(), target.field_name()) != 0 || strcmp(origin.table_name(), target.table_name()) != 0)) {
      i++;
      if (i >= schema.fields().size())
        break;
      origin = schema.fields()[i];
    }
    if (i >= schema.fields().size())
      break;
    auto value = cur.values()[i];
    added.add(value);
    i++;
    j++;
  }

  res.add(std::move(added));
}

void dfs(std::vector<TupleSet> &tuple_sets, size_t index, TupleSet &res, Tuple &cur,
         std::vector<Condition> &multiple_conditions, const TupleSchema &schema) {
  if (index >= tuple_sets.size()) {
    // 递归终点
    // TODO 加一个filter, filter成功了再加进结果集
    if (filter(res, cur, multiple_conditions, schema)) {
      add_result(res, cur, schema);
      // res.add(Tuple(cur));
    }
    return;
  }
  TupleSet &tupleSet = tuple_sets[index];
  std::vector<Tuple> values = tupleSet.tuples(); // 所有行
  for (Tuple &value : values) {
    int length = value.size();
    // 一行
    // 把这一行的所有元素加进cur里面
    for (int i = 0; i < length; ++i) {
      cur.add(value.get_pointer(i));
    }
    // 递归下一层
    dfs(tuple_sets, index + 1, res, cur, multiple_conditions, schema);
    // 把这一行的所有元素删除
    for (int i = 0; i< length; ++i) {
      cur.pop_back();
    }
  }
}

#define RETURN_FAILURE \
do {                  \
  char response[] = "FAILURE\n"; \
  session_event->set_response(response); \
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

// 这里没有对输入的某些信息做合法性校验，比如查询的列名、where条件中的列名等，没有做必要的合法性校验
// 需要补充上这一部分. 校验部分也可以放在resolve，不过跟execution放一起也没有关系
RC ExecuteStage::do_select(const char *db, Query *sql, SessionEvent *session_event) {

  RC rc = RC::SUCCESS;
  Session *session = session_event->get_client()->session;
  Trx *trx = session->current_trx();
  const Selects &selects = sql->sstr.selection;

  QueryChecker query_checker(db, selects);
  rc = query_checker.check_fields();
  if (rc != RC::SUCCESS) {
    RETURN_FAILURE;
  }

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
  TupleSchema res_schema;
  TupleSchema connect_schema;
  size_t length = tuple_sets.size();
  for (int i = length - 1; i >= 0; i--) {
    auto tmp_schema = TupleSchema();
    tmp_schema.append(tuple_sets[i].schema());
    connect_schema.append(tuple_sets[i].schema());
    for (int j = 0; j < extra_counts[i]; ++j) {
      tmp_schema.pop_back();
    }
    res_schema.append(tmp_schema);
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
  TupleSet joined_tuple_set;
  if (tuple_sets.size() > 1) {
    // 本次查询了多张表，需要做join操作
    Tuple cur;
    joined_tuple_set.set_schema(res_schema);

    /*
     * 现在结果集已经筛选了一个表的条件，然后还需要手动筛选两个表的条件
     */
    dfs(tuple_sets, 0, joined_tuple_set, cur, multiple_conditions, connect_schema);

    result_tuple_set = &joined_tuple_set;
  } else {
    // 当前只查询一张表，直接返回结果即可
    result_tuple_set = &tuple_sets.front();
  }

  if (selects.agg_num > 0) {
    AggTupleSet agg_tuple_set;
    AggregationExecutor executor(selects, *result_tuple_set);

    rc = executor.execute(agg_tuple_set);
    if (rc != RC::SUCCESS) {
      ROLL_BACK_SELECT_EXE_NODES;
    }

    agg_tuple_set.print(ss);
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
  return rc;
}

/*
 * 选择两边是两个表的属性，并且类型可以匹配的条件
 */
RC create_multiple_selector(const Selects &selects, std::vector<Condition> &multiple_conditions) {
  for (size_t i = 0; i < selects.condition_num; i++) {
    const Condition &condition = selects.conditions[i];
    // 左右都是表名而且不一样
    if (condition.left_is_attr == 1 && condition.right_is_attr == 1 &&
      strcmp(condition.left_attr.relation_name, condition.right_attr.relation_name) != 0) {
      multiple_conditions.push_back(condition);
    }
  }
  return RC::SUCCESS;
}
