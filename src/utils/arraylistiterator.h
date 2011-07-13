#ifndef ARRAY_LIST_ITERATOR_H
#define ARRAY_LIST_ITERATOR_H

#include "utils/iterator.h"

namespace josh {
  
  template <typename T>
  class ArrayListIterator : public Iterator<T> {
  public: 
    ArrayListIterator(T *iterData, unsigned int iterSize);
    const T next();
    const bool hasNext();
    const T &operator*();
    
  private: 
    void invalidate();
    void init(T *iterData, unsigned int iterSize);
    
    T *data;
    unsigned int index, numElts;
    bool valid;
  };

}

#define ARRAY_LIST_ITERATOR_CPP \
  "../../src/utils/arraylistiterator.cpp"

#include ARRAY_LIST_ITERATOR_CPP

#endif /* LIST_ITERATOR_H */
