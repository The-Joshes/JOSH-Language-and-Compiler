#include "josh/ir/type.h"
#include "josh/ir/instructions.h"

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
  // as long as there are only arithmetic or binary ops
  // if op is not arithmetic it is compare, and vice versa
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
  if(allUsesConstant())
    return true;

  if(!lhs->isConstant())
  {
    BinaryInst *biLHS = dynamic_cast<BinaryInst*>(lhs);
    if(!(biLHS || biLHS->canBeComputedAtCompileTime()))
      return false;
  }
  
  if(!rhs->isConstant())
  {
    BinaryInst *biRHS = dynamic_cast<BinaryInst*>(rhs);
    if(!(biRHS || biRHS->canBeComputedAtCompileTime()))
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

const Value* BinaryInst::getLHS()
{
  return lhs;
}

const Value* BinaryInst::getRHS()
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
  
  /***************************************************************************
   *                           StoreInst                                     *
   ***************************************************************************/
  
  /***************************************************************************
   *                           LoadInst                                      *
   ***************************************************************************/
  
  /***************************************************************************
   *                           AllocaInst                                    *
   ***************************************************************************/
