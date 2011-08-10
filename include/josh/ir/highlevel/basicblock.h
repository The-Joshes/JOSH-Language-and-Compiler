#ifndef __BASICBLOCK_H__
#define __BASICBLOCK_H__

#include <list>
#include <string>

#include "josh/ir/highlevel/value.h"
#include "josh/ir/highlevel/memoryuser.h"

class Function;
class Instruction;
class TerminatorInst;

/// class BasicBlock
/// BB represents a segment of Instructions that can be entered from the beginning or 
/// exited from the end, but cannot be entered or exited from any other point.
/**
 * A BB keeps track of all BB that potentially enter it (predecessors)
 * and all BB that it potentially enters (successors).
 * A valid BB must contain exactly ona TerminatorInst that is located as its 
 * last Instruction.  This property may not be valid during the creation and 
 * optimization of the BB, but must be true by the time the code is to be compiled.
 * The BaseType of a BasicBlock is always LABEL.
 */
class BasicBlock : public Value, public MemoryUser
{
public:
  static BasicBlock* Create(Function *parent, const std::string &name = "");
  
  std::list<BasicBlock*>::const_iterator&  getPreds() const; ///< @see preds
  std::list<BasicBlock*>::const_iterator&  getSuccs() const; ///< @see succs
  std::list<Instruction*>::const_iterator& getInsts() const; ///< @see insts
 
  void removeInstruction(int);
  void removeInstruction(Instruction*);

  Function* getParent();                         ///< @see parent

private:
  std::list<BasicBlock*> preds, succs; ///< The preceeding and succeeding BB
  std::list<Instruction*> insts;       ///< All Instructions in this BB
  Function *parent;                    ///< The function containing this BB.
};

#endif
