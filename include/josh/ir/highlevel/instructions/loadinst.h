#ifndef __LOADINST_H__
#define __LOADINST_H__

#include "josh/ir/highlevel/instruction.h"

class PointerType;

  /***************************************************************************
   *                           LoadInst                                      *
   ***************************************************************************/
/// class LoadInst
/// Loads a Value from memory.  
class LoadInst : public Instruction
{
public:
  /// Returns a new LoadInst that loads a Value from address.
  /// Asserts 0 if address's Type is not a pointer.
  /// Takes on the Type that address points to.
  static LoadInst* Create(Value *address, BasicBlock *insertAtEnd);

  Value* getAddress();     ///< returns the address to which this is loading from

  /// Sets the Value to which this instruction stores to.
  /// asserts 0 if the Value's Type is not a pointer.
  /// asserts 0 if the address' pointed to Type is different 
  /// from the instruction's Type.
  void setAddress(Value*); 

protected:
  LoadInst(PointerType *addressType, BasicBlock *insertAtEnd);

private:
  Value *address;
};

#endif
