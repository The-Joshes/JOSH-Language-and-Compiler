#ifndef __INSTRUCTION_H__
#define __INSTRUCTION_H__

#include "josh/ir/highlevel/user.h"

class BasicBlock;

/// class Instruction
/// Represents all Users whose value must be computed at run time
/**
 * Instruction is an abstract base class.
 * Instruction is a subclass of User that represents a Value whos value
 * and/or size are not known at compile time, and thus must be computed
 * at run time.
 */
class Instruction : public User
{
public:
  /// This function to set the Inst's parent does NOT insert it into the BB
  /// or remove any old parent dependencies.
  virtual void setParent(BasicBlock*);
  BasicBlock* getParent();

protected:
  Instruction(Type*, BasicBlock *insertAtEnd);

private:
  BasicBlock *parent;
};

#endif
