#ifndef __STOREINST_H__
#define __STOREINST_H__

#include "josh/ir/highlevel/instruction.h"
  /***************************************************************************
   *                           StoreInst                                     *
   ***************************************************************************/
/// class StoreInst
/// Stores a value to memory.  All StoreInst are void Type, thus that they
/// cannot be used by subsequent Instructions.
class StoreInst : public Instruction
{
public:
  /// Returns a new StoreInst that stores Value toStore at location address.
  /// Asserts 0 if address's Type is not a pointer.
  /// Asserts 0 if the address's pointed to Type to is not equal to Value's Type.
  static StoreInst* Create(Value *toStore, Value *address, BasicBlock *insertAtEnd);

  /// Asserts 0 if the Value's Type is different than the address' pointed to Type.
  void setStoredValue(Value*);
  Value* getStoredValue(); ///< returns the Value which this is storing

  /// Asserts 0 if address's Type is not a pointer.
  /// Asserts 0 if the address' pointed to Type is different than toStore's Type.
  void setAddress(Value*);
  Value* getAddress();     ///< returns the address to which this is storing to

protected:
  StoreInst(BasicBlock *insertAtEnd);

private:
  Value *toStore;
  Value *address;
};
#endif
