//
// Created by Light-Laptop on 2021/11/15.
//

#include "disk_buffer_pool.h"
#include "common/log/log.h"

BPManager::BPManager(DiskBufferPool *buffer_pool, int size = BP_BUFFER_SIZE)
  : buffer_pool_(buffer_pool) {
  this->size = size;
  frames = new LRUFrame[size];

  list_init(&frame_list);
  for (int i = 0; i < size; i++) {
    frames[i].allocated = false;
    list_add_prev(&frame_list, &frames[i].list);
  }
}

BPManager::~BPManager() {
  size = 0;
  delete[] frames;
  frames = nullptr;
}

Frame *BPManager::alloc(int file_desc, PageNum page_num) {
  LRUFrame *alloc_frame = find_unallocated();

  if (alloc_frame != nullptr) {
    alloc_frame->allocated = true;
  } else {
    alloc_frame = evict();
    if (alloc_frame == nullptr) {
      return nullptr;
    }
  }

  // don't touch page_num, this should be set by file read
  alloc_frame->frame.dirty = false;
  alloc_frame->frame.file_desc = file_desc;

  // hash map update
  list_map[key(file_desc, page_num)] = alloc_frame;

  // lru update
  lru_update(alloc_frame);

  return &alloc_frame->frame;
}

void BPManager::lru_update(LRUFrame *lru_frame) {
  list_delete(&lru_frame->list);
  list_add(&frame_list, &lru_frame->list);
}

BPManager::LRUFrame *BPManager::find_unallocated() {
  for (int i = 0; i < size; i++) {
    if (!frames[i].allocated) {
      return &frames[i];
    }
  }
  return nullptr;
}

Frame *BPManager::get(int file_desc, PageNum page_num) {
  LRUFrame *found_frame = find(file_desc, page_num);

  if (found_frame != nullptr) {
    lru_update(found_frame);
    return &found_frame->frame;
  }

  return nullptr;
}

BPManager::LRUFrame *BPManager::find(int file_desc, PageNum page_num) {
  Key search_key = key(file_desc, page_num);

  if (list_map.find(search_key) != list_map.end()) {
    return list_map[search_key];
  }

  return nullptr;
}

BPManager::LRUFrame *BPManager::evict() {
  LRUFrame *search_frame;
  RC rc;

  // reversely search
  for (list_head *cur_list = frame_list.prev; cur_list != &frame_list; cur_list = cur_list->prev) {
    search_frame = container_of(LRUFrame, list, cur_list);

    if (search_frame->frame.pin_count == 0) {

      list_map.erase(key(search_frame->frame.file_desc, search_frame->frame.page.page_num));

      if (search_frame->frame.dirty) {
        rc = buffer_pool_->flush_block(&search_frame->frame);
        if (rc != RC::SUCCESS) {
          LOG_ERROR("Fail to flush block file_desc: %d, page_num: %d\n",
                    search_frame->frame.file_desc, search_frame->frame.page.page_num);
          return nullptr;
        }
      }

      return search_frame;
    }
  }

  // all pages have pin_count non-zero, fail to evict
  return nullptr;
}

RC BPManager::dispose_block(Frame *buf) {
  LRUFrame *lru_frame = container_of(LRUFrame, frame, buf);

  if (buf->pin_count != 0) {
    LOG_WARN("Begin to free page %d of %d, but it's pinned.", buf->page.page_num, buf->file_desc);
    return RC::LOCKED_UNLOCK;
  }

  if (buf->dirty) {
    RC rc = buffer_pool_->flush_block(buf);
    if (rc != RC::SUCCESS) {
      LOG_WARN("Failed to flush block %d of %d during dispose block.", buf->page.page_num, buf->file_desc);
      return rc;
    }
  }

  buf->dirty = false;
  lru_frame->allocated = false;

  LOG_DEBUG("dispost block frame =%p", buf);
  return RC::SUCCESS;
}

RC BPManager::dispose_page(int file_desc, PageNum page_num) {
  LRUFrame *frame = find(file_desc, page_num);

  if (frame != nullptr) {
    if (frame->frame.pin_count != 0) {
      LOG_ERROR("Fail to dispose page (fd: %d, page_num: %d) due to page pinned", file_desc, page_num);
      return RC::BUFFERPOOL_PAGE_PINNED;
    }
    frame->allocated = false;
  }

  return RC::SUCCESS;
}

RC BPManager::force_all_pages(int file_desc) {
  for (int i = 0; i < size; i++) {
    if (!frames[i].allocated || frames[i].frame.file_desc != file_desc) {
      continue;
    }

    if (frames[i].frame.dirty) {
      RC rc = buffer_pool_->flush_block(&frames[i].frame);
      if (rc != RC::SUCCESS) {
        LOG_ERROR("Failed to flush all pages' of fd: %d", file_desc);
        return rc;
      }
    }

    frames[i].allocated = false;
  }

  return RC::SUCCESS;
}