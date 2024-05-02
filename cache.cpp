#include "cache.h"
#include <iostream>

// TODO: 필요한 함수 구현

Cache::Cache() {
  this->hashMap = new HashListNode*[HASH_SIZE];
  for (int i = 0; i < HASH_SIZE; ++i) {
    this->hashMap[i] = NULL;
  }
}

void Cache::add(std::string key, int value) {
  this->_addCacheListNode(new CacheListNode(key, value));
}

void Cache::add(std::string key, double value) {
  this->_addCacheListNode(new CacheListNode(key, value));
}

bool Cache::get(std::string key, int &value) {
  int hashId = this->hash(key);
  HashListNode* head = this->hashMap[hashId];
  if (head == NULL || (head->llink == head && head->rlink == head)) {
    return false;
  }

  for (HashListNode* p = head->rlink; p != head; p = p->rlink) {
    if (p->value->getKey() == key) {
      value = p->value->getIntValue();

      // 삭제 후 재등록하여 우선순위를 위로 올린다.
      CacheListNode* link = p->value;
      this->_unlinkCacheListNode(link);
      this->_addCacheListNode(link);

      return true;
    }
  }

  return false;
}

bool Cache::get(std::string key, double &value) {
  int hashId = this->hash(key);
  HashListNode* head = this->hashMap[hashId];
  if (head == NULL || (head->llink == head && head->rlink == head)) {
    return false;
  }

  for (HashListNode* p = head->rlink; p != head; p = p->rlink) {
    if (p->value->getKey() == key) {
      value = p->value->getDoubleValue();

      // 삭제 후 재등록하여 우선순위를 위로 올린다.
      CacheListNode* link = p->value;
      this->_unlinkCacheListNode(link);
      this->_addCacheListNode(link);

      return true;
    }
  }

  return false;
}

std::string Cache::toString() {
  std::ostringstream stream;
  for (CacheListNode* node = head->rlink; node != head; node = node->rlink) {
    stream << "[";

    CacheType type = node->getType();
    if (type == CacheType::INT) {
      stream << "palindrome(" << node->getKey() << "): ";
      stream << node->getIntValue();
    }
    
    if (type == CacheType::DOUBLE) {
      stream << "multiply(" << node->getKey() << "): ";
      stream << node->getDoubleValue();
    }

    stream << "]";

    if (node->rlink != head) {
      stream << " -> ";
    }
  }

  stream << std::endl;
  return stream.str();
}

void Cache::_addCacheListNode(CacheListNode* node) {
  node->llink = head;
  node->rlink = head->rlink;
  head->rlink->llink = node;
  head->rlink = node;

  // 해시맵에 등록
  this->_addHashListNode(this->hash(node->getKey()), node);

  // 캐시 리스트가 꽉 찼다면 마지막 값 제거
  if (this->_isCacheListNodeFull()) {
    delete this->_unlinkCacheListNode(head->llink);
  }
}

void Cache::_addHashListNode(int hashId, CacheListNode* item) {
  if (this->hashMap[hashId] == NULL) {
    // 첫 추가라면 헤드 노드를 추가한다.
    this->hashMap[hashId] = new HashListNode();
  }

  HashListNode* node = new HashListNode();
  HashListNode* head = this->hashMap[hashId];
  node->value = item;

  node->llink = head;
  node->rlink = head->rlink;
  head->rlink->llink = node;
  head->rlink = node;
}

bool Cache::_isCacheListNodeFull() {
  if (head->llink == head && head->rlink == head) {
    return 0;
  }

  int size = 0;
  for (CacheListNode* p = head->rlink; p != head; p = p->rlink) {
    ++size;
  }

  return size > CACHE_SIZE;
}

Cache::CacheListNode* Cache::_unlinkCacheListNode(CacheListNode* target) {
  if (target == head) {
    return NULL;
  }

  // 해시맵에서 삭제
  HashListNode* head = this->hashMap[this->hash(target->getKey())];
  if (head->llink == head && head->rlink == head) {
    std::cout << "Fatal! hashMap already empty." << std::endl;
  } else {
    for (HashListNode* p = head->rlink; p != head; p = p->rlink) {
      if (p->value == target) {
        delete this->_unlinkHashListNode(head, p);
        break;
      }
    }
  }

  target->llink->rlink = target->rlink;
  target->rlink->llink = target->llink;
  return target;
}

Cache::HashListNode* Cache::_unlinkHashListNode(HashListNode* head, HashListNode* target) {
  if (target == head) {
    return NULL;
  }

  target->llink->rlink = target->rlink;
  target->rlink->llink = target->llink;
  return target;
}

int Cache::hash(std::string key) {
  int sum = 0;
  for (int i = 0; i < key.length(); ++i) {
    sum += key[i];
  }

  return sum % HASH_SIZE;
}

Cache::~Cache() {
  CacheListNode* remove = NULL;
  for (CacheListNode* p = this->head->rlink; p != head; p = p->rlink) {
    if (remove != NULL) {
      delete remove;
    }
    remove = p;
  }
  delete remove;

  for (int i = 0; i < HASH_SIZE; ++i) {
    HashListNode* head = this->hashMap[i];
    if (head != NULL) {
      HashListNode* remove = NULL;
      for (HashListNode* p = head->rlink; p != head; p = p->rlink) {
        if (remove != NULL) {
          delete remove;
        }
        remove = p;
      }
    }
    delete remove;
  }
}