#ifndef __LIST_H__
#define __LIST_H__

#include "utils/listiterator.h"

namespace josh {
  
  class ListIndexOutOfBounds {
  };
  
  template <typename T>
  class List {
  public:
    List();
    List(unsigned int initSize);
    ~List();
    
    const T &operator[](unsigned int index) const;
    T &operator[](unsigned int index);
    
    void append(const T &data);
    
    Iterator<T> &iterator();
    
  private:
    T *data;
    unsigned int maxElts, numElts;
    
    void checkBounds(unsigned int index);
    void extend();
    
    struct iterNode {
      ListIterator<T> *it;
      iterNode *next;
    };
    
    iterNode *validIters;
    iterNode *invalidIters;
    
    void invalidateIterators();
  };

}

#define __LIST_CPP__ "../../src/utils/list.cpp"

#include __LIST_CPP__

#endif /* __LIST_H__ */
