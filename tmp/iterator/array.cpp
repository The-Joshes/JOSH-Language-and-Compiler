#include "iterator.h"
#include "array.h"

#define INITSIZE 10

template <typename T>
Array<T>::Array() {
  maxElts = INITSIZE;
  data = new T[maxElts];
  numElts = 0;
  validIters = 0;
  invalidIters = 0;
}

template <typename T>
Array<T>::Array(unsigned int initSize) {
  maxElts = initSize;
  data = new T[maxElts];
  numElts = 0;
  validIters = 0;
  invalidIters = 0;
}

template <typename T>
Array<T>::~Array() {
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
const T &Array<T>::operator[](unsigned int index) const {
  checkBounds(index);
  return data[index];
}

template <typename T>
T &Array<T>::operator[](unsigned int index) {
  checkBounds(index);
  return data[index];
}

template <typename T>
void Array<T>::append(const T &elt) {
  while(numElts >= maxElts)
    extend();
  data[numElts++] = elt;
  invalidateIterators();
}

template <typename T>
Iterator<T> &Array<T>::iterator() {
  iterNode *node;
  if(invalidIters) {
    node = invalidIters;
    invalidIters = node->next;
    node->it->init(data, numElts);
  }
  else {
    node = new iterNode;
    node->it = new ArrayIterator<T>(data, numElts);
  }
  
  node->next = validIters;
  validIters = node;

  return *(node->it);
}

template <typename T>
void Array<T>::checkBounds(unsigned int index) {
  if(index >= numElts)
    throw ArrayIndexOutOfBounds();
  return;
}

template <typename T>
void Array<T>::extend() {
  T *newData = new T[2*maxElts+1];
  for(int i = 0; i < maxElts; i++)
    newData[i] = data[i];
  delete [] data;
  maxElts *= 2;
}

template <typename T>
void Array<T>::invalidateIterators() {
  while(validIters) {
    iterNode *node = validIters;
    validIters->it->invalidate();
    validIters = validIters->next;
    node->next = invalidIters;
    invalidIters = node;
  }
}
