//
// Created by Light-Laptop on 2021/11/12.
//

#include <vector>
#include <memory>
#include <unordered_map>

#include "grouper.h"
#include "common/log/log.h"
#include "storage/default/default_handler.h"

using std::vector;
using std::shared_ptr;
using std::make_shared;
using std::unordered_map;

RC Grouper::execute(GroupByTupleSet &out_tuple_set) {
  RC rc;

  rc = init(out_tuple_set);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  Group *group;
  const auto &in_tuples = in_tuple_set_.tuples();
  for (auto itr = in_tuples.rbegin(); itr != in_tuples.rend(); itr++) {
    group = get_group_of_tuple(*itr);
    if (group == nullptr) {
      return RC::GENERIC_ERROR;
    }
    group->push_back(&(*itr));
  }

  do_aggregation(out_tuple_set);

  return RC::SUCCESS;
}

RC Grouper::init(GroupByTupleSet &out_tuple_set) {
  RC rc;

  rc = init_schema_and_indices(out_tuple_set);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  rc = manager_.create();
  if (rc != RC::SUCCESS) {
    return rc;
  }

  return RC::SUCCESS;
}

RC Grouper::init_schema_and_indices(GroupByTupleSet &out_tuple_set) {
  const char *table_name;
  AttrType field_type;
  int group_by_field_index;
  const TupleSchema &in_schema = in_tuple_set_.schema();
  GroupBySchema &out_schema = out_tuple_set.schema();

  // group by field
  for (int i = selects_.group_by_num - 1; i >= 0; i--) {
    const RelAttr &attr = selects_.group_by_attributes[i];
    table_name = attr.relation_name == nullptr
      ? selects_.relations[0]
      : attr.relation_name;
    field_type = DefaultHandler::get_default()
      .find_table(db_, table_name)->table_meta()
      .field(attr.attribute_name)->type();

    out_schema.add_if_not_exists(field_type, table_name, attr.attribute_name);

    // find index in in_tuple_set
    group_by_field_index = in_schema.index_of_field(table_name, attr.attribute_name);
    if (group_by_field_index < 0) {
      LOG_ERROR("Fail to find index in in_tuple_set of table: %s field: %s for group by: %d",
                table_name, attr.attribute_name, i);
      return RC::SCHEMA_FIELD_NOT_EXIST;
    }
    group_by_tuple_indices.push_back(group_by_field_index);
  }

  // aggregation field
  for (int i = selects_.agg_num - 1; i >= 0; i--) {
    out_schema.add(selects_.aggs[i]);
  }

  return RC::SUCCESS;
}

Grouper::Group *Grouper::get_group_of_tuple(const Tuple &tuple) {
  Map *map = &map_;

  // deal with map chain
  for (int i = 0; i < map_depth_; i++) {
    auto index = group_by_tuple_indices[i];
    auto key = const_cast<Key>(&tuple.get(index));

    if (i != map_depth_ - 1) {
      // internal map
      if (map->find(key) == map->end()) {
        return create_later_map_chain(map, i, tuple);
      }
      map = static_cast<Map *>((*map)[key].get());
    } else {
      // final group
      if (map->find(key) == map->end()) {
        (*map)[key] = std::make_shared<Group>();
      }

      return static_cast<Group *>((*map)[key].get());
    }
  }

  LOG_ERROR("Fail to get group of tuple: %p\n", &tuple);
  return nullptr;
}

Grouper::Group *Grouper::create_later_map_chain(Map *map_start, int chain_start_cnt, const Tuple &tuple) {
  Key key;
  Map *map = map_start;

  for (int i = chain_start_cnt; i < map_depth_ - 1; i++) {
    auto index = group_by_tuple_indices[i];
    key = const_cast<Key>(&tuple.get(index));

    (*map)[key] = make_shared<Map>();
    map = static_cast<Map *>((*map)[key].get());
  }

  key = const_cast<Key>(&tuple.get(group_by_tuple_indices[map_depth_ - 1]));
  (*map)[key] = make_shared<Group>();

  return static_cast<Group *>((*map)[key].get());
}

void Grouper::do_aggregation(GroupByTupleSet &out_tuple_set) {
  Tuple tuple;
  do_aggregation_helper(0, static_cast<void *>(&map_), tuple, out_tuple_set);
}

void Grouper::do_aggregation_helper(int depth, void *ptr, const Tuple &tuple, GroupByTupleSet &out_tuple_set) {
  if (depth == selects_.group_by_num) {
    manager_.reset();
    auto group = static_cast<Group *>(ptr);

    for (auto tuple_ptr : *group) {
      for (auto aggregator : manager_.aggregators()) {
        aggregator->consume(*tuple_ptr);
      }
    }

    auto result_tuple = const_cast<Tuple &>(tuple);
    for (auto aggregator : manager_.aggregators()) {
      result_tuple.add(aggregator->result());
    }

    out_tuple_set.add(std::move(result_tuple));
  } else {
    auto map = static_cast<Map *>(ptr);
    for (auto &pair : *map) {
      Tuple tuple_copy = tuple;
      tuple_copy.add(pair.first->clone());
      do_aggregation_helper(depth + 1, pair.second.get(), tuple_copy, out_tuple_set);
    }
  }
}
