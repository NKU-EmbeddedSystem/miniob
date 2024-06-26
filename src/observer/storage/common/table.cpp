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
// Created by Wangyunlai on 2021/5/13.
//

#include <limits.h>
#include <string.h>
#include <algorithm>
#include <sql/executor/execution_node.h>
#include <sql/executor/execute_stage.h>

#include "storage/common/table.h"
#include "storage/common/table_meta.h"
#include "common/log/log.h"
#include "common/lang/string.h"
#include "storage/default/disk_buffer_pool.h"
#include "storage/common/record_manager.h"
#include "storage/common/condition_filter.h"
#include "storage/common/meta_util.h"
#include "storage/common/index.h"
#include "storage/common/bplus_tree_index.h"
#include "storage/trx/trx.h"

Table::Table() : 
    data_buffer_pool_(nullptr),
    file_id_(-1),
    record_handler_(nullptr) {
}

Table::~Table() {
  delete record_handler_;
  record_handler_ = nullptr;

  if (data_buffer_pool_ != nullptr && file_id_ >= 0) {
    data_buffer_pool_->close_file(file_id_);
    data_buffer_pool_ = nullptr;
  }

  const int index_num = unique_indexes_.size();
  for (int i = index_num - 1; i >= 0; --i) {
    BplusTreeIndex* index = dynamic_cast<BplusTreeIndex *>(unique_indexes_[i]);
    if (index == nullptr) {
      LOG_ERROR("error in index index\n");
      break;
    }
    RC rc = index->sync();
    if (rc == SUCCESS)
      LOG_INFO("Successfully close index %s\n", index->index_meta().name());
    else
      LOG_ERROR("Error when closing index %s\n", index->index_meta().name());
    free(index);
  }
  unique_indexes_.clear();

  LOG_INFO("Table has been closed: %s", name());
}

RC Table::create(const char *path, const char *name, const char *base_dir, int attribute_count, const AttrInfo attributes[]) {

  if (nullptr == name || common::is_blank(name)) {
    LOG_WARN("Name cannot be empty");
    return RC::INVALID_ARGUMENT;
  }
  LOG_INFO("Begin to create table %s:%s", base_dir, name);

  if (attribute_count <= 0 || nullptr == attributes) {
    LOG_WARN("Invalid arguments. table_name=%s, attribute_count=%d, attributes=%p",
        name, attribute_count, attributes);
    return RC::INVALID_ARGUMENT;
  }

  RC rc = RC::SUCCESS;

  // 使用 table_name.table记录一个表的元数据
  // 判断表文件是否已经存在
  int fd = ::open(path, O_WRONLY | O_CREAT | O_EXCL | O_CLOEXEC, 0600);
  if (-1 == fd) {
    if (EEXIST == errno) {
      LOG_ERROR("Failed to create table file, it has been created. %s, EEXIST, %s",
                path, strerror(errno));
      return RC::SCHEMA_TABLE_EXIST;
    }
    LOG_ERROR("Create table file failed. filename=%s, errmsg=%d:%s", 
       path, errno, strerror(errno));
    return RC::IOERR;
  }

  close(fd);

  // 创建文件
  if ((rc = table_meta_.init(name, attribute_count, attributes)) != RC::SUCCESS) {
    LOG_ERROR("Failed to init table meta. name:%s, ret:%d", name, rc);
    return rc; // delete table file
  }

  std::fstream fs;
  fs.open(path, std::ios_base::out | std::ios_base::binary);
  if (!fs.is_open()) {
    LOG_ERROR("Failed to open file for write. file name=%s, errmsg=%s", path, strerror(errno));
    return RC::IOERR;
  }

  // 记录元数据到文件中
  table_meta_.serialize(fs);
  fs.close();

  std::string data_file = std::string(base_dir) + "/" + name + TABLE_DATA_SUFFIX;
  data_buffer_pool_ = theGlobalDiskBufferPool();
  rc = data_buffer_pool_->create_file(data_file.c_str());
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to create disk buffer pool of data file. file name=%s", data_file.c_str());
    return rc;
  }

  rc = init_record_handler(base_dir);

  base_dir_ = base_dir;
  LOG_INFO("Successfully create table %s:%s", base_dir, name);
  return rc;
}

RC open_index(TableMeta &table_meta_, std::vector<Index*> &indexes_, const char* base_dir, const char *name) {
  RC rc = RC::SUCCESS;
  const int index_num = table_meta_.index_num();
  for (int i = 0; i < index_num; i++) {
    const IndexMeta *index_meta = table_meta_.index(i);
    auto str_fields = index_meta->fields();
    std::vector<FieldMeta> fields;
    for (int i = 0; i < str_fields.size(); ++i) {
      const FieldMeta *field_meta = table_meta_.field(str_fields[i].c_str());
      if (field_meta == nullptr) {
        LOG_PANIC("Found invalid index meta info which has a non-exists field. table=%s, index=%s",
                  name, index_meta->name());
        return RC::GENERIC_ERROR;
      }
      fields.emplace_back(*field_meta);
    }

    BplusTreeIndex *index = new BplusTreeIndex();
    std::string index_file = index_data_file(base_dir, name, index_meta->name());
    rc = index->open(index_file.c_str(), *index_meta, fields);
    if (rc != RC::SUCCESS) {
      delete index;
      LOG_ERROR("Failed to open index. table=%s, index=%s, file=%s, rc=%d:%s",
                name, index_meta->name(), index_file.c_str(), rc, strrc(rc));
      return rc;
    }
    indexes_.push_back(index);
  }
  return RC::SUCCESS;
}

RC Table::open(const char *meta_file, const char *base_dir) {
  // 加载元数据文件
  std::fstream fs;
  std::string meta_file_path = std::string(base_dir) + "/" + meta_file;
  fs.open(meta_file_path, std::ios_base::in | std::ios_base::binary);
  if (!fs.is_open()) {
    LOG_ERROR("Failed to open meta file for read. file name=%s, errmsg=%s", meta_file, strerror(errno));
    return RC::IOERR;
  }
  if (table_meta_.deserialize(fs) < 0) {
    LOG_ERROR("Failed to deserialize table meta. file name=%s", meta_file);
    return RC::GENERIC_ERROR;
  }
  fs.close();

  // 加载数据文件
  RC rc = init_record_handler(base_dir);

  base_dir_ = base_dir;

  rc = open_index(table_meta_, indexes_, base_dir, name());
  if (rc != RC::SUCCESS)
    return rc;

  // add unique indexes
  const int unique_index_num = table_meta_.unique_index_num();
  for (int i = 0; i < unique_index_num; i++) {
    const IndexMeta *index_meta = table_meta_.unique_index(i);
    const FieldMeta *field_meta = table_meta_.field(index_meta->fields()[0].c_str());
    if (field_meta == nullptr) {
      LOG_PANIC("Found invalid index meta info which has a non-exists field. table=%s, index=%s, field=%s",
                name(), index_meta->name(), index_meta->fields()[0].c_str());
      return RC::GENERIC_ERROR;
    }

    BplusTreeIndex *index = new BplusTreeIndex();
    std::string index_file = index_data_file(base_dir, name(), index_meta->name());
    std::vector<FieldMeta> only_field;
    only_field.emplace_back(*field_meta);
    rc = index->open(index_file.c_str(), *index_meta, only_field);
    if (rc != RC::SUCCESS) {
      delete index;
      LOG_ERROR("Failed to open index. table=%s, index=%s, file=%s, rc=%d:%s",
                name(), index_meta->name(), index_file.c_str(), rc, strrc(rc));
      return rc;
    }
    unique_indexes_.push_back(index);
  }
  return rc;
}

RC Table::drop_all_indexes() {
  const int index_num = table_meta_.index_num();
  for (int i = 0; i < index_num; ++i) {
    BplusTreeIndex *index = dynamic_cast<BplusTreeIndex *>(indexes_[i]);

    // remove index file
    std::string index_file = index_data_file(base_dir_.c_str(), name(), index->index_meta().name());
    LOG_INFO("ready to delete index file %s\n", index_file.c_str());
    
    // close index
    delete index;
    if (remove(index_file.c_str())) {
      LOG_ERROR("Failed to delete index file %s\n", index_file.c_str());
      return RC::IOERR;
    }
  }
  indexes_.clear();
  return RC::SUCCESS;
}

RC Table::drop_all_unique_indexes() {
  const int index_num = table_meta_.unique_index_num();
  for (int i = 0; i < index_num; ++i) {
    BplusTreeIndex *index = dynamic_cast<BplusTreeIndex *>(unique_indexes_[i]);

    // remove index file
    std::string index_file = index_data_file(base_dir_.c_str(), name(), index->index_meta().name());
    LOG_INFO("ready to delete index file %s\n", index_file.c_str());

    // close index
    delete index;
    if (remove(index_file.c_str())) {
      LOG_ERROR("Failed to delete index file %s\n", index_file.c_str());
      return RC::IOERR;
    }
  }
  unique_indexes_.clear();
  return RC::SUCCESS;
}

RC Table::commit_insert(Trx *trx, const RID &rid) {
  Record record;
  RC rc = record_handler_->get_record(&rid, &record);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  return trx->commit_insert(this, record);
}

RC Table::rollback_insert(Trx *trx, const RID &rid) {

  Record record;
  RC rc = record_handler_->get_record(&rid, &record);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  // remove all indexes
  rc = delete_entry_of_indexes(record.data, rid, false);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to delete indexes of record(rid=%d.%d) while rollback insert, rc=%d:%s",
              rid.page_num, rid.slot_num, rc, strrc(rc));
  } else {
    rc = record_handler_->delete_record(&rid);
  }
  return rc;
}



RC Table::insert_record(Trx *trx, Record *record) {
  RC rc = RC::SUCCESS;

  if (trx != nullptr) {
    trx->init_trx_info(this, *record);
  }
  rc = record_handler_->insert_record(record->data, table_meta_.record_size(), &record->rid);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Insert record failed. table name=%s, rc=%d:%s", table_meta_.name(), rc, strrc(rc));
    return rc;
  }

  if (trx != nullptr) {
    rc = trx->insert_record(this, record);
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to log operation(insertion) to trx");

      RC rc2 = record_handler_->delete_record(&record->rid);
      if (rc2 != RC::SUCCESS) {
        LOG_PANIC("Failed to rollback record data when insert index entries failed. table name=%s, rc=%d:%s",
                  name(), rc2, strrc(rc2));
      }
      return rc;
    }
  }

  rc = insert_entry_of_indexes(record->data, record->rid);
  if (rc != RC::SUCCESS) {
    RC rc2 = delete_entry_of_indexes(record->data, record->rid, true);
    if (rc2 != RC::SUCCESS) {
      LOG_PANIC("Failed to rollback index data when insert index entries failed. table name=%s, rc=%d:%s",
                name(), rc2, strrc(rc2));
    }
    rc2 = record_handler_->delete_record(&record->rid);
    if (rc2 != RC::SUCCESS) {
      LOG_PANIC("Failed to rollback record data when insert index entries failed. table name=%s, rc=%d:%s",
                name(), rc2, strrc(rc2));
    }
    return rc;
  }

  return rc;
}

RC Table::insert_record(Trx *trx, int value_num, const Value *values) {
  if (value_num <= 0 || nullptr == values ) {
    LOG_ERROR("Invalid argument. value num=%d, values=%p", value_num, values);
    return RC::INVALID_ARGUMENT;
  }

  // 数据进行分组
  TupleSchema schema;
  TupleSchema::from_table(this, schema);
  int per_size = schema.fields().size();
  if (value_num % per_size != 0) {
    return RC::SCHEMA_FIELD_MISSING;
  }
  int group = value_num / per_size;
  if (group > 1) {
    multi_insertion_flag = true;
  }

  RC rc;
  for(int i = 0; i < group; ++i) {
    char *record_data;
    rc = make_record(per_size, &values[i * per_size], record_data);
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to create a record. rc=%d:%s", rc, strrc(rc));
      break;
    }

    Record record;
    record.data = record_data;
    // record.valid = true;
    rc = insert_record(trx, &record);
    delete[] record_data;
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to insert a record. rc=%d:%s", rc, strrc(rc));
      break;
    }

    if (multi_insertion_flag) {
      rollback_rids.push_back(record.rid);
    }
  }
  
  // rollback insertion
  if (rc != SUCCESS && multi_insertion_flag) {
    for (auto rid : rollback_rids) {
      rollback_insert(trx, rid);
    }
  }

  // clear multiple insertion flag
  multi_insertion_flag = false;
  rollback_rids.clear();
  return rc;
}

const char *Table::name() const {
  return table_meta_.name();
}

const TableMeta &Table::table_meta() const {
  return table_meta_;
}

// date string will be recognized as CHARS type
// during parsing, so we may have to rewrite
// type here
static bool type_match(AttrType field_type, Value *value) {
  if (field_type == value->type) {
    return true;
  }

  // type rewrite
  if (field_type == DATE && value->type == CHARS) {
    value->type = DATE;
    return true;
  }

  return false;
}

/**
 * @param table 表指针
 * @param field_name 列名
 * @param res_set 结果集引用
 * @param condition select条件的指针
 * @return true表示没有错误，false表示有错误
 */
bool do_custom_select(Table *table, const char *field_name, TupleSet &res_set, Condition *condition) {
  RC rc;
  // filter
  std::vector<DefaultConditionFilter *> condition_filters;
  if (condition != nullptr) {
    auto *condition_filter = new DefaultConditionFilter();
    rc = condition_filter->init(*table, *condition);
    if (rc != RC::SUCCESS)
      return false;
    condition_filters.push_back(condition_filter);
  }

  // schema
  TupleSchema schema;
  rc = schema_add_field(table, field_name, schema);
  if (rc != RC::SUCCESS)
    return false;

  // select node
  auto *select_node = new SelectExeNode;
  rc = select_node->init(nullptr, table, std::move(schema), std::move(condition_filters));
  if (rc != RC::SUCCESS)
    return false;
  select_node->execute(res_set);

  return true;
}

/**
 * 用于insert时 unique index表中是否有一样的值
* @param value unique index所在的列的值
 * @param table 表指针
 * @param field_name 列名
 * @param res_set 结果集
 * @return
 */
bool do_unique_select(const _Value &value, Table *table, const char *field_name, TupleSet &res_set) {
  // attr
  RelAttr attr;
  relation_attr_init(&attr, table->name(), field_name);
  // condition
  Condition condition;
  memset(&condition, 0, sizeof(Condition));
  condition.left.attr = attr;
  condition.left.type = COND_FIELD;
  condition.right.value = value;
  condition.right.type = COND_VALUE;
  condition.comp = EQUAL_TO;

  return do_custom_select(table, field_name, res_set, &condition);
}

// 加在make record这里会好一点
bool Table::find_if_exist_unique_record(int value_num, const Value *values) {
  for (int i = 0; i < value_num; ++i) {
    Value &value = const_cast<Value &>(values[i]);
    const FieldMeta* field_meta = table_meta_.field(i + table_meta_.sys_field_num());
    for (const Index *index : unique_indexes_) {
      if (strcmp(index->index_meta().fields()[0].c_str(), field_meta->name()) == 0) {
        TupleSet res;
        bool success = do_unique_select(value, this, field_meta->name(), res);
        if (!success || res.size() > 0) {
          return true;
        }
      }
    }
  }
  return false;
}


RC Table::make_record(int value_num, const Value *values, char * &record_out) {
  // 检查字段类型是否一致
  if (value_num + table_meta_.sys_field_num() != table_meta_.field_num()) {
    return RC::SCHEMA_FIELD_MISSING;
  }

  const int normal_field_start_index = table_meta_.sys_field_num();
  for (int i = 0; i < value_num; i++) {
    const FieldMeta *field = table_meta_.field(i + normal_field_start_index);
    Value &value = const_cast<Value &>(values[i]);

    // match null type
    if (!field->is_nullable() && value.type == NULLS) {
      return RC::SCHEMA_FIELD_TYPE_MISMATCH;
    }

    if (!type_match(field->type(), &value)) {
      if (!field->is_nullable() || value.type != NULLS) {
        LOG_ERROR("Invalid value type. field name=%s, type=%d, but given=%d",
                  field->name(), field->type(), value.type);
        return RC::SCHEMA_FIELD_TYPE_MISMATCH;
      }
    }

    // validate value
    if (!value_validation(&value)) {
      LOG_ERROR("Fail to validate record value, field type: %d value[%d] type: %d", field->type(), i, value.type);
      return RC::INVALID_ARGUMENT;
    }
  }

  // 如果找到重复的字段，返回false
  if (find_if_exist_unique_record(value_num, values)) {
      return RC::SCHEMA_INDEX_EXIST;
  }

  // 复制所有字段的值
  int record_size = table_meta_.record_size();
  char *record = new char [record_size + 4]{0};

  for (int i = 0; i < value_num; i++) {
    const FieldMeta *field = table_meta_.field(i + normal_field_start_index);
    LOG_INFO("field %s, len %d\n", field->name(), field->len());
    const Value &value = values[i];
    if (field->is_nullable()) {
      // 增加4个字节用来表示是否为空
      int *null_flag = (int*)(record + field->offset());
      if (value.type == NULLS) {
        *null_flag = 1;
        memset(record + field->offset() + 4, 0, field->len() - 4);
      }
      else {
        *null_flag = 0;
        memcpy(record + field->offset() + 4, value.data, field->len() - 4);
      }
    }
    else {
      memcpy(record + field->offset(), value.data, field->len());
    }
  }

  record_out = record;
  return RC::SUCCESS;
}

RC Table::init_record_handler(const char *base_dir) {
  std::string data_file = std::string(base_dir) + "/" + table_meta_.name() + TABLE_DATA_SUFFIX;
  if (nullptr == data_buffer_pool_) {
    data_buffer_pool_ = theGlobalDiskBufferPool();
  }

  int data_buffer_pool_file_id;
  RC rc = data_buffer_pool_->open_file(data_file.c_str(), &data_buffer_pool_file_id);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to open disk buffer pool for file:%s. rc=%d:%s",
              data_file.c_str(), rc, strrc(rc));
    return rc;
  }

  record_handler_ = new RecordFileHandler();
  rc = record_handler_->init(*data_buffer_pool_, data_buffer_pool_file_id);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to init record handler. rc=%d:%s", rc, strrc(rc));
    return rc;
  }

  file_id_ = data_buffer_pool_file_id;
  return rc;
}

/**
 * 为了不把Record暴露出去，封装一下
 */
class RecordReaderScanAdapter {
public:
  explicit RecordReaderScanAdapter(void (*record_reader)(const char *data, void *context), void *context)
      : record_reader_(record_reader), context_(context){
  }

  void consume(const Record *record) {
    record_reader_(record->data, context_);
  }
private:
  void (*record_reader_)(const char *, void *);
  void *context_;
};

static RC scan_record_reader_adapter(Record *record, void *context) {
  RecordReaderScanAdapter &adapter = *(RecordReaderScanAdapter *)context;
  adapter.consume(record);
  return RC::SUCCESS;
}

RC Table::scan_record(Trx *trx, ConditionFilter *filter, int limit, void *context, void (*record_reader)(const char *data, void *context)) {
  RecordReaderScanAdapter adapter(record_reader, context);
  return scan_record(trx, filter, limit, (void *)&adapter, scan_record_reader_adapter);
}

int first = 0;
void connect_record(Record &r1, Record &r2, int offset, int len) {
  if (first == 0)
    memcpy(r1.data, r2.data, len);
  else {
    memcpy(r1.data + offset, r2.data + 4, len);
  }
  first++;
}

RC Table::scan_record(Trx *trx, ConditionFilter *filter, int limit, void *context, RC (*record_reader)(Record *record, void *context)) {
  if (nullptr == record_reader) {
    return RC::INVALID_ARGUMENT;
  }

  if (0 == limit) {
    return RC::SUCCESS;
  }

  if (limit < 0) {
    limit = INT_MAX;
  }

  int per_size = (table_meta_.record_size() + 4055) / 4056;

  IndexScanner *index_scanner = find_index_for_scan(filter);
  if (index_scanner != nullptr) {
    return scan_record_by_index(trx, index_scanner, filter, limit, context, record_reader);
  }

  RC rc = RC::SUCCESS;
  RecordFileScanner scanner;
  if (per_size == 1)
    rc = scanner.open_scan(*data_buffer_pool_, file_id_, filter);
  else
    rc = scanner.open_scan(*data_buffer_pool_, file_id_, nullptr);

  if (rc != RC::SUCCESS) {
    LOG_ERROR("failed to open scanner. file id=%d. rc=%d:%s", file_id_, rc, strrc(rc));
    return rc;
  }

  int record_count = 0;
  int offset = 0;
  int len = 4056;
  Record *record = nullptr;
  std::vector<Record *> need_to_free_records;
  Record tmp{};
  if (per_size > 1) {
    record = new Record{};
    record->data = static_cast<char *>(malloc(table_meta_.record_size() + 4055));
    memset(record->data, 0, table_meta_.record_size() + 4055);
  }

  rc = scanner.get_first_record(&tmp);
  for ( ; RC::SUCCESS == rc && record_count < limit; rc = scanner.get_next_record(&tmp)) {
    if (trx == nullptr || trx->is_visible(this, &tmp)) {
      record_count++;
      if (per_size == 1) {
        rc = record_reader(&tmp, context);
      }
      else {
        RID rid = tmp.rid;
        rollback_rids.emplace_back(rid);
        connect_record(*record, tmp, offset, table_meta_.record_size() - offset > len ? len : table_meta_.record_size() - offset);
        offset += 4056;
        if (record_count % per_size == 0) {
          if (filter == nullptr || filter->filter(*record)) {
              rc = record_reader(record, context);
          }
          need_to_free_records.emplace_back(record);
          record = new Record{};
          record->data = static_cast<char *>(malloc(table_meta_.record_size() + 4055));
          memset(record->data, 0, table_meta_.record_size() + 4055);
          offset = 0;
          first = 0;
          rollback_rids.clear();
        }
      }
      if (rc != RC::SUCCESS) {
        break;
      }
    }
  }
  LOG_ERROR("read page count : %d\n", record_count);
  if (per_size > 1) {
    for (Record *del : need_to_free_records) {
      free(del->data);
      delete del;
    }
  }

  if (RC::RECORD_EOF == rc) {
    rc = RC::SUCCESS;
  } else {
    LOG_ERROR("failed to scan record. file id=%d, rc=%d:%s", file_id_, rc, strrc(rc));
  }
  scanner.close_scan();
  return rc;
}

RC Table::scan_record_by_index(Trx *trx, IndexScanner *scanner, ConditionFilter *filter, int limit, void *context,
                               RC (*record_reader)(Record *, void *)) {
  RC rc = RC::SUCCESS;
  RID rid;
  Record record;
  int record_count = 0;
  while (record_count < limit) {
    rc = scanner->next_entry(&rid);
    if (rc != RC::SUCCESS) {
      if (RC::RECORD_EOF == rc) {
        rc = RC::SUCCESS;
        break;
      }
      LOG_ERROR("Failed to scan table by index. rc=%d:%s", rc, strrc(rc));
      break;
    }

    rc = record_handler_->get_record(&rid, &record);
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to fetch record of rid=%d:%d, rc=%d:%s", rid.page_num, rid.slot_num, rc, strrc(rc));
      break;
    }

    if ((trx == nullptr || trx->is_visible(this, &record)) && (filter == nullptr || filter->filter(record))) {
      rc = record_reader(&record, context);
      if (rc != RC::SUCCESS) {
        LOG_TRACE("Record reader break the table scanning. rc=%d:%s", rc, strrc(rc));
        break;
      }
    }

    record_count++;
  }

  scanner->destroy();
  return rc;
}

class IndexInserter {
public:
  explicit IndexInserter(Index *index) : index_(index) {
  }

  RC insert_index(const Record *record) {
    return index_->insert_entry(record->data, &record->rid);
  }
private:
  Index *index_;
};

static RC insert_index_record_reader_adapter(Record *record, void *context) {
  IndexInserter &inserter = *(IndexInserter *)context;
  return inserter.insert_index(record);
}

RC Table::create_index(Trx *trx, const char *index_name, int attr_count, const char **attribute_name) {
  if (index_name == nullptr || common::is_blank(index_name) ||
      attribute_name == nullptr || attr_count == 0) {
    return RC::INVALID_ARGUMENT;
  }
  if (table_meta_.index(index_name) != nullptr ||
          table_meta_.find_index_by_fields(attribute_name, attr_count)) {
    return RC::SCHEMA_INDEX_EXIST;
  }

  std::vector<FieldMeta> fields;
  for (int i = 0; i < attr_count; ++i) {
    const FieldMeta *field_meta = table_meta_.field(attribute_name[i]);
    if (!field_meta) {
      return RC::SCHEMA_FIELD_MISSING;
    }
    fields.emplace_back(*field_meta);
  }

  // 创建index meta
  IndexMeta new_index_meta;
  RC rc = new_index_meta.init(index_name, fields);
  if (rc != RC::SUCCESS) {
    return rc;
  }
  // 创建索引相关数据
  BplusTreeIndex *index = new BplusTreeIndex();
  std::string index_file = index_data_file(base_dir_.c_str(), name(), index_name);
  rc = index->create(index_file.c_str(), new_index_meta, fields);
  if (rc != RC::SUCCESS) {
    delete index;
    LOG_ERROR("Failed to create bplus tree index. file name=%s, rc=%d:%s", index_file.c_str(), rc, strrc(rc));
    return rc;
  }

  // 遍历当前的所有数据，插入这个索引
  IndexInserter index_inserter(index);
  rc = scan_record(trx, nullptr, -1, &index_inserter, insert_index_record_reader_adapter);
  if (rc != RC::SUCCESS) {
    // rollback
    delete index;
    LOG_ERROR("Failed to insert index to all records. table=%s, rc=%d:%s", name(), rc, strrc(rc));
    return rc;
  }
  indexes_.push_back(index);

  TableMeta new_table_meta(table_meta_);
  rc = new_table_meta.add_index(new_index_meta);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to add index (%s) on table (%s). error=%d:%s", index_name, name(), rc, strrc(rc));
    return rc;
  }
  // 创建元数据临时文件
  std::string tmp_file = table_meta_file(base_dir_.c_str(), name()) + ".tmp";
  std::fstream fs;
  fs.open(tmp_file, std::ios_base::out | std::ios_base::binary | std::ios_base::trunc);
  if (!fs.is_open()) {
    LOG_ERROR("Failed to open file for write. file name=%s, errmsg=%s", tmp_file.c_str(), strerror(errno));
    return RC::IOERR; // 创建索引中途出错，要做还原操作
  }
  if (new_table_meta.serialize(fs) < 0) {
    LOG_ERROR("Failed to dump new table meta to file: %s. sys err=%d:%s", tmp_file.c_str(), errno, strerror(errno));
    return RC::IOERR;
  }
  fs.close();

  // 覆盖原始元数据文件
  std::string meta_file = table_meta_file(base_dir_.c_str(), name());
  int ret = rename(tmp_file.c_str(), meta_file.c_str());
  if (ret != 0) {
    LOG_ERROR("Failed to rename tmp meta file (%s) to normal meta file (%s) while creating index (%s) on table (%s). " \
              "system error=%d:%s", tmp_file.c_str(), meta_file.c_str(), index_name, name(), errno, strerror(errno));
    return RC::IOERR;
  }

  table_meta_.swap(new_table_meta);

  LOG_INFO("add a new index (%s) on the table (%s)", index_name, name());

  return rc;
}


RC Table::create_unique_index(Trx *trx, const char *index_name, const char *attribute_name) {
  if (index_name == nullptr || common::is_blank(index_name) ||
      attribute_name == nullptr || common::is_blank(attribute_name)) {
    return RC::INVALID_ARGUMENT;
  }
  if (table_meta_.index(index_name) != nullptr ||
      table_meta_.find_index_by_fields(&attribute_name, 1)) {
    return RC::SCHEMA_INDEX_EXIST;
  }

  const FieldMeta *field_meta = table_meta_.field(attribute_name);
  if (!field_meta) {
    return RC::SCHEMA_FIELD_MISSING;
  }

  // 查找当前列是否有重复字段
  TupleSet res;
  do_custom_select(this, field_meta->name(), res, nullptr);
  const auto tuples = res.tuples();
  for (int i = 0; i < tuples.size(); ++i) {
    for (int j = i + 1; j < tuples.size(); ++j) {
      if (tuples[i].get(0).compare(tuples[j].get(0)) == 0) {
        return RC::SCHEMA_INDEX_EXIST;
      } // end if
    } // end for j
  } // end for i

  std::vector<FieldMeta> single_field;
  single_field.emplace_back(*field_meta);
  IndexMeta new_index_meta;
  RC rc = new_index_meta.init(index_name, single_field);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  // 创建索引相关数据
  BplusTreeIndex *index = new BplusTreeIndex();
  std::string index_file = index_data_file(base_dir_.c_str(), name(), index_name);
  rc = index->create(index_file.c_str(), new_index_meta, single_field);
  if (rc != RC::SUCCESS) {
    delete index;
    LOG_ERROR("Failed to create bplus tree index. file name=%s, rc=%d:%s", index_file.c_str(), rc, strrc(rc));
    return rc;
  }

  // 遍历当前的所有数据，插入这个索引
  IndexInserter index_inserter(index);
  rc = scan_record(trx, nullptr, -1, &index_inserter, insert_index_record_reader_adapter);
  if (rc != RC::SUCCESS) {
    // rollback
    delete index;
    LOG_ERROR("Failed to insert index to all records. table=%s, rc=%d:%s", name(), rc, strrc(rc));
    return rc;
  }
  unique_indexes_.push_back(index);

  TableMeta new_table_meta(table_meta_);
  rc = new_table_meta.add_unique_index(new_index_meta);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to add index (%s) on table (%s). error=%d:%s", index_name, name(), rc, strrc(rc));
    return rc;
  }
  // 创建元数据临时文件
  std::string tmp_file = table_meta_file(base_dir_.c_str(), name()) + ".tmp";
  std::fstream fs;
  fs.open(tmp_file, std::ios_base::out | std::ios_base::binary | std::ios_base::trunc);
  if (!fs.is_open()) {
    LOG_ERROR("Failed to open file for write. file name=%s, errmsg=%s", tmp_file.c_str(), strerror(errno));
    return RC::IOERR; // 创建索引中途出错，要做还原操作
  }
  if (new_table_meta.serialize(fs) < 0) {
    LOG_ERROR("Failed to dump new table meta to file: %s. sys err=%d:%s", tmp_file.c_str(), errno, strerror(errno));
    return RC::IOERR;
  }
  fs.close();

  // 覆盖原始元数据文件
  std::string meta_file = table_meta_file(base_dir_.c_str(), name());
  int ret = rename(tmp_file.c_str(), meta_file.c_str());
  if (ret != 0) {
    LOG_ERROR("Failed to rename tmp meta file (%s) to normal meta file (%s) while creating index (%s) on table (%s). " \
              "system error=%d:%s", tmp_file.c_str(), meta_file.c_str(), index_name, name(), errno, strerror(errno));
    return RC::IOERR;
  }

  table_meta_.swap(new_table_meta);

  LOG_INFO("add a new index (%s) on the table (%s)", index_name, name());
  return rc;
}


class RecordUpdater {
public:
  void split_record(Record *record, std::vector<Record*> &rec) {
    int total = table_->table_meta_.record_size();
    int count = 0;
    int offset = 0;
    while (total > 0) {
      auto *new_record = static_cast<Record *>(malloc(sizeof(Record)));
      new_record->data = static_cast<char *>(malloc(4056));
      memset(new_record->data, 0, 4056);
      memcpy(new_record->data, record->data + offset, total - offset > 4056 ? 4056 : total - offset);
      new_record->rid = table_->rollback_rids[count];
      total -= 4056;
      count++;
      rec.push_back(new_record);
    }
  }

  RecordUpdater(Table *table, Trx *trx, const char *attribute_name, const Value *value)
      : table_(table), trx_(trx), attribute_name_(attribute_name), value_(value), updated_count_(0)
      { }

    RC update(Record *old_record) {
      std::vector<Record*> old_records;
      if (table_->table_meta_.record_size() > 4056) {
        split_record(old_record, old_records);
      }
      else {
        old_records.emplace_back(old_record);
      }

      for (Record *record : old_records) {
        // prepare record to commit to update
        char* new_value_buff;
        RC rc = make_record(record, &new_value_buff);
        if (rc != RC::SUCCESS) {
          return rc;
        }

        Record new_record{};
        new_record.rid = record->rid;
        new_record.data = new_value_buff;

        // perform update
        rc = table_->update_record(trx_, record, &new_record);
        if (rc != RC::SUCCESS) {
          return rc;
        }
        delete new_value_buff;
      }

      updated_count_++;
      return RC::SUCCESS;
    }

    int update_count() const {
      return updated_count_;
    }


private:
    RC make_record(Record *record, char **out_buff) {
      auto meta = table_->table_meta();

      // copy old record data
      auto record_size = meta.record_size();
      *out_buff = new char[record_size];
      memcpy(*out_buff, record->data, record_size);

      // update field of new record data
      auto field_meta = meta.field(attribute_name_);
      memcpy(*out_buff + field_meta->offset(), value_->data, field_meta->len());

      return RC::SUCCESS;
    }

    Table *table_;
    Trx *trx_;
    const char *attribute_name_;
    const Value *value_;
    int updated_count_;
};

static RC record_reader_update_adapter(Record *record, void *context) {
  return reinterpret_cast<RecordUpdater *>(context)->update(record);
}

RC Table::update_record(Trx *trx, Record *old_record, Record *new_record) {
  RC rc;

  rc = delete_entry_of_indexes(old_record->data, old_record->rid, false);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to update(delete) indexes of record (rid=%d.%d). rc=%d:%s",
              old_record->rid.page_num, old_record->rid.slot_num, rc, strrc(rc));
  } else {  
    rc = insert_entry_of_indexes(new_record->data, new_record->rid);
    if (rc != RC::SUCCESS) {
      // how to rollback?
      LOG_ERROR("Failed to update(reinsert) indexes of record (rid=%d.%d). rc=%d:%s",
                new_record->rid.page_num, new_record->rid.slot_num, rc, strrc(rc));
      return rc;
    }
    // split record
    rc = record_handler_->update_record(new_record);
  }

  // TODO: trx used correctly?
  if (rc == RC::SUCCESS) {
    if (trx != nullptr) {
      rc = trx->update_record(this, new_record);
    }
  }

  return rc;
}

RC Table::update_record(Trx *trx, ConditionFilter *filter, const char *attribute_name, const Value *value, int *updated_count) {
  // sanity check
  const FieldMeta *field = table_meta_.field(attribute_name);

  if (field == nullptr) {
    LOG_WARN("No such field. %s.%s", name(), attribute_name);
    return RC::SCHEMA_FIELD_MISSING;
  }

  if (!type_match(field->type(), const_cast<Value *>(value))) {
    LOG_ERROR("Invalid value type. field name=%s, type=%d, but given=%d",
              field->name(), field->type(), value->type);
    return RC::SCHEMA_FIELD_TYPE_MISMATCH;
  }

  if (!value_validation(const_cast<Value *>(value))) {
    return RC::INVALID_ARGUMENT;
  }

  // real update
  RecordUpdater updater(this, trx , attribute_name, value);

  RC rc = scan_record(trx, filter, -1, &updater, record_reader_update_adapter);
  if (updated_count != nullptr) {
    *updated_count = updater.update_count();
  }

  return rc;
}

class RecordDeleter {
public:
  RecordDeleter(Table &table, Trx *trx) : table_(table), trx_(trx) {
  }

  RC delete_record(Record *record) {
    RC rc = RC::SUCCESS;
    rc = table_.delete_record(trx_, record);
    if (rc == RC::SUCCESS) {
      deleted_count_++;
    }
    return rc;
  }

  int deleted_count() const {
    return deleted_count_;
  }

private:
  Table & table_;
  Trx *trx_;
  int deleted_count_ = 0;
};

static RC record_reader_delete_adapter(Record *record, void *context) {
  RecordDeleter &record_deleter = *(RecordDeleter *)context;
  return record_deleter.delete_record(record);
}

RC Table::delete_record(Trx *trx, ConditionFilter *filter, int *deleted_count) {
  RecordDeleter deleter(*this, trx);
  RC rc = scan_record(trx, filter, -1, &deleter, record_reader_delete_adapter);
  if (deleted_count != nullptr) {
    *deleted_count = deleter.deleted_count();
  }
  return rc;
}

RC Table::delete_record(Trx *trx, Record *record) {
  RC rc = RC::SUCCESS;
  int times = (table_meta_.record_size() + 4055) / 4056;
  if (trx != nullptr) {
    if (times > 1)
      rc = trx->delete_record(this, record, rollback_rids);
    else {
      std::vector<RID> single_rid;
      single_rid.push_back(record->rid);
      rc = trx->delete_record(this, record, single_rid);
    }
  } else {
    rc = delete_entry_of_indexes(record->data, record->rid, false);// 重复代码 refer to commit_delete
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to delete indexes of record (rid=%d.%d). rc=%d:%s",
                record->rid.page_num, record->rid.slot_num, rc, strrc(rc));
    } else {
      if (times > 1) {
        for (const auto &rid: rollback_rids) {
          rc = record_handler_->delete_record(&rid);
          if (rc != RC::SUCCESS)
            return rc;
        }
      } else {
        rc = record_handler_->delete_record(&record->rid);
      }
    }
  }
  return rc;
}

RC Table::commit_delete(Trx *trx, const RID &rid) {
  RC rc = RC::SUCCESS;
  Record record;
  rc = record_handler_->get_record(&rid, &record);
  if (rc != RC::SUCCESS) {
    return rc;
  }
  rc = delete_entry_of_indexes(record.data, record.rid, false);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to delete indexes of record(rid=%d.%d). rc=%d:%s",
              rid.page_num, rid.slot_num, rc, strrc(rc));// panic?
  }

  rc = record_handler_->delete_record(&rid);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  return rc;
}

RC Table::rollback_delete(Trx *trx, const RID &rid) {
  RC rc = RC::SUCCESS;
  Record record;
  rc = record_handler_->get_record(&rid, &record);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  return trx->rollback_delete(this, record); // update record in place
}

RC Table::commit_update(Trx *trx, const RID &rid) {
  Record record;
  RC rc = record_handler_->get_record(&rid, &record);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  return trx->commit_update(this, record);
}

RC Table::insert_entry_of_indexes(const char *record, const RID &rid) {
  RC rc = RC::SUCCESS;
  for (Index *index : indexes_) {
    rc = index->insert_entry(record, &rid);
    if (rc != RC::SUCCESS) {
      break;
    }
  }

  // unique index
  for (Index *index : unique_indexes_) {
    rc = index->insert_entry(record, &rid);
    if (rc != RC::SUCCESS) {
      break;
    }
  }
  return rc;
}

RC Table::delete_entry_of_indexes(const char *record, const RID &rid, bool error_on_not_exists) {
  RC rc = RC::SUCCESS;
  for (Index *index : indexes_) {
    rc = index->delete_entry(record, &rid);
    if (rc != RC::SUCCESS) {
      if (rc != RC::RECORD_INVALID_KEY || !error_on_not_exists) {
        break;
      }
    }
  }
  return rc;
}

Index *Table::find_index(const char *index_name) const {
  for (Index *index: indexes_) {
    if (0 == strcmp(index->index_meta().name(), index_name)) {
      return index;
    }
  }

  // find unique_index
  for (Index *index: unique_indexes_) {
    if (0 == strcmp(index->index_meta().name(), index_name)) {
      return index;
    }
  }

  return nullptr;
}

IndexScanner *Table::find_index_for_scan(const DefaultConditionFilter &filter) {
  const ConDesc *field_cond_desc = nullptr;
  const ConDesc *value_cond_desc = nullptr;
  if (is_attr(filter.left()) && !is_attr(filter.right())) {
    field_cond_desc = &filter.left();
    value_cond_desc = &filter.right();
  } else if (is_attr(filter.right()) && !is_attr(filter.left())) {
    field_cond_desc = &filter.right();
    value_cond_desc = &filter.left();
  }
  if (field_cond_desc == nullptr || value_cond_desc == nullptr) {
    return nullptr;
  }

  const FieldMeta *field_meta = table_meta_.find_field_by_offset(field_cond_desc->attr_offset);
  if (nullptr == field_meta) {
    LOG_PANIC("Cannot find field by offset %d. table=%s",
              field_cond_desc->attr_offset, name());
    return nullptr;
  }

  if (field_meta->is_nullable()) {
    return nullptr;
  }

  const char *names[2] = {const_cast<char *>(field_meta->name()), nullptr};
  const IndexMeta *index_meta = table_meta_.find_index_by_fields(names, 1);
  if (nullptr == index_meta) {
    return nullptr;
  }

  Index *index = find_index(index_meta->name());
  if (nullptr == index) {
    return nullptr;
  }

  return index->create_scanner(filter.comp_op(), (const char *)value_cond_desc->value);
}

IndexScanner *Table::find_index_for_scan(const ConditionFilter *filter) {
  if (nullptr == filter) {
    return nullptr;
  }

  // remove dynamic_cast
  const DefaultConditionFilter *default_condition_filter = dynamic_cast<const DefaultConditionFilter *>(filter);
  if (default_condition_filter != nullptr) {
    return find_index_for_scan(*default_condition_filter);
  }

  const CompositeConditionFilter *composite_condition_filter = dynamic_cast<const CompositeConditionFilter *>(filter);
  if (composite_condition_filter != nullptr) {
    int filter_num = composite_condition_filter->filter_num();
    for (int i = 0; i < filter_num; i++) {
      IndexScanner *scanner= find_index_for_scan(&composite_condition_filter->filter(i));
      if (scanner != nullptr) {
        return scanner; // 可以找到一个最优的，比如比较符号是=
      }
    }
  }
  return nullptr;
}

RC Table::sync() {
  RC rc = data_buffer_pool_->flush_all_pages(file_id_);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to flush table's data pages. table=%s, rc=%d:%s", name(), rc, strrc(rc));
    return rc;
  }

  for (Index *index: indexes_) {
    rc = index->sync();
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to flush index's pages. table=%s, index=%s, rc=%d:%s",
                name(), index->index_meta().name(), rc, strrc(rc));
      return rc;
    }
  }

  // flush unique_index
  for (Index *index: unique_indexes_) {
    rc = index->sync();
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to flush index's pages. table=%s, index=%s, rc=%d:%s",
                name(), index->index_meta().name(), rc, strrc(rc));
      return rc;
    }
  }
  LOG_INFO("Sync table over. table=%s", name());
  return rc;
}
