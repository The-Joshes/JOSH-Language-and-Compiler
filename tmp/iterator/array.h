#ifndef __ARRAY_H__
#define __ARRAY_H__

#include "iterator.h"

class ArrayIndexOutOfBounds {
};

template <typename T>
class Array {
public:
  Array();
  Array(unsigned int initSize);
  ~Array();

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
    Iterator *it;
    iterNode *next;
  };

  iterNode *validIters;

  void invalidateIterators();
};

#include "array.cpp"

#endif /* __ARRAY_H__ */
