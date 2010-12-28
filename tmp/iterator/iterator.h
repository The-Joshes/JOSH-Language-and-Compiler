#ifndef __ITERATOR_H__
#define __ITERATOR_H__

class InvalidIterator {};
class EmptyIterator {};

template <typename T>
class Iterator {
  virtual const T next() = 0;
  virtual const T hasNext() = 0;
};

#endif /* __ITERATOR_H__ */
