#ifndef __IMMUTABLEVALUE_H__
#define __IMMUTABLEVALUE_H__

#include <list>

#include "josh/ir/highlevel/value.h"

/// class Immutable
/// Represents any run-time immutable Value.
/**
 * 
 */
class ImmutableValue : public Value
{
public:
  std::list<ImmutableValue*>::iterator& getUses();

  void replaceUsesOfWith(ImmutableValue *from, ImmutableValue *to);

protected:
  ImmutableValue(Type*, const std::string &name = "");
  
  void addUse(ImmutableValue*);     ///< adds Value to the uses list
  bool removeUse(ImmutableValue*);  ///< if Value is in uses list, removes and returns true
  
private:
  std::list<ImmutableValue*> uses;
};

#endif
