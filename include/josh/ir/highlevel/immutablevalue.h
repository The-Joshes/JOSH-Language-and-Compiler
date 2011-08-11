#ifndef __IMMUTABLEVALUE_H__
#define __IMMUTABLEVALUE_H__

#include <list>

#include "josh/ir/highlevel/user.h"

/// class Immutable
/// Represents any run-time immutable Value.
/**
 * An ImmutableValue can only use other ImmutableValue; attempting to make it 
 * use any other kind of Value will result in an assert(0).
 */
class ImmutableValue : public User 
{
public:

protected:
  ImmutableValue(Type*, const std::string &name = "");
  
  void addUse(Value*);     ///< overriden from User addUse()
  bool removeUse(Value*);  ///< overriden from User removeUse()
};

#endif
