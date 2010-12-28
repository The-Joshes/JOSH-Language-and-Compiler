#ifndef __CONSTANT_H__
#define __CONSTANT_H__

#include "utils/vector.h"

#include "josh/ir/value.h"

class Type;

//! class Constant
//! represents all Values whos value and size are known at compile time
/*!
 * Constant is a subclass of Value that represents a Value whos size and value
 * are known at compile time.
 */

class Constant : public Value
{
public:
  static Constant* CreateEquivalentConstant(Value*);

protected:
};

#endif
