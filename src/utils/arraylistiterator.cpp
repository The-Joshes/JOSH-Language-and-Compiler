#include "utils/arraylistiterator.h"

template <typename T>
josh::ArrayListIterator<T>::ArrayListIterator(T *iterData, unsigned int iterSize) {
  init(iterData, iterSize);
}

template <typename T>
const T josh::ArrayListIterator<T>::next() {
  if(!valid)
    throw InvalidIterator();
  if(index >= numElts)
    throw EmptyIterator();
  return data[index++];
}

template <typename T>
const bool josh::ArrayListIterator<T>::hasNext() {
  if(!valid)
    throw InvalidIterator();
  return index < numElts;
}

template <typename T>
const T &josh::ArrayListIterator<T>::operator*() {
  if(!valid)
    throw InvalidIterator();
  if(index >= numElts)
    throw EmptyIterator();
  return data[index];
}

template <typename T>
void josh::ArrayListIterator<T>::init(T *iterData, unsigned int iterSize) {
  data = iterData;
  numElts = iterSize;
  valid = true;
  index = 0;
}

template <typename T>
void josh::ArrayListIterator<T>::invalidate() {
  valid = false;
}
