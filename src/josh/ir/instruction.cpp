#include "josh/ir/instruction.h"

#include <assert.h>

//  Constructor
Instruction::Instruction(Type *type, InstCategory instCategory)
  : Value(type), instCat(instCategory)
{
}

//  getInstCategory()
Instruction::InstCategory Instruction::getInstCategory()
{
  return instCat;
}
