#ifndef __CONSTANT_H__
#define __CONSTANT_H__

#include "josh/ir/value.h"

class Type;
class BinaryInst;

/// class Constant
/// represents all Values whos value and size are known at compile time
/**
 * Constant is a subclass of Value that represents a Value whos size and value
 * are known at compile time.
 */
class Constant : public Value
{
public:
  //  CreateEquivalentConstant(BinaryInst*)
  /// If BinaryInst->canBeComputedAtCompileTime(),
  /// this method returns a Constant that is equivalent to BinaryInst;
  /// if !BinaryInst->canBeComputedAtCompileTime(), 0 is asserted.
  static Constant* CreateEquivalentConstant(BinaryInst*);
protected:
};

#endif
