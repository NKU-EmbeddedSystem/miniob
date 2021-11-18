//
// Created by Light-Laptop on 2021/11/17.
//

#include "subquery.h"
#include "execute_stage.h"
#include "execution_node.h"
#include "single_relation_select_execution_node_creator.h"
#include "aggregation_executor.h"

static RC evaluate_condition(Condition &condition, const char *db, Trx *trx);
static RC evaluate_subquery(Subquery *subquery, const char *db, Trx *trx);
static Selects subquery2selects(const Subquery *subquery);

RC evaluate_conditions(Condition conditions[], int condition_num, const char *db, Trx *trx) {
  RC rc;

  for (int i = 0; i < condition_num; i++) {
    printf("before evaluate condition[%d]\n", i);
    rc = evaluate_condition(conditions[i], db, trx);
    if (rc != RC::SUCCESS) {
      return rc;
    }
    printf("end evaluate condition[%d]\n", i);
  }

  return RC::SUCCESS;
}

static RC evaluate_condition(Condition &condition, const char *db, Trx *trx) {
  RC rc;

  if (is_subquery(&condition.left)) {
    printf("before evaluate left subquery\n");
    rc = evaluate_subquery(condition.left.subquery, db, trx);
    if (rc != RC::SUCCESS) {
      return rc;
    }
    printf("end evaluate left subquery\n");
  }

  if (is_subquery(&condition.right)) {
    printf("before evaluate right subquery\n");
    rc = evaluate_subquery(condition.right.subquery, db, trx);
    if (rc != RC::SUCCESS) {
      return rc;
    }
    printf("end evaluate right subquery\n");
  }

  return RC::SUCCESS;
}

#define ROLL_BACK_SELECT_EXE_NODES \
do {                               \
  for (SelectExeNode *& tmp_node: select_nodes) { \
    delete tmp_node; \
  }                                \
  return rc;                                 \
} while(0)

static RC evaluate_subquery(Subquery *subquery, const char *db, Trx *trx) {
  RC rc;

  printf("before evaluate subquery conditions\n");
  rc = evaluate_conditions(subquery->conditions, subquery->condition_num, db, trx);
  if (rc != RC::SUCCESS) {
    return rc;
  }
  printf("after evaluate subquery conditions\n");

  const Selects selects = subquery2selects(subquery);

  printf("before subquery node create\n");
  vector<int> extra_counts;
  vector<SelectExeNode *> select_nodes;
  SingleRelationSelectExeNodeCreator node_creator(db, selects, trx);
  rc = node_creator.create(select_nodes, extra_counts);
  if (rc != RC::SUCCESS) {
    return rc;
  }
  printf("after subquery node create\n");

  printf("before subquery single node execute\n");
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
  printf("after subquery single node execute\n");

  // 多表查询结果集schema
  TupleSchema connect_schema;
  size_t length = tuple_sets.size();
  for (int i = length - 1; i >= 0; i--) {
    connect_schema.append(tuple_sets[i].schema());
  }

  if (select_nodes.empty()) {
    LOG_ERROR("No table given");
    rc = RC::SQL_SYNTAX;
    ROLL_BACK_SELECT_EXE_NODES;
  }

  TupleSchema res_schema;
  if (tuple_sets.size() > 1) {
    if (selects.agg_num > 0) {
      res_schema = connect_schema;
    } else {
      set_multiple_schema(res_schema, selects, db);
      if (res_schema.fields().size() != 1) {
        LOG_ERROR("Subquery schema with column size: %d", res_schema.fields().size());
        ROLL_BACK_SELECT_EXE_NODES;
      }
    }
  }

  if (tuple_sets.size() == 0) {
    LOG_ERROR("no data\n");
    rc = RC::SCHEMA_FIELD_TYPE_MISMATCH;
    ROLL_BACK_SELECT_EXE_NODES;
  }

  // 反转结果集, 因为写在后面的表会先查
  std::reverse(tuple_sets.begin(), tuple_sets.end());

  printf("before create multiple selector\n");
  // 收集多表查询条件
  std::vector<Condition> multiple_conditions;
  rc = create_multiple_selector(selects, multiple_conditions);
  if (rc != RC::SUCCESS) {
    ROLL_BACK_SELECT_EXE_NODES;
  }

  printf("before subquery join\n");
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
  printf("after subquery join\n");

  if (selects.agg_num > 0) {
    AggTupleSet agg_tuple_set;
    AggregationExecutor executor(selects, *result_tuple_set);

    printf("before agg exe\n");
    rc = executor.execute(agg_tuple_set);
    if (rc != RC::SUCCESS) {
      ROLL_BACK_SELECT_EXE_NODES;
    }

    printf("after agg exe\n");
    printf("tuples.size = %d\n", agg_tuple_set.tuples().size());
    printf("tuples[0].size = %d\n", agg_tuple_set.tuples()[0].size());

    TupleValue *result = agg_tuple_set.tuples()[0].get(0).clone();
    printf("after agg result: %p\n", result);
    subquery->result = result;
    subquery->result_type = result->type();
  } else {
    if (result_tuple_set->schema().fields().size() != 1) {
      LOG_ERROR("After execute subquery, schema size invalid: %d", result_tuple_set->schema().fields().size());
      ROLL_BACK_SELECT_EXE_NODES;
    }
    using Set = std::unordered_set<TupleValue *, std::hash<TupleValue *>, TupleValueKeyEqualTo>;
    Set *result_set = new Set;
    for (auto &tuple : result_tuple_set->tuples()) {
      result_set->emplace(tuple.get(0).clone());
    }
    subquery->result = result_set;
    subquery->result_type = result_tuple_set->schema().field(0).type();
  }

  for (SelectExeNode *& tmp_node: select_nodes) {
    delete tmp_node;
  }
  return RC::SUCCESS;
}

static Selects subquery2selects(const Subquery *subquery) {
  Selects selects;
  memset(&selects, 0, sizeof(selects));

  if (subquery->is_agg) {
    selects.aggs[0] = subquery->agg;
    selects.agg_num = 1;
  } else {
    selects.attributes[0] = subquery->attribute;
    selects.attr_num = 1;
  }

  for (int i = 0; i < subquery->relation_num; i++) {
    selects.relations[i] = subquery->relations[i];
  }
  selects.relation_num = subquery->relation_num;

  for (int i = 0; i < subquery->condition_num; i++) {
    selects.conditions[i] = subquery->conditions[i];
  }
  selects.condition_num = subquery->condition_num;

  return selects;
}
