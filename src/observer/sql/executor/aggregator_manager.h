//
// Created by Luminosity on 2021/11/13.
//

#ifndef MINIDB_AGGREGATOR_MANAGER_H
#define MINIDB_AGGREGATOR_MANAGER_H

#include <vector>

#include "rc.h"
#include "aggregator.h"

class AggregatorManager {
public:
  AggregatorManager(const Selects &selects, const TupleSet &in_tuple_set)
    : selects_(selects), in_tuple_set_(in_tuple_set)
    { }

  ~AggregatorManager();

  RC create();
  void reset();
  std::vector<Aggregator *> &aggregators() { return aggregators_; }
  static AttrType result_type(const AggDesc &agg_desc, const char *db);

private:
  Aggregator *create_from(const AggDesc &agg_desc);
  RC find_pos_of_agg_field_in_schema(const RelAttr &rel_attr, int *pos);

  const Selects &selects_;
  const TupleSet &in_tuple_set_;
  std::vector<Aggregator *> aggregators_;
};


#endif //MINIDB_AGGREGATOR_MANAGER_H
