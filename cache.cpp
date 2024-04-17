#include "cache.h"
#include <iostream>

// TODO: 필요한 함수 구현

Cache::Cache() {
  this->head = NULL;
}

void Cache::add(std::string key, int value) {
  ListNode* node = new ListNode(key, value);

  if (this->head == NULL) {
    this->head = node;
  } else {
    node->next = this->head;
    this->head = node;
  }
}

void Cache::add(std::string key, double value) {
 ListNode* node = new ListNode(key, value);

  if (this->head == NULL) {
    this->head = node;
  } else {
    node->next = this->head;
    this->head = node;
  }
}

bool Cache::get(std::string key, int &value) {
  ListNode* node = this->head;

  while (node != NULL) {
    if (node->getKey() == key) {
      value = node->getIntValue();
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
    stream << "[" << node->getKey() << ": ";

    ListNodeType type = node->getType();
    if (type == ListNodeType::INT) {
      stream << node->getIntValue();
    }
    
    if (type == ListNodeType::DOUBLE) {
      stream << node->getDoubleValue();
    }

    stream << "]";

    if (node->next != NULL) {
      stream << " -> ";
    }
    
    node = node->next;
  }

  return stream.str();
}

Cache::~Cache() {
  ListNode* current = this->head;
  while (current != NULL) {
    ListNode* removed = current;
    current = current->next;
    delete removed;
  }
}