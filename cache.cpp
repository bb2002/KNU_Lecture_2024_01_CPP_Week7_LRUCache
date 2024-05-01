#include "cache.h"
#include <iostream>

// TODO: 필요한 함수 구현

Cache::Cache() {
  this->head = NULL;
}

void Cache::add(std::string key, int value) {
  this->_addListNode(new ListNode(key, value));
}

void Cache::add(std::string key, double value) {
  this->_addListNode(new ListNode(key, value));
}

bool Cache::get(std::string key, int &value) {
  ListNode* node = this->head;

  while (node != NULL) {
    if (node->getKey() == key) {
      value = node->getIntValue();
      delete this->_unlink(node);

      return true;
    }
    node = node->next;
  }

  return false;
}

bool Cache::get(std::string key, double &value) {
  ListNode* node = this->head;

  while (node != NULL) {
    if (node->getKey() == key) {
      value = node->getDoubleValue();
      delete this->_unlink(node);

      return true;
    }
    node = node->next;
  }

  return false;
}

std::string Cache::toString() {
  std::ostringstream stream;
  ListNode* node = this->head;

  while (node != NULL) {
    stream << "[";

    ListNodeType type = node->getType();
    if (type == ListNodeType::INT) {
      stream << "palindrome(" << node->getKey() << "): ";
      stream << node->getIntValue();
    }
    
    if (type == ListNodeType::DOUBLE) {
      stream << "multiply(" << node->getKey() << "): ";
      stream << node->getDoubleValue();
    }

    stream << "]";

    if (node->next != NULL) {
      stream << " -> ";
    }
    
    node = node->next;
  }

  stream << std::endl;
  return stream.str();
}

void Cache::_addListNode(ListNode* node) {
  if (this->head == NULL) {
    this->head = node;
  } else {
    node->next = this->head;
    this->head = node;
  }

  if (this->_isOverflow()) {
    ListNode* node = this->head;
    while (node->next != NULL) {
      node = node->next;
    }

    // 리스트 갯수를 초과했다면, 값을 하나 삭제한다.
    delete this->_unlink(node);
  }
}

bool Cache::_isOverflow() {
  int size = 0;
  for (ListNode* node = this->head; node != NULL; node = node->next) {
    ++size;
  }

  return size == CACHE_SIZE + 1;
}

Cache::ListNode* Cache::_unlink(ListNode* target) {
  if (target == NULL || this->head == NULL) {
    return NULL;
  }

  if (target == this->head) {
    this->head = this->head->next;
    return target;
  }

  ListNode* before = this->head;
  while (before->next != NULL && before->next != target) {
    before = before->next;
  }

  if (before->next == NULL) {
    return NULL;
  }

  before->next = target->next;
  return target;
}

Cache::~Cache() {
  ListNode* current = this->head;
  while (current != NULL) {
    ListNode* removed = current;
    current = current->next;
    delete removed;
  }
}