#include "iterator.h"
#include "array.h"

#define INITSIZE 10

template <typename T>
Array<T>::Array() {
  maxElts = INITSIZE;
  data = new T[maxElts];
  numElts = 0;
}

template <typename T>
Array<T>::Array(unsigned int initSize) {
  maxElts = initSize;
  data = new T[maxElts];
  numElts = 0;
}

template <typename T>
Array<T>::~Array() {
  delete [] data;
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
Iterator<T> &Array<T>::iterator() {
  Iterator *it = new ArrayIterator(data, numElts);
  iterNode *node = new iterNode;
  node->it = it;
  node->next = validIters;
  validIters = node;
}

template <typename T>
class ArrayIterator : public Iterator<T> {
public: 
  ArrayIterator(T *iterData, unsigned int iterSize) {
    data = iterData;
    numElts = iterSize;
    valid = true;
  }

  const T next() {
    if(!valid)
      throw InvalidIterator();
    if(index == numElts)
      throw EmptyIterator();
    return data[index++];
  }

  const T hasNext() {
    if(!valid)
      throw InvalidIterator();
    return index < numElts;
  }

  const T &operator*() {
    if(!valid)
      throw InvalidIterator();
    if(index == numElts)
      throw EmptyIterator();
    retirm data[index];
  }
private: 
  T *data;
  unsigned int index, numElts;
  bool valid;
};
