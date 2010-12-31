#ifndef __INSTRUCTIONS_H__
#define __INSTRUCTIONS_H__

#include "josh/ir/instruction.h"

class BasicBlock;

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

  //  CreateBinaryInst(BinaryOp, Value*, Value*)
  /// Create a new BinaryInst of the form (val) = (lhs) op (rhs).
  /// If lhs and rhs do not have the same BaseType, 0 is asserted.
  /// If the op is arithmetic, the new BinaryInst has the same BaseType as lhs and rhs.
  /// If the op is a compare, the new BinaryInst has a BaseType of Integer.
  static BinaryInst* Create(BinaryOp op, Value *lhs, Value *rhs);

  /***************************************************************************
   *                           Member functions                              *
   ***************************************************************************/
  
  //  canBeComputedAtCompileTime()
  /// returns true if this Instruction's value can be computed at compile time,
  /// returns false otherwise.
  /// A BinaryInst can be computed at compile time if all of its uses are Constant
  /// and the Instruction's execution is guaranteed not to trap.
  bool canBeComputedAtCompileTime();

  bool isArithmetic(); ///< returns true if this BinaryInst is arithmetic
  bool isCompare();    ///< returns true if this BinaryInst is compare 

  BinaryOp getBinaryOp(); ///< returns this instruction's op
  Type *getOpType();      ///< returns the type of the operator

  const Value *getLHS(); ///< returns the Value corresponding to the lhs of the BinaryInst
  const Value *getRHS(); ///< returns the Value corresponding to the rhs of the BinaryInst

  void setLHS(Value*); ///< changes the lhs Value.
                       ///< asserts 0 if the new Value has a differing Type.
  void setRHS(Value*); ///< changes the rhs Value.
                       ///< asserts 0 if the new Value has a differing Type.
protected:
  // Constructor
  /// Requires the instruction's op, type, and operatorType
  BinaryInst(BinaryOp, Type *type, Type *operatorType);

private:
  bool arithmetic;
  BinaryOp op; ///< @see getBinaryOp()
  Type *opType; ///< Type of the operators
  Value *lhs, *rhs; ///< lhs and rhs values of the binary instruction
};

  /***************************************************************************
   *                           TerminatorInst                                *
   ***************************************************************************/
/// All Instructions that serve as terminators; that is, 
/// disrupt the flow of control.
class TerminatorInst : public Instruction
{
public:
  //  enum TerminatorOps
  /// Ops available for a TerminatorInst
  enum TerminatorOp
  {
    RETURN, BRANCH
  };
private:
};

  /***************************************************************************
   *                           CallInst                                      *
   ***************************************************************************/
/// Instruction that calls a function
class CallInst : public Instruction
{
public:
private:
};

  /***************************************************************************
   *                           PhiNode                                       *
   ***************************************************************************/
/// A Phi Instruction ('function') makes SSA form possible by
/// allowing a Value to take value based on where flow of control
/// came from.  For a given PhiNode, every successor basic block to the
/// PhiNode's parent basic block must be represented by a (path, value) pair.
class PhiNode : public Instruction
{
public:
  //  Create(Iterator<Value*>, Iterator<BasicBlock*>)
  /// Creates a PhiNode that determines value based on flow.
  /// All Values in values must have the same Type, else 0 is asserted.
  /// The PhiNode's Value is equivalent to the Type of any of the values.
  static PhiNode* Create(Iterator<Value*> &values, Iterator<BasicBlock*> &paths);

  //  CreateEmpty(Type*)
  /// Creates an empty PhiNode to be filled in later.  
  /// Not a valid Instruction to PhiNode's parent block (see class description).
  static PhiNode* CreateEmpty(Type *type);

  //  getNumPairs()
  /// returns the number of (Value*, BasicBlock*) pairs that 
  /// exist for this PhiNode
  int getNumPairs();

  //  getNthValue(int)
  /// Returns the Value located at position int in the list of incoming pairs.
  /// Asserts 0 if int is out of range.
  Value* getNthValue(int);

  //  setNthValue(Value*, int)
  /// Sets the Value located at position int in the list of incoming pairs.
  /// Asserts 0 if Value is not the same Type as the PhiNode.
  /// Asserts 0 if int is out of range.
  void setNthValue(Value*, int);

  //  getNthBlock(int)
  /// Returns the BasicBlock located at position int in the list of incoming pairs.
  /// Asserts 0 if int is out of range.
  BasicBlock* getNthBlock(int);
  
  //  setNthBlock(BasicBlock*, int)
  /// Sets the BasicBlock located at position int in the list of incoming pairs.
  /// Asserts 0 if int is out of range.
  void setNthBlock(BasicBlock*, int);

  //  addPair(Value*, BasicBlock*)
  /// adds the pair of (Value*, BasicBlock*) to the list of incoming pairs.
  /// Asserts 0 if Value* is not the same Type as the PhiNode
  void addPair(Value*, BasicBlock*);

  //  removeNthPair(int)
  /// detaches the pair at location int from the list of incoming pairs.
  void removeNthPair(int);
  
protected:
  //  Constructor
  PhiNode(Type *type);

private:
  //  pairs
  /// all pairs of Values and BasicBlocks representing each Value
  /// this PhiNode could take on depending on the flow of control
  josh::List< std::pair<Value*, BasicBlock*> > pairs;
};

  /***************************************************************************
   *                           StoreInst                                     *
   ***************************************************************************/
class StoreInst : public Instruction
{
public:
  //  Create(Value *toStore, Value *address)
  /// Returns a new StoreInst that stores Value toStore at location address.
  /// Asserts 0 if address's Type is not a pointer.
  /// Asserts 0 if the Type address's Type points to is not equal to Value's Type.
  static StoreInst* Create(Value *toStore, Value *address);

  Value* getStoredValue(); ///< returns the Value which this is storing
  Value* getAddress();     ///< returns the address to which this is storing to

protected:
  //  Constructor
  StoreInst(Value *toStore, Value *address);

private:
  Value *toStore;
  Value *address;

};

  /***************************************************************************
   *                           LoadInst                                      *
   ***************************************************************************/
class LoadInst : public Instruction
{
public:
  //  Create(Value*)
  /// Returns a new LoadInst that loads a Value from address.
  /// Asserts 0 if address's Type is not a pointer
  static LoadInst* Create(Value *address);

private:
  Value *address;
};

  /***************************************************************************
   *                          AllocaInst                                     *
   ***************************************************************************/
class AllocaInst : public Instruction
{
public:
  static AllocaInst* Create(Type *type);
  static AllocaInst* CreateArray(Type *type, Value *size);
private:
};

#endif
