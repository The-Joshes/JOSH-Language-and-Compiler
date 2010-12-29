#include "utils/listiterator.h"

using namespace josh;

template <typename T>
ListIterator<T>::ListIterator(T *iterData, unsigned int iterSize) {
  init(iterData, iterSize);
}

template <typename T>
const T ListIterator<T>::next() {
  if(!valid)
    throw InvalidIterator();
  if(index >= numElts)
    throw EmptyIterator();
  return data[index++];
}

template <typename T>
const T ListIterator<T>::hasNext() {
  if(!valid)
    throw InvalidIterator();
  return index < numElts;
}

template <typename T>
const T &ListIterator<T>::operator*() {
  if(!valid)
    throw InvalidIterator();
  if(index >= numElts)
    throw EmptyIterator();
  return data[index];
}

template <typename T>
void ListIterator<T>::init(T *iterData, unsigned int iterSize) {
  data = iterData;
  numElts = iterSize;
  valid = true;
  index = 0;
}

template <typename T>
void ListIterator<T>::invalidate() {
  valid = false;
}
