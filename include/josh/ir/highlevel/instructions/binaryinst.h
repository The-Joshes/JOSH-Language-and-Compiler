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
  /// This Type must be ArithmeticType, else 0 is asserted.
  static ArithmeticInst* CreateADD(Value *lhs, Value *rhs, 
                                   BasicBlock *insertAtEnd); ///< Creates a new Add Instruction
  static ArithmeticInst* CreateSUB(Value *lhs, Value *rhs, 
                                   BasicBlock *insertAtEnd); ///< Creates a new Substraction Instruction
  static ArithmeticInst* CreateMUL(Value *lhs, Value *rhs, 
                                   BasicBlock *insertAtEnd); ///< Creates a new Multiplication Instruction
  static ArithmeticInst* CreateDIV(Value *lhs, Value *rhs, 
                                   BasicBlock *insertAtEnd); ///< Creates a new Division Instruction
  static ArithmeticInst* CreateREM(Value *lhs, Value *rhs, 
                                   BasicBlock *insertAtEnd); ///< Creates a new Remainder Instruction

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
  /// This Type must be NumericType, else 0 is asserted.
  static CompareInst* CreateEQ(Value *lhs, Value *rhs,
                               BasicBlock *insertAtEnd);
  static CompareInst* CreateNE(Value *lhs, Value *rhs,
                               BasicBlock *insertAtEnd);
  static CompareInst* CreateLT(Value *lhs, Value *rhs,
                               BasicBlock *insertAtEnd);
  static CompareInst* CreateLTE(Value *lhs, Value *rhs,
                                BasicBlock *insertAtEnd);
  static CompareInst* CreateGT(Value *lhs, Value *rhs,
                               BasicBlock *insertAtEnd);
  static CompareInst* CreateGTE(Value *lhs, Value *rhs,
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
    NOT,         /*!< Logical not */
  };
 
  /// lhs must have a ArithmeticType and rhs must have have an Integer Type.
  /// Else, 0 is asserted.
  static LogicalInst* CreateSHL(Value *lhs, Value *rhs,
                                BasicBlock *insertAtEnd);
  /// lhs must have a ArithmeticType and rhs must have have an Integer Type.
  /// Else, 0 is asserted.
  static LogicalInst* CreateSHR(Value *lhs, Value *rhs,
                                BasicBlock *insertAtEnd);
  /// lhs and rhs must both be the same ArithmeticType, else 0 is asserted.
  static LogicalInst* CreateAND(Value *lhs, Value *rhs,
                                BasicBlock *insertAtEnd);
  /// lhs and rhs must both be the same ArithmeticType, else 0 is asserted.
  static LogicalInst* CreateOR(Value *lhs, Value *rhs,
                               BasicBlock *insertAtEnd);
  /// lhs and rhs must both be the same ArithmeticType, else 0 is asserted.
  static LogicalInst* CreateXOR(Value *lhs, Value *rhs,
                                BasicBlock *insertAtEnd);
  
  /// Lhs must have an ArithmeticType, else 0 is asserted.
  static LogicalInst* CreateNEG(Value *lhs, BasicBlock *insertAtEnd);
  
  /// Lhs must have an ArithmeticType, else 0 is asserted.
  static LogicalInst* CreateNOT(Value *lhs, BasicBlock *insertAtEnd);

  LogicalOp getOp() const;

protected:
  LogicalInst(Value *lhs, Value *rhs, LogicalOp op, BasicBlock*);

private:
  LogicalOp op;
};

#endif
