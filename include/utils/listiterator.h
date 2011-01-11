#ifndef __LIST_ITERATOR_H__
#define __LIST_ITERATOR_H__

#include "utils/iterator.h"

namespace josh {
  
  template <typename T>
  class ListIterator : public Iterator<T> {
  public: 
    ListIterator(T *iterData, unsigned int iterSize);
    
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

#define __LIST_ITERATOR_CPP__ "../../src/utils/listiterator.cpp"

#include __LIST_ITERATOR_CPP__

#endif /* __LIST_ITERATOR_H__ */
