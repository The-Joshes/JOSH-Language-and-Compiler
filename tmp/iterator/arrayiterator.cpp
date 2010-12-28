#include "arrayiterator.h"

template <typename T>
ArrayIterator<T>::ArrayIterator(T *iterData, unsigned int iterSize) {
  init(iterData, iterSize);
}

template <typename T>
const T ArrayIterator<T>::next() {
  if(!valid)
    throw InvalidIterator();
  if(index >= numElts)
    throw EmptyIterator();
  return data[index++];
}

template <typename T>
const T ArrayIterator<T>::hasNext() {
  if(!valid)
    throw InvalidIterator();
  return index < numElts;
}

template <typename T>
const T &ArrayIterator<T>::operator*() {
  if(!valid)
    throw InvalidIterator();
  if(index >= numElts)
    throw EmptyIterator();
  return data[index];
}

template <typename T>
void ArrayIterator<T>::init(T *iterData, unsigned int iterSize) {
  data = iterData;
  numElts = iterSize;
  valid = true;
  index = 0;
}

template <typename T>
void ArrayIterator<T>::invalidate() {
  valid = false;
}
