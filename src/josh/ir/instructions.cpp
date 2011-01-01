#include "josh/ir/type.h"
#include "josh/ir/instructions.h"

#include "utils/list.h"

#include <cstring> // for NULL
#include "assert.h"


  /***************************************************************************
   *                           BinaryInst                                    *
   ***************************************************************************/

bool BinaryInst::isOpArithmetic(BinaryOp op)
{
  return (op == ADD) || 
         (op == SUBTRACT) || 
         (op == MULTIPLY) || 
         (op == DIVIDE);
}

bool BinaryInst::isOpCompare(BinaryOp op)
{
  // As long as there are only two different kinds of ops,
  // the op is arithmetic if it is not compare, and vice versa.
  return !BinaryInst::isOpArithmetic(op);
}

BinaryInst* BinaryInst::Create(BinaryOp op, Value *lhs, Value *rhs)
{
  // ensure lhs and rhs have the same type
  Type *t1 = lhs->getType(), *t2 = rhs->getType();
  if(!t1->equals(t2))
    assert(0 && "Cannot create a BinaryInst from two values of different types!");

  // the opType is the same type of lhs and rhs
  Type *opType = t1;
  
  // find the BinaryInst's type
  Type *instType;

  if(BinaryInst::isOpArithmetic(op)) // arithmetic have the same type as their op
    instType = opType;
  else if(BinaryInst::isOpCompare(op)) // compare have int type
    assert(0 && "CompareOps not yet implemented");
  else
    assert(0 && "Unknown op type in creating new BinaryInst");

  // create the new BinaryInst
  BinaryInst *bi = new BinaryInst(op, instType, opType);
  bi->setLHS(lhs);
  bi->setRHS(rhs);

  return bi;
}

bool BinaryInst::canBeComputedAtCompileTime()
{
  /// To calculate a BinaryInst at compile time, both the LHS and RHS must 
  /// either be Constant or can be computed at compile time themselves.

  if(!lhs->isConstant())
  {
    BinaryInst *biLHS = dynamic_cast<BinaryInst*>(lhs);
    if(!(biLHS && biLHS->canBeComputedAtCompileTime()))
      return false;
  }
  
  if(!rhs->isConstant())
  {
    BinaryInst *biRHS = dynamic_cast<BinaryInst*>(rhs);
    if(!(biRHS && biRHS->canBeComputedAtCompileTime()))
      return false;
  }

  return true;
}

bool BinaryInst::isArithmetic()
{
  return arithmetic;
}

bool BinaryInst::isCompare()
{
  return !arithmetic;
}

BinaryInst::BinaryOp BinaryInst::getBinaryOp()
{
  return op;
}

Value* BinaryInst::getLHS()
{
  return lhs;
}

Value* BinaryInst::getRHS()
{
  return rhs;
}

void BinaryInst::setLHS(Value *val)
{
  if(!this->getOpType()->equals(val->getType()))
    assert(0 && "Cannot use an operand that has a different type than the op type");

  if(this->lhs)
    this->removeUse(this->lhs);
  
  this->lhs = val;
  this->addUse(val);
}

void BinaryInst::setRHS(Value *val)
{
  if(!this->getOpType()->equals(val->getType()))
    assert(0 && "Cannot set an operand as a different type than the op type");

  if(this->rhs)
    this->removeUse(this->rhs);
  
  this->rhs = val;
  this->addUse(val);
}

BinaryInst::BinaryInst(BinaryOp newOp, Type* instType, Type *operatorType)
  : Instruction(instType, Instruction::BINARY), 
    op(newOp), opType(operatorType), lhs(NULL), rhs(NULL)
{
  arithmetic = BinaryInst::isOpArithmetic(op);
}

  /***************************************************************************
   *                           TerminatorInst                                *
   ***************************************************************************/
  
  /***************************************************************************
   *                           CallInst                                      *
   ***************************************************************************/
  
  /***************************************************************************
   *                           PhiNode                                       *
   ***************************************************************************/
PhiNode* PhiNode::Create(josh::Iterator<Value*> &values, josh::Iterator<BasicBlock*> &paths)
{
  Value *val        = values.next();
  BasicBlock *block = paths.next();
  PhiNode *pi       = new PhiNode(val->getType());

  // Fill the PhiNode with (Value*, BasicBlock*) pairs
  while(values.hasNext() && paths.hasNext())
  {
    pi->addPair(val, block);
    val   = values.next();
    block = paths.next();
  }

  // if there is a Value or BasicBlock remaining, we were given an unequal
  // number of pairs!
  if(values.hasNext() || paths.hasNext())
    assert(0 && "There must be an equal number of values and paths to create a PhiNode!");
}

PhiNode* PhiNode::CreateEmpty(Type *type)
{
  PhiNode *pi = new PhiNode(type);
  return pi;
}

int PhiNode::getNumPairs()
{
  assert(0 && "Not implemented yet!");
}

Value* PhiNode::getNthValue(int n)
{
  assert(0 && "Not implemented yet!");
}

void PhiNode::setNthValue(int n, Value *val)
{
  assert(0 && "Not implemented yet!");
}

BasicBlock* PhiNode::getNthBlock(int n)
{
  assert(0 && "Not implemented yet!");
}

void PhiNode::setNthBlock(int n, BasicBlock *bb)
{
  assert(0 && "Not implemented yet!");
}

void PhiNode::addPair(Value *val, BasicBlock *path)
{
  // make sure the type of this new pair is kosher
  Type *t1 = val->getType();
  if(!t1->equals(getType()))
    assert(0 && "Can't add a Value of a different Type to a PhiNode!");

  std::pair<Value*, BasicBlock*> newPair (val, path);
  pairs.append(newPair);
  addUse(val); // don't forget, we now use a new Value
}

void PhiNode::removeNthPair(int n)
{
  assert(0 && "Not implemented yet!");
}

PhiNode::PhiNode(Type *type)
  : Instruction(type, Instruction::PHINODE)
{
}

  /***************************************************************************
   *                           StoreInst                                     *
   ***************************************************************************/
StoreInst* StoreInst::Create(Value *toStore, Value *address)
{
  Type *type = address->getType();
  PointerType *pt = dynamic_cast<PointerType*>(type);
  if(!pt)
    assert(0 && "Cannot make a StoreInst with a non-pointer address!");

  StoreInst *si = new StoreInst(pt);
  si->setStoredValue(toStore);
  si->setAddress(address);

  return si;
}

Value* StoreInst::getStoredValue()
{
  return toStore;
}

void StoreInst::setStoredValue(Value *newStore)
{
  Type  *oldType = addressType->getPointedToType();
  
  // ensure address points to the same type that toStore is
  Type *newType = newStore->getType();
  if(!newType->equals(oldType))
    assert(0 && "StoreInst cannot use an address which points to a different\
                 Type than its stored value's Type!");

  if(toStore)
    removeUse(toStore);

  toStore = newStore;
  addUse(newStore);
}

Value* StoreInst::getAddress()
{
  return address;
}

void StoreInst::setAddress(Value *newAddr)
{
  // ensure address is a pointer
  Type *newType = newAddr->getType();
  PointerType *pointer = dynamic_cast<PointerType*>(newType);
  if(!pointer)
    assert(0 && "StoreInst cannot use an address that isn't a pointer!");

  // ensure address points to correct Type
  if(!newType->equals(addressType))
    assert(0 && "Cannot change the Type which StoreInst uses as an address!");

  if(newAddr)
    removeUse(address);

  address = newAddr;
  addUse(newAddr);
}

StoreInst::StoreInst(PointerType *addrType)
  : Instruction(Type::GetVoidType(), Instruction::STORE),
    toStore(NULL), address(NULL),
    addressType(addrType)
{
}

  /***************************************************************************
   *                           LoadInst                                      *
   ***************************************************************************/
LoadInst* LoadInst::Create(Value *address)
{
  Type *type = address->getType();
  PointerType *pt = dynamic_cast<PointerType*>(type);
  if(!pt)
    assert(0 && "Cannot make a LoadInst with a non-pointer address Type!");

  LoadInst *li = new LoadInst(pt);
  li->setAddress(address);

  return li;
}

Value* LoadInst::getAddress()
{
  return address;
}

void LoadInst::setAddress(Value *newAddr)
{
  // ensure address is a pointer
  Type *oldType = address->getType();
  Type *newType = newAddr->getType();
  PointerType *pointer = dynamic_cast<PointerType*>(newType);
  if(!pointer)
    assert(0 && "StoreInst cannot use an address that isn't a pointer!");

  // ensure address points to correct Type
  if(!newType->equals(oldType))
    assert(0 && "Cannot change the Type which StoreInst uses as an address!");

  if(address)
    removeUse(address);

  address = newAddr;
  addUse(newAddr);
}

LoadInst::LoadInst(PointerType *addrType)
  : Instruction(addrType->getPointedToType(), Instruction::LOAD),
    address(NULL)
{
}

  /***************************************************************************
   *                           AllocaInst                                    *
   ***************************************************************************/
AllocaInst* AllocaInst::Create(Type *type)
{
  AllocaInst *ai = new AllocaInst(type);
  return ai;
}

AllocaInst* AllocaInst::CreateArray(Type *type, Value *arraySize)
{
  AllocaInst *ai = new AllocaInst(type, arraySize);
  return ai;
}

Value* AllocaInst::getArraySize()
{
  return arraySize;
}

AllocaInst::AllocaInst(Type *type, Value *newSize)
  : Instruction(type, Instruction::ALLOCA)
{
  if(newSize)
  {
    // ensure size is of type integer
    Type *arrayType = arraySize->getType();
    if(arrayType->getBaseType() != Type::INTEGER)
      assert(0 && "Array size must be integer!");
  
    // this now depends on the size, so add it as a use
    arraySize = newSize;
    addUse(newSize);
  }
}

int main()
{
  return 0;
}
