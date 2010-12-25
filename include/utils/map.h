#ifndef __MAP_H__
#define __MAP_H__

#include <map>

namespace josh
{
  template <typename Key, typename Val>
  class Map
  {
  public:
    Val &operator[](const Key key);
  private:
    std::map<Key, Val> fakeMap;
  };
}

using josh::Map;

template <typename Key, typename Val>
Val &Map<Key, Val>::operator[](const Key key)
{
  return fakeMap[key];
}

#endif
