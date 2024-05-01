#include "cached_runner.h"
#include "task_runner.h"

// TODO: 필요한 함수 구현

CachedRunner::CachedRunner(Cache &cache) : _cache(cache) {}

double CachedRunner::multiply(std::string filename) {
  double value;
  if (this->_cache.get(filename, value)) {
    // Cache hit
    ++this->hitCount;
  } else {
    value = TaskRunner::multiply(filename);
    ++this->missCount;
  }
  
  this->_cache.add(filename, value);
  return value;
}

int CachedRunner::palindrome(std::string filename) {
  int value;
  if (this->_cache.get(filename, value)) {
    // Cache hit
    ++this->hitCount;
  } else {
    value = TaskRunner::palindrome(filename);
    ++this->missCount;
  }
  
  this->_cache.add(filename, value);
  return value;
}

int CachedRunner::hits() {
  return this->hitCount;
}

int CachedRunner::misses() {
  return this->missCount;
}