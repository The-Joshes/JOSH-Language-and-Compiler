#ifndef __INSTRUCTION_H__
#define __INSTRUCTION_H__

#include "josh/ir/value.h"

/// class Instruction
/// represents all Values which must be computed at run time
/**
 * Instruction is a subclass of Value that represents a Value whos value
 * and/or size are not known at compile time, and thus must be computed
 * at run time.
 */
class Instruction : public Value
{
public:
  enum InstCategory
  {
    BINARY, TERMINATOR, CALL, PHINODE, STORE, LOAD, ALLOCA
  };

  InstCategory getInstCategory();

protected:
  // Constructor
  /// requires the instruction's type and its category
  Instruction(Type*, InstCategory);

private:
  InstCategory instCat;
};

#endif