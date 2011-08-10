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
  BasicBlock* getParent();
  
  /// returns true if this Instruction's execution may have side effects, such
  /// as accessing memory, dividing by zero, etc.  An Instruction with side
  /// effects cannot safely be moved or removed from its sequence of 
  /// Instructions.
  bool mayHaveSideEffects() const;

  /// Returns an iterator containing all Values that this Value
  /// depends on/uses.
  std::list<Value*>::const_iterator& getUses() const;

  int getNumUses() const; ///< returns the number of Values that this uses

protected:
  Instruction(Type*, BasicBlock *insertAtEnd,
              bool mayReadMemory = false, bool mayWriteMemory = false);

  void addUse(Value*);     ///< adds Value to the uses list
  bool removeUse(Value*);  ///< if Value is in uses list, removes and returns true

private:
  BasicBlock *parent;
  std::list<Value*> uses;  ///< all Values this Instruction depends on

};

#endif
