#ifndef __INSTRUCTIONS_H__
#define __INSTRUCTIONS_H__

#include "josh/ir/highlevel/instruction.h"

#include <cstring> // for NULL

class BasicBlock;
class Function;
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
  
  /// List of binary operators.\n
  /// Arithmetic: ADD, SUBTRACT, MULTIPLY, DIVIDE.\n
  /// Compare: LESS_THAN, GREATER_THAN, LESS_OR_EQUAL, GREATER_OR_EQUAL, EQUAL, NOT_EQUAL.
  /// Compare Insts always have a Type of Integer, regardless of the Type of its operators.
  /// To see a BinaryInst's operator Type, see getOpType()
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

  /// Create a new BinaryInst of the form (val) = (lhs) op (rhs).
  /// If lhs and rhs do not have the same BaseType, 0 is asserted.
  /// If the op is arithmetic, the new BinaryInst has the same BaseType as lhs and rhs.
  /// If the op is a compare, the new BinaryInst has a Type of Integer.
  /// If the op is not defined for the operator Types, 0 is asserted.
  static BinaryInst* Create(BinaryOp op, Value *lhs, Value *rhs, BasicBlock *insertAtEnd=NULL);

  /***************************************************************************
   *                           Member functions                              *
   ***************************************************************************/
  
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
  BinaryInst(BinaryOp, Type *type, Type *operatorType, BasicBlock *insertAtEnd);

private:
  bool arithmetic;
  BinaryOp op; 
  Type *opType; 
  Value *lhs, *rhs; 
};

  /***************************************************************************
   *                           TerminatorInst                                *
   ***************************************************************************/
/// All Instructions that serve as terminators; that is, instructions that
/// disrupt the flow of control.
class TerminatorInst : public Instruction
{
public:
  /// Ops available for a TerminatorInst
  enum TerminatorOp
  {
    RETURN, UNCONDITIONAL_BRANCH, CONDITIONAL_BRANCH
  };

  /// Create a new Conditional Branching Instruction.
  /// The condition's Type must be Integer, else 0 is asserted.
  /// If condition is evaluated at run time to be non-zero, BB jumpToOnTrue is branched to.
  /// Else, BB jumpToOnFalse is branched to.
  /// TerminatorOp's Type is set to void.
  static TerminatorInst* CreateConditionalBranch(BasicBlock *jumpToOnTrue,
                                                 BasicBlock *jumpToOnFalse,
                                                 Value *condition, 
                                                 BasicBlock *insertAtEnd=NULL);

  /// Create a new Unconditional Branching Instruction.
  /// Flow of control is always handed to BB jumpTo.
  /// TerminatorOp's Type is set to void.
  static TerminatorInst* CreateUnconditionalBranch(BasicBlock *jumpTo,
                                                   BasicBlock *insertAtEnd=NULL);

  /// Creates an Instruction to return from a function back to the original
  /// calling point.  If the parent function exists at creation time and
  /// returnVal's Type is different than the parent function's returnType, 
  /// 0 is asserted.
  static TerminatorInst* CreateReturn(Value *returnVal, BasicBlock *insertAtEnd=NULL);

  TerminatorOp getTerminatorOp(); 

  /// If this Instruction is a RETURN, ensures that the parent Function's 
  /// return Type is the same as the Type of the Value being returned.
  /// If not, 0 is asserted.
  virtual void setParent(BasicBlock*);

protected:
  TerminatorInst(TerminatorOp op, BasicBlock *insertAtEnd);

private:
  TerminatorOp op; 
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
  /// Create a CallInst
  static CallInst* Create(Function *toCall, 
                          std::list<Value*> args,
                          BasicBlock *insertAtEnd=NULL);
 
  /// Sets the argument at position 0 in the CallInst to be Value.
  /// Asserts 0 if the index is out of bounds.
  /// Asserts 0 if the Value has an incorrect Type for the Function
  /// at position index.
  void setArg(int, Value*);
  Value* getArg(int);

protected:
  CallInst(Function *toCall, BasicBlock *insertAtEnd);

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
  /// Creates a PhiNode that determines value based on flow.
  /// All Values in values must have the same Type, else 0 is asserted.
  /// The PhiNode's Value is equivalent to the Type of any of the values.
  static PhiNode* Create(std::list<Value*>::iterator &values, 
                         std::list<BasicBlock*>::iterator &paths, 
                         BasicBlock *insertAtEnd=NULL);

  /// Creates an empty PhiNode to be filled in later.  
  /// The Instruction returned is not considered valid until all appropriate 
  /// paths to the PhiNode's parent basic block are filled in with a 
  /// (path, value) pair.
  static PhiNode* CreateEmpty(Type *type, BasicBlock *insertAtEnd=NULL);

  /// returns the number of (Value*, BasicBlock*) pairs that 
  /// exist for this PhiNode
  int getNumPairs();

  /// Returns the Value located at position int in the list of incoming pairs.
  /// Asserts 0 if int is out of range.
  Value* getNthValue(int);

  /// Sets the Value located at position int in the list of incoming pairs.
  /// Asserts 0 if Value is not the same Type as the PhiNode.
  /// Asserts 0 if int is out of range.
  void setNthValue(int, Value*);

  /// Returns the BasicBlock located at position int in the list of incoming
  /// pairs. Asserts 0 if int is out of range.
  BasicBlock* getNthBlock(int);
  
  /// Sets the BasicBlock located at position int in the list of incoming 
  /// pairs. Asserts 0 if int is out of range.
  void setNthBlock(int, BasicBlock*);

  /// Adds the pair of (Value*, BasicBlock*) to the list of incoming pairs.
  /// Asserts 0 if Value is not the same Type as the PhiNode.
  void addPair(Value*, BasicBlock*);

  /// detaches the pair at location int from the list of incoming pairs.
  void removeNthPair(int);
  
protected:
  PhiNode(Type *type, BasicBlock *insertAtEnd);

private:
  /// all pairs of Values and BasicBlocks representing each Value
  /// this PhiNode could take on depending on the flow of control
  std::list< std::pair<Value*, BasicBlock*> > pairs;
};

  /***************************************************************************
   *                           StoreInst                                     *
   ***************************************************************************/
/// Stores a value to memory.  All StoreInst are void Type, thus that they
/// cannot be used by subsequent Instructions.
class StoreInst : public Instruction
{
public:
  /// Returns a new StoreInst that stores Value toStore at location address.
  /// Asserts 0 if address's Type is not a pointer.
  /// Asserts 0 if the address's pointed to Type to is not equal to Value's Type.
  static StoreInst* Create(Value *toStore, Value *address, BasicBlock *insertAtEnd=NULL);

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

  /***************************************************************************
   *                           LoadInst                                      *
   ***************************************************************************/
/// Loads a Value from memory.  
class LoadInst : public Instruction
{
public:
  /// Returns a new LoadInst that loads a Value from address.
  /// Asserts 0 if address's Type is not a pointer.
  /// Takes on the Type that address points to.
  static LoadInst* Create(Value *address, BasicBlock *insertAtEnd=NULL);

  Value* getAddress();     ///< returns the address to which this is loading from

  /// Sets the Value to which this instruction stores to.
  /// asserts 0 if the Value's Type is not a pointer.
  /// asserts 0 if the address' pointed to Type is different 
  /// from the instruction's Type.
  void setAddress(Value*); 

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
  /// Creates an Instruction to allocate a piece of memory.
  /// arraySize must be of type Integer.
  /// If arraySize is a Constant and evaluates to a negative number, 
  /// 0 is asserted.  The Value of AllocaInst is of Type Pointer and 
  /// points to the allocated space.
  static AllocaInst* CreateArray(Type *type, 
                                 Value *arraySize, 
                                 BasicBlock *insertAtEnd=NULL);

  /// Creates an Instruction to allocate a piece of memory.
  /// The Value of AllocaInst is a pointer which points to the allocated space.
  static AllocaInst* Create(Type *type, BasicBlock *insertAtEnd=NULL);

  /// Returns a Value of Type Integer detailing the amount of space allocated.
  /// If a non-array pointer was created, the array size will be a Constant of
  /// value 1.
  Value *getArraySize(); 
                        
protected:
  AllocaInst(Type *type, Value *arraySize, BasicBlock *insertAtEnd);

private:
  Value *arraySize; ///< @see getArraySize()
};

  /***************************************************************************
   *                          Cast Insts                                     *
   ***************************************************************************/
/// Does a cast on a Value from one Type to another.
/// Cast is an abstract class; need to create one of its subclasses.
class Cast : public Instruction
{
public:
  /// Determine what course of action to take if the Value has a smaller
  /// bit width than the Type it is being cast to.
  enum BitExtension
  {
    ZERO,            /*!< zero extend the Value */
    SIGN,            /*!< sign extend the Value */
    EXTENSION_ERROR  /*!< assert 0 */
  };
  
  /// Determine what course of action to take if the Value has a larger
  /// bit width than the Type it is being cast to.
  enum BitCut
  {
    CUT,      /*!< cuts away the upper bits of Value */
    CUT_ERROR /*!< assert 0 */
  };
  
protected:
  Cast(Value *toCast, Type *newType, BasicBlock *insertAtEnd);
  BitExtension extendMethod;
  BitCut cutMethod;
};

  /***************************************************************************
   *                          BitCast                                        *
   ***************************************************************************/
/// A BitCast does exactly that; it intreprets the bits of Value exactly
/// as if they were of Type newType.  If Type has a larger or smaller
/// bit width than toCast, appropriate cutting/extension action is taken.
class BitCast : public Cast
{
public:
  static Cast* Create(Value *toCast, 
                      Type *newType, 
                      BitExtension extendMethod = EXTENSION_ERROR,
                      BitCut cutMethod = CUT_ERROR,
                      BasicBlock *insertAtEnd=NULL);
protected:
  BitCast(Value *toCast, Type *newType, BasicBlock *insertAtEnd);
};

#endif
