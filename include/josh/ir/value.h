#ifndef __VALUE_H__
#define __VALUE_H__

#include "utils/vector.h"

class Type;

//! class Value
//! represents any value computed and/or used by a program
/*!
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
 * is, all Values this Value depends on in its definition.  Uses cannot be
 * changed directly through Value, only through subclasses (for example,
 * adding operands to an Instruction).
 */

class Value
{
public:
  /// getType
  /// returns a const pointer to the Value's Type
  const Type* getType();

  /// getUsers
  /// returns a const Vector containing all Values
  /// which depend on this Value
  const josh::Vector<Value*>* getUsers();
  /// addUser
  /// adds Value to the users list
  void addUser(Value*);
  /// removeUser
  /// if Value is in the users list, remove it
  /// returns true if the Value was in the list, false otherwise
  bool removeUser(Value*);
  /// removeUserAt
  /// removes Value at location int in the users list
  void removeUserAt(int);
  
  /// getUses
  /// returns a const Vector containing all Values
  /// that this Value depends on
  const josh::Vector<Value*>* getUses();

  /// isConstant
  /// a Value is constant if one of two things are true:
  /// 1) it is a Constant
  /// 2) all its uses are constant
  /// every time the uses are modified, constantness is updated
  bool isConstant();

protected:
  void addUser(Value*); /**< adds Value to the user list */
  
  void addUse(Value*); /**< adds Value to the uses list */
  bool removeUse(Value*); /**< if Value is in uses list, removes and returns true */
  void removeUseAt(int); /**< removes Value at location in in the uses list */

  Type *type; /**< this Value's type */
  
  josh::Vector<Value*> users; /**< all Values that use this Value */
  josh::Vector<Value*> uses; /**< all Values this Value depends on */
 
  bool isConstant; /**< is the Value constant? */
};

#endif
