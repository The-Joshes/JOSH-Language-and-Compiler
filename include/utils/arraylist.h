#ifndef __ARRAY_LIST_H__
#define __ARRAY_LIST_H__

#include "utils/arraylistiterator.h"
#include "utils/list.h"

namespace josh {
  
  class ArrayListIndexOutOfBounds {
  };
  
  template <typename T>
  class ArrayList : public List<T> {
  public:
    ArrayList();
    ArrayList(unsigned int initSize);
    ~ArrayList();
    
    const T &operator[](unsigned int index) const;
    T &operator[](unsigned int index);
    
    void append(const T &data);
    
    Iterator<T> &iterator();
    
  private:
    T *data;
    unsigned int maxElts, numElts;
    
    void checkBounds(unsigned int index) const;
    void extend();
    
    struct iterNode {
      ArrayListIterator<T> *it;
      iterNode *next;
    };
    
    iterNode *validIters;
    iterNode *invalidIters;
    
    void invalidateIterators();
  };

}

#define __ARRAY_LIST_CPP__ "../../src/utils/arraylist.cpp"

#include __ARRAY_LIST_CPP__

#endif /* __ARRAY_LIST_H__ */
