#ifndef __CONSTANT_H__
#define __CONSTANT_H__

#include "utils/vector.h"

#include "josh/ir/value.h"

class Type;
/// template <typename T>
/// class Constant<T>
/// represents all Values whos value and size are known at compile time
/**
 * Constant is a subclass of Value that represents a Value whos size and value
 * are known at compile time.
 */
class Constant : public Value
{
public:
  //  CreateEquivalentConstant(Value*)
  /// if Value canBeComputedAtCompileTime()
  /// this method returns a Constant that is equivalent to Value.  
  /// If Value can not be computed at compile time, 0 is asserted.
  static Constant* CreateEquivalentConstant(Value*);
protected:
};

#endif
