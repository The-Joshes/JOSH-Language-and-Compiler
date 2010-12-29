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

  //  isConstant()
  /// a Value is constant if one of two things are true:
  /// 1) it is a Constant
  /// -- or --
  /// 2) it is an arithmetic operation and all of its uses are constant.
  /// Every time the uses are modified, constantness is updated.
  bool isConstant();

protected:
  void addUser(Value*);       ///< adds Value to the user list
  bool removeUser(Value*);    ///< if Value is in users list, removes and returns true
  void removeUserAt(int);     ///< removes Value at location in in the users list
                              ///< asserts 0 if int is out of range of the users list
  
  void addUse(Value*);        ///< adds Value to the uses list
  bool removeUse(Value*);     ///< if Value is in uses list, removes and returns true
  void removeUseAt(int);      ///< removes Value at location in in the uses list
                              ///< asserts 0 if int is out of range of the uses list
  
  Type *type; ///< this Value's type
 
  bool isConstant; ///< is this Value constant? @see isConstant()

private:
  josh::List<Value*> users; ///< all Values that use this Value
  josh::List<Value*> uses;  ///< all Values this Value depends on
};
