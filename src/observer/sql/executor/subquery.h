//
// Created by Light-Laptop on 2021/11/17.
//

#ifndef MINIDB_SUBQUERY_H
#define MINIDB_SUBQUERY_H

#include "storage/trx/trx.h"
#include "sql/parser/parse_defs.h"
#include "rc.h"

RC evaluate_conditions(Condition conditions[], int condition_num, const char *db, Trx *trx);

#endif //MINIDB_SUBQUERY_H
