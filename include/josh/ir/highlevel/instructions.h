#ifndef __INSTRUCTIONS_H__
#define __INSTRUCTIONS_H__

#include "josh/ir/instruction.h"

#include <cstring> // for NULL

class BasicBlock;
class PointerType;

  /***************************************************************************
   *                           BinaryInst                                    *
   ***************************************************************************/
/// Instructions of the form (val) = (lhs) op (rhs)
class BinaryInst : public Instruction 
{
public: 
  /***************************************************************************
   *                           Static members                                *
   ***************************************************************************/
  
  //  enum BinaryOp
  /// List of binary operators.\n
  /// Arithmetic: ADD, SUBTRACT, MULTIPLY, DIVIDE.\n
  /// Compare: LESS_THAN, GREATER_THAN, LESS_OR_EQUAL, GREATER_OR_EQUAL, EQUAL, NOT_EQUAL.
  /// Compare Insts always have a Type of Integer, regardless of the Type of its operators.
  /// To see a BinaryInst's operator Type, @see getOpType()
  enum BinaryOp
  {
    ADD,                /*!< A = (X + Y)  */  
    SUBTRACT,           /*!< A = (X - Y)  */  
    MULTIPLY,           /*!< A = (X * Y)  */  
    DIVIDE,             /*!< A = (X / Y)  */  
    LESS_THAN,          /*!< A = (X < Y)  */  
    GREATER_THAN,       /*!< A = (X > Y)  */  
    LESS_OR_EQUAL,      /*!< A = (X <= Y) */  
    GREATER_OR_EQUAL,   /*!< A = (X >= Y) */  
    EQUAL,              /*!< A = (X == Y) */  
    NOT_EQUAL           /*!< A = (X != Y) */  
  };

  static bool isOpArithmetic(BinaryOp op); ///< returns true if op is arithmetic;
                                           ///< returns false otherwise
  static bool isOpCompare(BinaryOp op);    ///< returns true if op is compare;
                                           ///< returns false otherwise

  //  Create(BinaryOp, Value*, Value*, BasicBlock*)
  /// Create a new BinaryInst of the form (val) = (lhs) op (rhs).
  /// If lhs and rhs do not have the same BaseType, 0 is asserted.
  /// If the op is arithmetic, the new BinaryInst has the same BaseType as lhs and rhs.
  /// If the op is a compare, the new BinaryInst has a BaseType of Integer.
  static BinaryInst* Create(BinaryOp op, Value *lhs, Value *rhs, BasicBlock *insertAtEnd=NULL);

  /***************************************************************************
   *                           Member functions                              *
   ***************************************************************************/
  
  //  canBeComputedAtCompileTime()
  /// returns true if this Instruction's value can be computed at compile time,
  /// returns false otherwise.
  bool canBeComputedAtCompileTime();

  bool isArithmetic(); ///< returns true if this BinaryInst is arithmetic
  bool isCompare();    ///< returns true if this BinaryInst is compare 

  BinaryOp getBinaryOp(); ///< returns this instruction's op
  Type *getOpType();      ///< returns the type of the inst's operators

  Value *getLHS(); ///< returns the Value corresponding to the lhs of the BinaryInst
  Value *getRHS(); ///< returns the Value corresponding to the rhs of the BinaryInst

  void setLHS(Value*); ///< changes the lhs Value.
                       ///< asserts 0 if the new Value has a differing Type.
  void setRHS(Value*); ///< changes the rhs Value.
                       ///< asserts 0 if the new Value has a differing Type.
protected:
  // Constructor
  /// Requires the instruction's op, type, and operatorType
  BinaryInst(BinaryOp, Type *type, Type *operatorType, BasicBlock *insertAtEnd);

private:
  bool arithmetic;
  BinaryOp op; ///< @see getBinaryOp()
  Type *opType; ///< Type of the operators
  Value *lhs, *rhs; ///< lhs and rhs values of the binary instruction
};

  /***************************************************************************
   *                           TerminatorInst                                *
   ***************************************************************************/
/// All Instructions that serve as terminators; that is, instructions that
/// disrupt the flow of control.
class TerminatorInst : public Instruction
{
public:
  //  enum TerminatorOps
  /// Ops available for a TerminatorInst
  enum TerminatorOp
  {
    RETURN, UNCONDITIONAL_BRANCH, CONDITIONAL_BRANCH
  };

  //  CreateBranch(BasicBlock*, BasicBlock*, Value*, BasicBlock*)
  /// Create a new Branching Instruction.
  /// If jumpToOnFalse is NULL or condition is NULL, an unconditional branch is created.
  /// Otherwise, a conditional branch is created.
  /// A non-NULL condition's Type must be Integer, else 0 is asserted.
  /// If condition is NULL or evaluated at run time to be non-zero, BB jumpToOnTrue is branched to.
  /// Else if condition is evaluated at run time to be zero, BB jumpToOnFalse is branched to.
  /// TerminatorOp's Type is set to void.
  static TerminatorInst* CreateBranch(BasicBlock *jumpToOnTrue,
                                      BasicBlock *jumpToOnFalse = NULL,
                                      Value *condition = NULL, 
                                      BasicBlock *insertAtEnd=NULL);

  //  CreateReturn(Value*, BasicBlock*)
  /// Creates an Instruction to return from a CallInst.
  /// If returnVal is NULL, TerminatorInst's Type is set to void.
  static TerminatorInst* CreateReturn(Value* returnVal = NULL, BasicBlock *insertAtEnd=NULL);

  TerminatorOp getTerminatorOp(); ///< returns this instruction's op

protected:
  TerminatorInst(TerminatorOp op, BasicBlock *jumpToOnTrue, BasicBlock *jumpToOnFalse,
                 Value *condition, Value *returnVal, BasicBlock *insertAtEnd);

private:
  TerminatorOp op; ///< @see getTerminatorOp()
  BasicBlock *jumpToOnTrue, *jumpToOnFalse;
  Value *condition;
  Value *returnVal;
};

  /***************************************************************************
   *                           CallInst                                      *
   ***************************************************************************/
/// Instruction that calls a function.  
class CallInst : public Instruction
{
public:
private:
};

  /***************************************************************************
   *                           PhiNode                                       *
   ***************************************************************************/
/// A PhiNode Instruction ('phi function') makes SSA form possible by
/// allowing a Value to take value based on where flow of control
/// came from.  For a given PhiNode, every successor basic block to the
/// basic block the PhiNode is in must be represented by a (path, value) pair.
class PhiNode : public Instruction
{
public:
  //  Create(Iterator<Value*>, Iterator<BasicBlock*>, BasicBlock*)
  /// Creates a PhiNode that determines value based on flow.
  /// All Values in values must have the same Type, else 0 is asserted.
  /// The PhiNode's Value is equivalent to the Type of any of the values.
  static PhiNode* Create(Iterator<Value*> &values, 
                         Iterator<BasicBlock*> &paths, 
                         BasicBlock *insertAtEnd=NULL);

  //  CreateEmpty(Type*, BasicBlock*)
  /// Creates an empty PhiNode to be filled in later.  
  /// This Instruction is not considered valid until all appropriate paths to
  /// the PhiNode's containing basic block are filled in with a (path, value) pair.
  static PhiNode* CreateEmpty(Type *type, BasicBlock *insertAtEnd=NULL);

  //  getNumPairs()
  /// returns the number of (Value*, BasicBlock*) pairs that 
  /// exist for this PhiNode
  int getNumPairs();

  //  getNthValue(int)
  /// Returns the Value located at position int in the list of incoming pairs.
  /// Asserts 0 if int is out of range.
  Value* getNthValue(int);

  //  setNthValue(int, Value*)
  /// Sets the Value located at position int in the list of incoming pairs.
  /// Asserts 0 if Value is not the same Type as the PhiNode.
  /// Asserts 0 if int is out of range.
  void setNthValue(int, Value*);

  //  getNthBlock(int)
  /// Returns the BasicBlock located at position int in the list of incoming pairs.
  /// Asserts 0 if int is out of range.
  BasicBlock* getNthBlock(int);
  
  //  setNthBlock(int, BasicBlock*)
  /// Sets the BasicBlock located at position int in the list of incoming pairs.
  /// Asserts 0 if int is out of range.
  void setNthBlock(int, BasicBlock*);

  //  addPair(Value*, BasicBlock*)
  /// adds the pair of (Value*, BasicBlock*) to the list of incoming pairs.
  /// Asserts 0 if Value* is not the same Type as the PhiNode
  void addPair(Value*, BasicBlock*);

  //  removeNthPair(int)
  /// detaches the pair at location int from the list of incoming pairs.
  void removeNthPair(int);
  
protected:
  //  Constructor
  PhiNode(Type *type, BasicBlock *insertAtEnd);

private:
  //  pairs
  /// all pairs of Values and BasicBlocks representing each Value
  /// this PhiNode could take on depending on the flow of control
  josh::List< std::pair<Value*, BasicBlock*> > pairs;
};

  /***************************************************************************
   *                           StoreInst                                     *
   ***************************************************************************/
/// Stores a value to memory.  All StoreInst are void Type, thus that they
/// cannot be used by subsequent Instructions.
class StoreInst : public Instruction
{
public:
  //  Create(Value *toStore, Value *address, BasicBlock*)
  /// Returns a new StoreInst that stores Value toStore at location address.
  /// Asserts 0 if address's Type is not a pointer.
  /// Asserts 0 if the Type address's Type points to is not equal to Value's Type.
  static StoreInst* Create(Value *toStore, Value *address, BasicBlock *insertAtEnd=NULL);

  Value* getStoredValue(); ///< returns the Value which this is storing
  void setStoredValue(Value*);
  Value* getAddress();     ///< returns the address to which this is storing to
  void setAddress(Value*);

protected:
  //  Constructor
  StoreInst(PointerType *addressType, BasicBlock *insertAtEnd);

private:
  Value *toStore;
  Value *address;
  PointerType  *addressType;

};

  /***************************************************************************
   *                           LoadInst                                      *
   ***************************************************************************/
/// Loads a Value from memory.  
class LoadInst : public Instruction
{
public:
  //  Create(Value*, BasicBlock*)
  /// Returns a new LoadInst that loads a Value from address.
  /// Asserts 0 if address's Type is not a pointer.
  /// Takes on the Type that address points to.
  static LoadInst* Create(Value *address, BasicBlock *insertAtEnd=NULL);

  Value *getAddress();     ///< returns the address to which this is loading from
  void setAddress(Value*); ///< sets the Value to which this instruction stores to
                           ///< asserts 0 if the Value's Type is not a pointer
                           ///< asserts 0 if the address' pointed to Type is different from the instruction's Type

protected:
  //  Constructor
  LoadInst(PointerType *addressType, BasicBlock *insertAtEnd);

private:
  Value *address;
};

  /***************************************************************************
   *                          AllocaInst                                     *
   ***************************************************************************/
/// Allocates a piece of memory.
class AllocaInst : public Instruction
{
public:
  //  CreateArray(Type*, Value*, BasicBlock*)
  /// Creates an Instruction to allocate a piece of memory.
  /// arraySize must be of type Integer.
  /// The Value of AllocaInst is a pointer which points to the allocated space.
  static AllocaInst* CreateArray(Type *type, Value *arraySize, BasicBlock *insertAtEnd=NULL);

  //  Create(Type*, BasicBlock*)
  /// Creates an Instruction to allocate a piece of memory.
  /// The Value of AllocaInst is a pointer which points to the allocated space.
  static AllocaInst* Create(Type *type, BasicBlock *insertAtEnd=NULL);

  //  getArraySize()
  /// Returns a Value of Type Integer detailing the amount of space allocated.
  /// If a non-array pointer was created, the array size will be a Constant of value 1
  Value *getArraySize(); 
                        
protected:
  AllocaInst(Type *type, Value *arraySize, BasicBlock *insertAtEnd);

private:
  Value *arraySize; ///< @see getArraySize()
};

#endif
