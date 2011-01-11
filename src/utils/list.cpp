#include "utils/iterator.h"
#include "utils/list.h"

#define INITSIZE 10

template <typename T>
josh::List<T>::List() {
  maxElts = INITSIZE;
  data = new T[maxElts];
  numElts = 0;
  validIters = 0;
  invalidIters = 0;
}

template <typename T>
josh::List<T>::List(unsigned int initSize) {
  maxElts = initSize;
  data = new T[maxElts];
  numElts = 0;
  validIters = 0;
  invalidIters = 0;
}

template <typename T>
josh::List<T>::~List() {
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
const T &josh::List<T>::operator[](unsigned int index) const {
  checkBounds(index);
  return data[index];
}

template <typename T>
T &josh::List<T>::operator[](unsigned int index) {
  checkBounds(index);
  return data[index];
}

template <typename T>
void josh::List<T>::append(const T &elt) {
  while(numElts >= maxElts)
    extend();
  data[numElts++] = elt;
  invalidateIterators();
}

template <typename T>
josh::Iterator<T> &josh::List<T>::iterator() {
  iterNode *node;
  if(invalidIters) {
    node = invalidIters;
    invalidIters = node->next;
    node->it->init(data, numElts);
  }
  else {
    node = new iterNode;
    node->it = new josh::ListIterator<T>(data, numElts);
  }
  
  node->next = validIters;
  validIters = node;

  return *(node->it);
}

template <typename T>
void josh::List<T>::checkBounds(unsigned int index) {
  if(index >= numElts)
    throw josh::ListIndexOutOfBounds();
  return;
}

template <typename T>
void josh::List<T>::extend() {
  T *newData = new T[2*maxElts+1];
  for(int i = 0; i < maxElts; i++)
    newData[i] = data[i];
  delete [] data;
  maxElts *= 2;
}

template <typename T>
void josh::List<T>::invalidateIterators() {
  while(validIters) {
    iterNode *node = validIters;
    validIters->it->invalidate();
    validIters = validIters->next;
    node->next = invalidIters;
    invalidIters = node;
  }
}
