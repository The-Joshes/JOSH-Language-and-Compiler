#ifndef __CALLINST_H__
#define __CALLINST_H__

#include <list>

#include "josh/ir/highlevel/instruction.h"
class Function;

  /***************************************************************************
   *                           CallInst                                      *
   ***************************************************************************/
/// Instruction that calls a function.  
class CallInst : public Instruction
{
public:
  /// Create a CallInst
  static CallInst* Create(Function *toCall, 
                          std::list<Value*> args,
                          BasicBlock *insertAtEnd);
 
  /// Create a CallInst to a Function with an empty args list.
  static CallInst* Create(Function *toCall, 
                          BasicBlock *insertAtEnd);
 
  /// Sets the argument at position 0 in the CallInst to be Value.
  /// Asserts 0 if the index is out of bounds.
  /// Asserts 0 if the Value has an incorrect Type for the Function
  /// at position index.
  void setArg(int, Value*);
  Value* getArg(int);
  
  /// Sets a new Function to be called.
  /// If the new Function does not have an equivalent FunctionType
  /// to the old one, 0 is asserted.
  void setFunction(Function*);
  Function *getFunction();

protected:
  CallInst(Function *toCall, BasicBlock *insertAtEnd);

private:
  Function *beingCalled;
};
#endif
