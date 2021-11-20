//
// Created by Light-Laptop on 2021/11/17.
//

#ifndef MINIDB_SUBQUERY_H
#define MINIDB_SUBQUERY_H

#include <vector>
#include <utility>

#include "storage/trx/trx.h"
#include "sql/parser/parse_defs.h"
#include "sql/executor/value.h"
#include "rc.h"


extern std::vector<std::pair<RelAttr, TupleValue *>> subquery_context;

RC evaluate_conditions(Condition conditions[], int condition_num, const char *db, Trx *trx);
RC evaluate_subquery(Subquery *subquery, const char *db, Trx *trx);
void free_condition_results(Condition conditions[], int condition_num);

#endif //MINIDB_SUBQUERY_H
