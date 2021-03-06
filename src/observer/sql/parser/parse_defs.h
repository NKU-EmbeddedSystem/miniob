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
// Created by wangyunlai.wyl on 2021/6/7.
//

#ifndef __OBSERVER_SQL_PARSER_PARSE_DEFS_H__
#define __OBSERVER_SQL_PARSER_PARSE_DEFS_H__

#include <stddef.h>

#define MAX_NUM 20
#define MAX_REL_NAME 20
#define MAX_ATTR_NAME 20
#define MAX_ERROR_MESSAGE 20
#define MAX_DATA 50

//属性结构体
typedef struct {
  char *relation_name;   // relation name (may be NULL) 表名
  char *attribute_name;  // attribute name              属性名
} RelAttr;

typedef enum {
  EQUAL_TO,     //"="     0
  LESS_EQUAL,   //"<="    1
  NOT_EQUAL,    //"<>"    2
  LESS_THAN,    //"<"     3
  GREAT_EQUAL,  //">="    4
  GREAT_THAN,   //">"     5
  NO_OP,
  IS_OP,
  IS_NOT_OP,
  COND_IN,
  NOT_IN
} CompOp;

//属性值类型
typedef enum { UNDEFINED, CHARS, INTS, DATE, FLOATS, TEXTS, NULLS} AttrType;

//属性值
typedef struct _Value {
  AttrType type;  // type of value
  void *data;     // value
} Value;

typedef enum {
  COND_VALUE,
  COND_FIELD,
  COND_SUBQUERY,
} ConditionFieldType;

struct Subquery;

typedef struct _ConditionField {
  ConditionFieldType type;
  union {
    Value value;
    struct {
      RelAttr attr;
      int refers_outer;
    };
    struct Subquery * subquery;
  };
} ConditionField;

typedef struct _Condition {
  ConditionField left;
  ConditionField right;
  CompOp comp;         // comparison operator
} Condition;

typedef enum { AGG_MAX, AGG_MIN, AGG_COUNT, AGG_AVG} AggType;
typedef enum { AGG_FIELD, AGG_STAR, AGG_NUMBER} AggOperandType;

typedef struct {
  AggType agg_type;
  AggOperandType agg_operand_type;
  union {
    RelAttr agg_attr;
    int number;                  // for case like SUM(2), value is 2
  };
} AggDesc;

typedef enum { ORDER_DESC,ORDER_ASC} OrderType;

//struct of order
typedef struct {
  OrderType order_type;
  RelAttr order_attr;
}Order;

// struct of select
typedef struct {
  size_t    attr_num;               // Length of attrs in Select clause
  RelAttr   attributes[MAX_NUM];    // attrs in Select clause
  size_t    agg_num;                // number of aggregation operations
  AggDesc   aggs[MAX_NUM];          // descriptor for each aggregation operation
  size_t    relation_num;           // Length of relations in Fro clause
  char *    relations[MAX_NUM];     // relations in From clause
  size_t    condition_num;          // Length of conditions in Where clause
  Condition conditions[MAX_NUM];    // conditions in Where clause
  size_t    group_by_num;           // Length of groups
  RelAttr   group_by_attributes[MAX_NUM];   // relations in Group By
  Order  orders[MAX_NUM];  //order attrs for Order
  size_t order_num;
} Selects;

struct Subquery {
  int is_agg;
  union {
    RelAttr   attribute;    // attrs in Select clause
    AggDesc   agg;          // descriptor for each aggregation operation
  };
  int lazy;
  AttrType result_type;
  void *result;
  size_t    relation_num;           // Length of relations in Fro clause
  char *    relations[MAX_NUM];     // relations in From clause
  size_t    condition_num;          // Length of conditions in Where clause
  Condition conditions[MAX_NUM];    // conditions in Where clause
};

// struct of insert
typedef struct {
  char *relation_name;    // Relation to insert into
  size_t value_num;       // Length of values
  Value values[MAX_NUM];  // values to insert
} Inserts;

// struct of delete
typedef struct {
  char *relation_name;            // Relation to delete from
  size_t condition_num;           // Length of conditions in Where clause
  Condition conditions[MAX_NUM];  // conditions in Where clause
} Deletes;

// struct of update
typedef struct {
  char *relation_name;            // Relation to update
  char *attribute_name;           // Attribute to update
  Value value;                    // update value
  size_t condition_num;           // Length of conditions in Where clause
  Condition conditions[MAX_NUM];  // conditions in Where clause
} Updates;

typedef struct {
  char *name;     // Attribute name
  AttrType type;  // Type of attribute
  size_t length;  // Length of attribute
  int null_type; // Type of nullable
} AttrInfo;

// struct of create_table
typedef struct {
  char *relation_name;           // Relation name
  size_t attribute_count;        // Length of attribute
  AttrInfo attributes[MAX_NUM];  // attributes
} CreateTable;

// struct of drop_table
typedef struct {
  char *relation_name;  // Relation name
} DropTable;

// struct of create_index
typedef struct {
  char *index_name;      // Index name
  char *relation_name;   // Relation name
  int attr_count;
  char *attribute_name[MAX_NUM];  // Attribute name
} CreateIndex;

// struct of  drop_index
typedef struct {
  const char *index_name;  // Index name
} DropIndex;

typedef struct {
  const char *relation_name;
} DescTable;

typedef struct {
  const char *relation_name;
  const char *file_name;
} LoadData;

union Queries {
  Selects selection;
  Inserts insertion;
  Deletes deletion;
  Updates update;
  CreateTable create_table;
  DropTable drop_table;
  CreateIndex create_index;
  DropIndex drop_index;
  DescTable desc_table;
  LoadData load_data;
  char *errors;
};

// 修改yacc中相关数字编码为宏定义
enum SqlCommandFlag {
  SCF_ERROR = 0,
  SCF_SELECT,
  SCF_INSERT,
  SCF_UPDATE,
  SCF_DELETE,
  SCF_CREATE_TABLE,
  SCF_DROP_TABLE,
  SCF_CREATE_INDEX,
  SCF_CREATE_UNIQUE_INDEX,
  SCF_DROP_INDEX,
  SCF_SYNC,
  SCF_SHOW_TABLES,
  SCF_DESC_TABLE,
  SCF_BEGIN,
  SCF_COMMIT,
  SCF_ROLLBACK,
  SCF_LOAD_DATA,
  SCF_HELP,
  SCF_EXIT
};
// struct of flag and sql_struct
typedef struct Query {
  enum SqlCommandFlag flag;
  union Queries sstr;
} Query;

typedef unsigned int date_t;

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

void relation_attr_init(RelAttr *relation_attr, const char *relation_name, const char *attribute_name);
void relation_attr_destroy(RelAttr *relation_attr);

void value_init_integer(Value *value, int v);
void value_init_float(Value *value, float v);
void value_init_string(Value *value, const char *v);
void value_init_date(Value *value, date_t v);
void value_init_null(Value *value);

int value_validation(Value *value);
void value_destroy(Value *value);

ConditionField *condition_field_init_value(Value *value);
ConditionField *condition_field_init_attr(char *relation_name, char *attribute_name);
ConditionField *condition_field_init_subquery(struct Subquery *subquery);
void subquery_set_attribute(struct Subquery *subquery, RelAttr *rel_attr);
void subquery_set_agg(struct Subquery *subquery, AggDesc *agg_desc);
void subquery_append_relation(struct Subquery *subquery, const char *relation_name);
void subquery_append_condition(struct Subquery *subquery, Condition *condition);
inline int is_value(const ConditionField *condition_field) { return condition_field->type == COND_VALUE; }
inline int is_attr(const ConditionField *condition_field) { return condition_field->type == COND_FIELD; }
inline int is_subquery(const ConditionField *condition_field) { return condition_field->type == COND_SUBQUERY; }

void condition_init(Condition *condition, ConditionField *left, ConditionField *right, CompOp comp);

void condition_destroy(Condition *condition);

void attr_info_init(AttrInfo *attr_info, const char *name, AttrType type, size_t length, int null_def);
void attr_info_destroy(AttrInfo *attr_info);

void agg_desc_init_string(AggDesc *agg_desc, AggType agg_type, AggOperandType agg_operand_type, char *relation_name, char *attribute_name);
void agg_desc_init_number(AggDesc *agg_desc, AggType agg_type, AggOperandType agg_operand_type, int number);

const char *comp_op_name(CompOp comp);
const char *agg_type_name(AggType agg_type);
const char *agg_operand_name(AggOperandType operand_type);

void order_info_init(Order *order,OrderType order_type,char *relation_name, char *attribute_name);
void selects_append_orders(Selects *selects, Order *order);


void selects_init(Selects *selects, ...);
void selects_append_attribute(Selects *selects, RelAttr *rel_attr);
void selects_append_agg(Selects *selects, AggDesc *agg_desc);
void selects_append_relation(Selects *selects, const char *relation_name);
void selects_append_conditions(Selects *selects, Condition conditions[], size_t condition_num);
void selects_append_group_by_attribute(Selects *selects, RelAttr *rel_attr);
void selects_append_order(Selects *selects, Order *order);
void selects_destroy(Selects *selects);

void inserts_init(Inserts *inserts, const char *relation_name, Value values[], size_t value_num);
void inserts_destroy(Inserts *inserts);

void deletes_init_relation(Deletes *deletes, const char *relation_name);
void deletes_set_conditions(Deletes *deletes, Condition conditions[], size_t condition_num);
void deletes_destroy(Deletes *deletes);

void updates_init(Updates *updates, const char *relation_name, const char *attribute_name, Value *value,
    Condition conditions[], size_t condition_num);
void updates_destroy(Updates *updates);

void create_table_append_attribute(CreateTable *create_table, AttrInfo *attr_info);
void create_table_init_name(CreateTable *create_table, const char *relation_name);
void create_table_destroy(CreateTable *create_table);

void drop_table_init(DropTable *drop_table, const char *relation_name);
void drop_table_destroy(DropTable *drop_table);

void create_index_init(CreateIndex *create_index, const char *index_name, const char *relation_name);
void create_index_append_attribution(CreateIndex *create_index, const char *attr_name);

//void create_index_init(
//    CreateIndex *create_index, const char *index_name, const char *relation_name, const char *attr_name);

void create_index_destroy(CreateIndex *create_index);

void drop_index_init(DropIndex *drop_index, const char *index_name);
void drop_index_destroy(DropIndex *drop_index);

void desc_table_init(DescTable *desc_table, const char *relation_name);
void desc_table_destroy(DescTable *desc_table);

void load_data_init(LoadData *load_data, const char *relation_name, const char *file_name);
void load_data_destroy(LoadData *load_data);

void query_init(Query *query);
Query *query_create();  // create and init
void query_reset(Query *query);
void query_destroy(Query *query);  // reset and delete

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // __OBSERVER_SQL_PARSER_PARSE_DEFS_H__