#ifndef __ARRAY_LIST_ITERATOR_H__
#define __ARRAY_LIST_ITERATOR_H__

#include "utils/iterator.h"

namespace josh {
  
  template <typename T>
  class ArrayListIterator : public Iterator<T> {
  public: 
    ArrayListIterator(T *iterData, unsigned int iterSize);
    
    const T next();
    
    const bool hasNext();
    
    const T &operator*();
    
    void invalidate();
    
    void init(T *iterData, unsigned int iterSize);
    
  private: 
    T *data;
    unsigned int index, numElts;
    bool valid;
  };

}

#define __ARRAY_LIST_ITERATOR_CPP__ \
  "../../src/utils/arraylistiterator.cpp"

#include __ARRAY_LIST_ITERATOR_CPP__

#endif /* __LIST_ITERATOR_H__ */
