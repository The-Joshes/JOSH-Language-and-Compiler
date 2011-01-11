#ifndef __CONTAINER_H__
#define __CONTAINER_H__

#include "iterator.h"

namespace josh {
  template <typename T>
  class Container {
    virtual josh::Iterator<T> &iterator() = 0;
  };
}

#endif /* __CONTAINER_H__ */
