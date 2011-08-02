#ifndef __FUNCTION_H__
#define __FUNCTION_H__

#include <cstring> // for NULL
#include <list>

#include "josh/ir/highlevel/value.h"

class BasicBlock;
class Module;
class FunctionType;

/// class Function
/// Represents a list of basic blocks that compose a function.
/**
 * A function may have only one entry point, but multiple exit points.
 * A function's return Type and argument Types are initialized at creation
 * and cannot be changed afterwards.
 * A function is not considered valid for compilation until an entryPoint 
 * is specified; see entryPoint.
 */
class Function : public Value
{
public:
  static Function* Create(Module *parent,
                          FunctionType *type,
                          const std::string &name = "");
  
  BasicBlock* getEntryPoint();          ///< @see entryPoint
  void setEntryPoint(BasicBlock*);      ///< @see entryPoint
  const FunctionType* getType() const;  ///< contains the return type and argument type(s)

  /// A function is composed of a list of BasicBlocks.
  /// The order of BB in a function is arbitrary; by convention, the entry point
  /// should be listed first, but this is not necessary.  The entry point is 
  /// determined by the Create and/or setEntryPoint functions.
  /// Just because a BB is in a function doesn't mean it is reachable from
  /// normal flow of control.  
  std::list<BasicBlock*> getBlocks(); 

  /// If the parent Module already has a main Function, the other
  /// main function is notified of its demotion and this Function
  /// becomes the Module's main Function.
  void setMainFunction(bool isMain);
  bool isMainFunction();

private:
  Function(Module*, FunctionType*, BasicBlock*);

  Module *parent;
  FunctionType *type;

  /// The point of entrance for when a function is called.
  BasicBlock *entryPoint;

  bool isMain;
};

#endif
