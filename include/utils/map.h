#ifndef __MAP_H__
#define __MAP_H__

#include <map>
#include "container.h"
#include "iterator.h"

namespace josh
{
  template <typename Key, typename Val>
  class Map : public Container<Val>
  {
  public:
    Val &operator[](const Key key);
    Iterator<Val> &iterator();
  private:
    std::map<Key, Val> fakeMap;
  };
}

template <typename Key, typename Val>
Val &josh::Map<Key, Val>::operator[](const Key key)
{
  return fakeMap[key];
}

#endif
