#ifndef __ARRAY_ITERATOR_H__
#define __ARRAY_ITERATOR_H__

#include "iterator.h"

template <typename T>
class ArrayIterator : public Iterator<T> {
public: 
  ArrayIterator(T *iterData, unsigned int iterSize);

  const T next();

  const T hasNext();

  const T &operator*();

  void invalidate();

  void init(T *iterData, unsigned int iterSize);
  
private: 
  T *data;
  unsigned int index, numElts;
  bool valid;
};

#include "arrayiterator.cpp"

#endif /* __ARRAY_ITERATOR_H__ */
