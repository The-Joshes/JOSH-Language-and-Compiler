#ifndef __ITERATOR_H__
#define __ITERATOR_H__

namespace josh {
  
  class InvalidIterator {};
  class EmptyIterator {};
  
  template <typename T>
  class Iterator {
  public:
    virtual const T next() = 0;
    virtual const bool hasNext() = 0;
    virtual const T &operator*() = 0;
  };

}

#endif /* __ITERATOR_H__ */
