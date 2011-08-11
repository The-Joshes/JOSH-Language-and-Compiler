#ifndef __INSTRUCTION_H__
#define __INSTRUCTION_H__

#include "josh/ir/highlevel/value.h"
#include "josh/ir/highlevel/memoryuser.h"

class BasicBlock;

/// class Instruction
/// Represents all Values whose value must be computed at run time
/**
 * Instruction is an abstract base class.
 */
class Instruction : public Value, public MemoryUser
{
public:
  BasicBlock* getParent() const;
  void setParent(BasicBlock*); ///< updates the old parent accordingly
  
  /// returns true if this Instruction's execution may have side effects, such
  /// as accessing memory, dividing by zero, etc.  An Instruction with side
  /// effects cannot safely be moved or removed from its sequence of 
  /// Instructions.
  bool mayHaveSideEffects() const;

protected:
  Instruction(Type*, BasicBlock *insertAtEnd,
              bool mayReadMemory = false, bool mayWriteMemory = false);

private:
  BasicBlock *parent;
};

#endif
