#ifndef __LIST_H__
#define __LIST_H__

#include "container.h"
#include "iterator.h"

namespace josh {
  
  template <typename T>
  class List : public Container<T> {
  public:
    
    virtual const T &operator[](unsigned int index) const = 0;
    virtual T &operator[](unsigned int index) = 0;
    
    virtual void append(const T &data) = 0;
    
  };

}

#endif /* __LIST_H__ */
