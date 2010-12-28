#ifndef __VALUE_H__
#define __VALUE_H__

#include "utils/vector.h"


/// class Value
/*!
 * Value is the base of a series of classes that represent all values 
 * computed and/or used by a program.  Value's constructor is private,
 * so it is impossible to create an actual instance of Value.
 * One must call a sub class' constructor or create method in order
 * to create a instance with a superclass of Value.
 *
 * All Values have a corresponding Type.  A Value's Type cannot be changed 
 * after creation; a new Value must be created in order to achieve this.
 *
 * All Values keep track of their users, that is, all other Values who use this
 * Value in their definition.  All Values also keep track of their uses, that
 * is, all Values this Value depends on in its definition.
 */

class Type;

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
  
  /// getUses
  /// returns a const Vector containing all Values
  /// that this Value depends on
  const josh::Vector<Value*>* getUses();

private:
  
  Type *type; //this Value's type
  
  josh::Vector<Value*> users; //all Values that use this Value
  josh::Vector<Value*> uses; //all Values this Value depends on
  
  /// Constructor
  /// private so that an instance of Value cannot be instanciated
  Value();
};

#endif
