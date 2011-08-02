#ifndef __PHINODE_H__
#define __PHINODE_H__

#include "josh/ir/highlevel/instruction.h"
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
                         BasicBlock *insertAtEnd);

  /// Creates an empty PhiNode to be filled in later.  
  /// The Instruction returned is not considered valid until all appropriate 
  /// paths to the PhiNode's parent basic block are filled in with a 
  /// (path, value) pair.
  static PhiNode* CreateEmpty(Type *type, BasicBlock *insertAtEnd);

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
#endif
