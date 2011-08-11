#ifndef __USER_H__
#define __USER_H__

#include <string>

#include "josh/ir/highlevel/value.h"

/// class User
/// Represents any Value which also directly depends on or uses other Value(s).
/**
 * User is an abstract base class.
 */
class User : public Value
{
public:
  /// Returns an iterator containing all Values that this Value
  /// depends on/uses.
  std::list<Value*>::iterator& getUses();

  int getNumUses() const; ///< returns the number of Values that this uses

  /// Modifies what values this Value depends on.
  /// Replaces each instance of from in the uses list with to.
  /// For Constants, it is not valid for "to" to be a non-Constant.
  /// If this is a Constant and to is not a Constant, 0 is asserted.
  /// If from is not in the uses list, the function returns as normal.
  void replaceUsesOfWith(Value *from, Value *to);

protected:
  virtual void addUse(Value*); ///< adds Value to the uses list
  virtual bool removeUse(Value*); ///< if Value is in uses list, removes and returns true
 
  User(Type*, const std::string &name = "");

private:
  std::list<Value*> uses; ///< all Values this User depends on
};

#endif
