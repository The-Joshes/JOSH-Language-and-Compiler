#include "utils/listiterator.h"

template <typename T>
josh::ListIterator<T>::ListIterator(T *iterData, unsigned int iterSize) {
  init(iterData, iterSize);
}

template <typename T>
const T josh::ListIterator<T>::next() {
  if(!valid)
    throw InvalidIterator();
  if(index >= numElts)
    throw EmptyIterator();
  return data[index++];
}

template <typename T>
const bool josh::ListIterator<T>::hasNext() {
  if(!valid)
    throw InvalidIterator();
  return index < numElts;
}

template <typename T>
const T &josh::ListIterator<T>::operator*() {
  if(!valid)
    throw InvalidIterator();
  if(index >= numElts)
    throw EmptyIterator();
  return data[index];
}

template <typename T>
void josh::ListIterator<T>::init(T *iterData, unsigned int iterSize) {
  data = iterData;
  numElts = iterSize;
  valid = true;
  index = 0;
}

template <typename T>
void josh::ListIterator<T>::invalidate() {
  valid = false;
}
