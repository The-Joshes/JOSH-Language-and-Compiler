#ifndef __BINARYINST_H__
#define  __BINARYINST_H__

#include "josh/ir/highlevel/instruction.h"


  /***************************************************************************
   *                           BinaryInst                                    *
   ***************************************************************************/
/// class BinaryInst
/// Instructions of the form (val) = (lhs) op (rhs)
/**
 * BinaryInst is an abstract base class.
 */
class BinaryInst : public Instruction 
{
public: 
  /// returns true if this Instruction's value can be computed at compile time,
  /// returns false otherwise.
  bool canBeComputedAtCompileTime();

  Value *getLHS(); ///< returns the Value corresponding to the lhs of the BinaryInst
  Value *getRHS(); ///< returns the Value corresponding to the rhs of the BinaryInst

  /// changes the lhs Value, asserting 0 if the new Value has a differing Type from the original LHS.
  virtual void setLHS(Value*); 

  /// changes the lhs Value, asserting 0 if the new Value has a differing Type from the original RHS.
  virtual void setRHS(Value*); 
  
protected:
  BinaryInst(Value *lhs, Value *rhs, BasicBlock *insertAtEnd);

private:
  Value *lhs, *rhs; 
};

/// class ArithmeticInst
/// Represents algebraic operations.  
class ArithmeticInst : public BinaryInst
{
public:
  enum ArithmeticOp
  {
    ADD, SUB, MUL, DIV,
    REM /*!< REMainder finds the remainder of the operation (lhs / rhs) */
  };

  /// Both lhs and rhs must have the same Type, else 0 is asserted.
  /// This Type must be NumericType, else 0 is asserted.
  static ArithmeticInst* Create(Value *lhs, Value *rhs,
                                ArithmeticOp op,
                                BasicBlock *insertAtEnd);

  ArithmeticOp getOp() const;

protected:
  ArithmeticInst(Value *lhs, Value *rhs, ArithmeticOp, BasicBlock*);

private:
  ArithmeticOp op;
};

/// class CompareInst
/// Compares two values, storing the result as 0 (false) or not 0 (true).
/// Commonly used as a condition for TerminatorInst::CreateConditionalBranch()
class CompareInst : public BinaryInst
{
public:
  enum CompareOp
  {
    EQ, NE,  /*!< Equal or not equal to */
    LT, LTE, /*!< Less than or less than equal to */
    GT, GTE  /*!< Greater than or greater than equal to */
  };
  
  /// Both lhs and rhs must have the same Type, else 0 is asserted.
  /// This Type must either be NumericType or PointerType, else 0 is asserted.
  static CompareInst* Create(Value *lhs, Value *rhs,
                             CompareOp op,
                             BasicBlock *insertAtEnd);
  CompareOp getOp() const;

protected:
  CompareInst(Value *lhs, Value *rhs, CompareOp op, BasicBlock*);

private:
  CompareOp op;
};

class LogicalInst : public BinaryInst
{
public:
  enum LogicalOp
  {
    SHL, SHR,    /*!< Shift left or shift right */
    AND, OR, XOR,
    NEG,         /*!< Two's complement negation */
    NOT          /*!< Logical not */
  };
 
  /// If op = SHL or SHR, lhs must have a Numeric Type and rhs must have have an Integer Type.
  /// If op = AND, OR, or XOR, lhs and rhs must both be the same Numeric Type.
  /// If op = NEG or NOT, lhs must have a Numeric Type and rhs must be NULL.
  static LogicalInst* Create(Value *lhs, Value *rhs,
                             LogicalOp op,
                             BasicBlock *insertAtEnd);

protected:
  LogicalInst(Value *lhs, Value *rhs, LogicalOp op, BasicBlock*);

private:
  LogicalOp op;
};

#endif
