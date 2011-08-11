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
/// BB represents a sequence of Instructions that can be entered from the 
/// beginning or exited from the end, but cannot be entered or exited from any 
/// other point inside the sequence.
/**
 * A BB keeps track of all BB that potentially enter it (predecessors)
 * and all BB that it potentially enters (successors).
 * A valid BB must contain exactly one TerminatorInst that is located as its 
 * last Instruction.  This property may not be valid during the creation and 
 * optimization of the BB, but must be true by the time the code is to be 
 * compiled. The Type of a BasicBlock is always LABEL.
 */
class BasicBlock : public Value, public MemoryUser
{
public:
  static BasicBlock* Create(Function *parent, const std::string &name = "");
  
  std::list<BasicBlock*>::const_iterator&   getPreds() const; ///< @see preds
  std::list<BasicBlock*>::const_iterator&   getSuccs() const; ///< @see succs
  std::list<Instruction*>::const_iterator&  getInsts() const; ///< @see insts
 
  int getNumPreds() const;
  int getNumSuccs() const;
  int getNumInsts() const;

  void addInst(int, Instruction*); ///< asserts 0 if int is out of range
  Instruction* removeInst(int); ///< asserts 0 if int is out of range

  Function* getParent() const; ///< @see parent

protected:
  void addPred(BasicBlock*);
  void addSucc(BasicBlock*);
  
  void removePred(int);
  void removePred(BasicBlock*);
  void removeSucc(int);
  void removeSucc(BasicBlock*);

private:
  std::list<BasicBlock*> preds, succs; ///< The preceeding and succeeding BB
  std::list<Instruction*> insts;       ///< All Instructions in this BB
  Function *parent;                    ///< The function containing this BB.
};

#endif
