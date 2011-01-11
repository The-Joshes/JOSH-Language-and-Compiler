#include "utils/arraylist.h"
#include "utils/arraylistiterator.h"

#define INITSIZE 10

template <typename T>
josh::ArrayList<T>::ArrayList() {
  maxElts = INITSIZE;
  data = new T[maxElts];
  numElts = 0;
  validIters = 0;
  invalidIters = 0;
}

template <typename T>
josh::ArrayList<T>::ArrayList(unsigned int initSize) {
  maxElts = initSize;
  data = new T[maxElts];
  numElts = 0;
  validIters = 0;
  invalidIters = 0;
}

template <typename T>
josh::ArrayList<T>::~ArrayList() {
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
const T &josh::ArrayList<T>::operator[](unsigned int index) const {
  checkBounds(index);
  return data[index];
}

template <typename T>
T &josh::ArrayList<T>::operator[](unsigned int index) {
  checkBounds(index);
  return data[index];
}

template <typename T>
void josh::ArrayList<T>::append(const T &elt) {
  while(numElts >= maxElts)
    extend();
  data[numElts++] = elt;
  invalidateIterators();
}

template <typename T>
josh::Iterator<T> &josh::ArrayList<T>::iterator() {
  iterNode *node;
  if(invalidIters) {
    node = invalidIters;
    invalidIters = node->next;
    node->it->init(data, numElts);
  }
  else {
    node = new iterNode;
    node->it = new josh::ArrayListIterator<T>(data, numElts);
  }
  
  node->next = validIters;
  validIters = node;

  return *(node->it);
}

template <typename T>
void josh::ArrayList<T>::checkBounds(unsigned int index) const {
  if(index >= numElts)
    throw josh::ArrayListIndexOutOfBounds();
  return;
}

template <typename T>
void josh::ArrayList<T>::extend() {
  T *newData = new T[2*maxElts+1];
  for(int i = 0; i < maxElts; i++)
    newData[i] = data[i];
  delete [] data;
  maxElts *= 2;
}

template <typename T>
void josh::ArrayList<T>::invalidateIterators() {
  while(validIters) {
    iterNode *node = validIters;
    validIters->it->invalidate();
    validIters = validIters->next;
    node->next = invalidIters;
    invalidIters = node;
  }
}
