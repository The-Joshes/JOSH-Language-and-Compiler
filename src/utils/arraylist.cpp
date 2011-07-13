#include "utils/arraylist.h"
#include "utils/arraylistiterator.h"

const int INITSIZE = 10;

namespace josh {
  
  template <typename T>
  ArrayList<T>::ArrayList() {
    maxElts = INITSIZE;
    data = new T[maxElts];
    numElts = 0;
    validIters = 0;
    invalidIters = 0;
  }
  
  template <typename T>
  ArrayList<T>::ArrayList(unsigned int initSize) {
    maxElts = initSize;
    data = new T[maxElts];
    numElts = 0;
    validIters = 0;
    invalidIters = 0;
  }
  
  template <typename T>
  ArrayList<T>::~ArrayList() {
    delete [] data;

    while(validIters) {
      iterNode *node = validIters;
      validIters = node->next;
      delete node->it;
      delete node;
    }
    while(invalidIters) {
      iterNode *node = invalidIters;
      invalidIters = node->next;
      delete node->it;
      delete node;
    }
  }
  
  template <typename T>
  const T &ArrayList<T>::operator[](unsigned int index) const {
    checkBounds(index);
    return data[index];
  }
  
  template <typename T>
  T &ArrayList<T>::operator[](unsigned int index) {
    checkBounds(index);
    return data[index];
  }
  
  template <typename T>
  void ArrayList<T>::append(const T &elt) {
    while(numElts >= maxElts)
      extend();
    data[numElts++] = elt;
    invalidateIterators();
  }
  
  template <typename T>
  Iterator<T> &ArrayList<T>::iterator() {
    iterNode *node;
    if(invalidIters) {
      node = invalidIters;
      invalidIters = node->next;
      node->it->init(data, numElts);
    }
    else {
      node = new iterNode;
      node->it = new ArrayListIterator<T>(data, numElts);
    }
    
    node->next = validIters;
    validIters = node;
    
    return *(node->it);
  }
  
  template <typename T>
  void ArrayList<T>::checkBounds(unsigned int index) const {
    if(index >= numElts)
      throw ArrayListIndexOutOfBounds();
    return;
  }
  
  template <typename T>
  void ArrayList<T>::extend() {
    T *newData = new T[2*maxElts+1];
    for(int i = 0; i < maxElts; i++)
      newData[i] = data[i];
    delete [] data;
    maxElts *= 2;
  }
  
  template <typename T>
  void ArrayList<T>::invalidateIterators() {
    while(validIters) {
      iterNode *node = validIters;
      validIters->it->invalidate();
      validIters = validIters->next;
      node->next = invalidIters;
      invalidIters = node;
    }
  }
  
}
