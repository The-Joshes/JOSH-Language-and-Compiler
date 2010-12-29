#ifndef __VALUE_H__
#define __VALUE_H__

#include "utils/list.h"

class Type;

/// class Value
/// represents any value computed and/or used by a program
/**
 * Value is the base of a series of classes that represent all values 
 * computed and/or used by a program.  Value is an abstract base class,
 * so it is impossible to create an actual instance of Value.
 * One must call a sub class' constructor or create method in order
 * to create a instance with a superclass of Value.  The 2 primary
 * subclasses of Value are Constant and Instruction.  Constant
 * represents any Value whos size and value are known at compile time.
 * Instruction represents any Value which must be computed dynamically.
 *
 * All Values have a corresponding Type.  A Value's Type cannot be changed 
 * after creation; a new Value must be created in order to achieve this.
 *
 * All Values keep track of their users, that is, all other Values who use this
 * Value in their definition.  All Values also keep track of their uses, that
 * is, all Values this Value depends on in its definition.  Uses and Users
 * cannot be changed directly through Value, only through subclasses.
 */
class Value
{
public:
  //  getType()
  /// returns a const pointer to the Value's Type
  const Type* getType();

  //  getUsers()
  /// returns an Iterator containing all Values which depend on this Value.
  /// an empty Iterator implies this Value is never used.
  josh::Iterator<Value*>& getUsers();
 
  //  getUses()
  /// returns an Iterator containing all Values that this Value depends on.
  /// an empty Iterator implies this Value is a Constant (or is not properly set up!).
  josh::Iterator<Value*>& getUses();

  //  canBeComputedAtCompileTime()
  /// returns true if this Value's value can be computed at compile time; returns false otherwise.
  /// a Value can be computed at compile time if one of two things are true:\n
  /// 1) it is a Constant\n
  /// -- or --\n
  /// 2) it is an arithmetic operation and all of its uses are Constant\n
  bool canBeComputedAtCompileTime();

  //  Destructor
  /// Frees up the Type used by this Value
  virtual ~Value();

protected:
  void addUser(Value*);    ///< adds Value to the user list
  Value* getUserAt(int);   ///< returns the Value at position int in the user list
  bool removeUser(Value*); ///< if Value is in users list, removes and returns true
  void removeUserAt(int);  ///< removes Value at position int in the users list.
                           ///< asserts 0 if int is out of range of the users list.
  
  void addUse(Value*);     ///< adds Value to the uses list
  Value* getUseAt(int);    ///< returns the Value at position int in the use list
  bool removeUse(Value*);  ///< if Value is in uses list, removes and returns true
  void removeUseAt(int);   ///< removes Value at position int in the uses list.
                           ///< asserts 0 if int is out of range of the uses list.

  //  Constructor
  Value(Type *type, bool isArithmetic = false, bool isConstant = false);
  
private:
  Type *type; ///< this Value's type
 
  bool isConstant;   ///< is this Value a Constant? 
  bool isArithmetic; ///< is this an Arithmetic Instruction?
  bool allUsesConst; ///< are all Values used by this Value Constant?

  josh::List<Value*> users; ///< all Values that use this Value
  josh::List<Value*> uses;  ///< all Values this Value depends on
};
