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
  enum ListNodeType {
    INT,
    DOUBLE,
  };

  class ListNode {
    private:
    std::string _key;
    int _intValue;
    double _doubleValue;
    ListNodeType _type;

    public:
    ListNode(std::string key, int value) 
      : _key(key), _intValue(value), _type(ListNodeType::INT) {}
    
    ListNode(std::string key, double value) 
      : _key(key), _doubleValue(value), _type(ListNodeType::DOUBLE) {}
  
    std::string getKey() {
      return this->_key;
    }

    int getIntValue() {
      return this->_intValue;
    }

    double getDoubleValue() {
      return this->_doubleValue;
    }

    ListNodeType getType() {
      return this->_type;
    }

    ListNode* next = NULL;
  };

  ListNode* head = NULL;

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
  void _addListNode(ListNode* node);

  bool _isOverflow();

  ListNode* _unlink(ListNode* target);

  int hash(std::string key);
};

#endif