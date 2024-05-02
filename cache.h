#ifndef CACHE_H
#define CACHE_H

#include <string>
#include <sstream>

#define CACHE_SIZE 10
#define HASH_SIZE 5

class Cache {
private:
  // TODO: private inner struct/class 선언 가능
  // TODO: private 멤버 변수와 함수 추가 가능
  enum CacheType {
    INT,
    DOUBLE,
  };

  class CacheListNode {
    private:
    std::string _key;
    int _intValue;
    double _doubleValue;
    CacheType _type;

    public:
    CacheListNode* llink;
    CacheListNode* rlink;

    public:
    CacheListNode() {
      this->llink = this;
      this->rlink = this;
    }

    CacheListNode(std::string key, int value) 
      : _key(key), _intValue(value), _type(CacheType::INT) {}
    
    CacheListNode(std::string key, double value) 
      : _key(key), _doubleValue(value), _type(CacheType::DOUBLE) {}

    std::string getKey() {
      return this->_key;
    }

    int getIntValue() {
      return this->_intValue;
    }

    double getDoubleValue() {
      return this->_doubleValue;
    }

    CacheType getType() {
      return this->_type;
    }
  };

  class HashListNode {
    public:
    HashListNode() {
      this->llink = this;
      this->rlink = this;
      this->value = NULL;
    }

    HashListNode* llink;
    HashListNode* rlink;
    Cache::CacheListNode* value;
  };

  CacheListNode* head = new CacheListNode();
  HashListNode** hashMap;

public:
  Cache();
  ~Cache();
  // int를 cache에 추가한다
  void add(std::string key, int value);
  // double을 cache에 추가한다
  void add(std::string key, double value);
  // key에 해당하는 value를 cache에서 가져온다
  // 타입과 key가 동일한 원소가 없다면 false를 반환한다.
  bool get(std::string key, int &value);
  // key에 해당하는 value를 cache에서 가져온다.
  // 타입과 key가 동일한 원소가 없다면 false를 반환한다.
  bool get(std::string key, double &value);

  // 디버그 및 채점 용: 연결 리스트를 문자열로 표현하여 반환한다
  // 다음과 같이 표현된 문자열을 반환한다
  // [key1: value1] -> [key2: value2] -> ... -> [keyN: valueN]
  std::string toString();

private:
  void _addCacheListNode(CacheListNode* node);

  void _addHashListNode(int hashId, CacheListNode* node);

  bool _isCacheListNodeFull();

  CacheListNode* _unlinkCacheListNode(CacheListNode* target);

  HashListNode* _unlinkHashListNode(HashListNode* head, HashListNode* target);

  int hash(std::string key);
};

#endif