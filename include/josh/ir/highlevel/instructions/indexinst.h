#ifndef __INDEXINST_H__
#define __INDEXINST_H__

#include "josh/ir/highlevel/instruction.h"

/// class IndexInst
/**
 *
 */
class IndexInst : public Instruction
{
public:
  static Value* IndexArray(Value *array, Value *index);
  static Value* IndexComplex(Value *complexValue, Value *index);

  Value *getIndex();
  Value *getBaseAddress();

protected:
  IndexInst(Value *baseAddress, Value *index);

private:
  Value *index, *baseAddress;
};

#endif
