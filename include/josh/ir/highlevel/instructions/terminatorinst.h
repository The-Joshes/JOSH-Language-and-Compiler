#ifndef __TERMINATORINST_H__
#define __TERMINATORINST_H__

#include "josh/ir/highlevel/instruction.h"
  /***************************************************************************
   *                           TerminatorInst                                *
   ***************************************************************************/
/// class TerminatorInst
/// All Instructions that serve as terminators; that is, instructions that
/// disrupt the flow of control.
class TerminatorInst : public Instruction
{
public:
  enum TerminatorOp
  {
    RETURN, UNCONDITIONAL_BRANCH, CONDITIONAL_BRANCH
  };

  /// Create a new Conditional Branching Instruction.
  /// The condition's Type must be NUMERIC, else 0 is asserted.
  /// The Type of jumpToOnTrue and jumpToOnFalse must be LABEL, else 0 is asserted.
  /// If condition is evaluated at run time to be non-zero, jumpToOnTrue is branched to.
  /// Else, jumpToOnFalse is branched to.
  /// TerminatorOp's Type is set to void.
  static TerminatorInst* CreateConditionalBranch(Value *jumpToOnTrue,
                                                 Value *jumpToOnFalse,
                                                 Value *condition, 
                                                 BasicBlock *insertAtEnd);

  /// Create a new Unconditional Branching Instruction.
  /// The Type of jumpTo must be LABEL, else 0 is asserted.
  /// Flow of control always branches to jumpTo.
  /// TerminatorOp's Type is set to void.
  static TerminatorInst* CreateUnconditionalBranch(Value *jumpTo,
                                                   BasicBlock *insertAtEnd);

  /// Creates an Instruction to return from a function back to the original
  /// calling point.  If the parent Function returnVal's Type is different 
  /// than returnVal's Type, 0 is asserted.
  static TerminatorInst* CreateReturn(Value *returnVal, 
                                      BasicBlock *insertAtEnd);
  
  /// Creates an Instruction to return from a function back to the original
  /// calling point.  If the parent Function returnVal's Type is not Void, 
  /// 0 is asserted.
  static TerminatorInst* CreateVoidReturn(BasicBlock *insertAtEnd);

  TerminatorOp getTerminatorOp(); 

protected:
  TerminatorInst(TerminatorOp op, BasicBlock *insertAtEnd);

private:
  TerminatorOp op; 
  Value *jumpToOnTrue, *jumpToOnFalse;
  Value *condition;
  Value *returnVal;
};
#endif
