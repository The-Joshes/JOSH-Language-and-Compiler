#ifndef __ALOCAINST_H__
#define __ALOCAINST_H__

#include "josh/ir/highlevel/instruction.h"

  /***************************************************************************
   *                          AllocaInst                                     *
   ***************************************************************************/
/// Allocates a piece of memory.  The actual Instruction is always of Type
/// PointerType and can be used as a reference for future LoadInst and StoreInst.
class AllocaInst : public Instruction
{
public:
  static AllocaInst* Create(Type *type, BasicBlock *insertAtEnd=NULL);

  /// arraySize must be of type Integer.
  static AllocaInst* CreateArray(Type *type, 
                                 Value *arraySize, 
                                 BasicBlock *insertAtEnd=NULL);

  /// Returns a Value of Type Integer detailing the amount of space allocated.
  /// If a non-array pointer was created, the array size will be a Constant with
  /// Type INTEGER and value 1.
  Value *getArraySize(); 
                        
protected:
  AllocaInst(Type *type, Value *arraySize, BasicBlock *insertAtEnd);

private:
  Value *arraySize; ///< @see getArraySize()
};
#endif
