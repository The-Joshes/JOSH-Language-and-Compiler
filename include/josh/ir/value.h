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
 * to create an instance with a superclass of Value.  The 2 primary
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
  /// returns a pointer to the Value's Type
  Type* getType();
  
  bool isConstant(); ///< is this Value a subclass of Constant?

  //  getUsers()
  /// returns an Iterator containing all Values which depend on this Value.
  /// an empty Iterator implies this Value is never used.
  Iterator<Value*>& getUsers();
  int getNumUsers(); ///< returns the number of Values that use this Value
 
  //  getUses()
  /// returns an Iterator containing all Values that this Value depends on.
  /// an empty Iterator implies this Value is a Constant (or is not completely set up!).
  Iterator<Value*>& getUses();

  //  void replaceAllUsesWith(Value*)
  /// replaces all uses of this value with Value
  /// iterates over this Value's user list and replaces 
  /// Value's use of this value with the new Value
  void replaceAllUsesWith(Value*);

  //  Destructor
  virtual ~Value();

protected:
  void addUser(Value*);    ///< adds Value to the user list
  bool removeUser(Value*); ///< if Value is in users list, removes and returns true
  
  void addUse(Value*);     ///< adds Value to the uses list
  bool removeUse(Value*);  ///< if Value is in uses list, removes and returns true
 
  /// returns true if all Values this Value relies on are subclasses of Constant;
  /// returns true if this Value relies on no Values;
  /// returns false otherwise.
  bool allUsesConstant();  
  
  //  Constructor
  Value(Type*, bool isConstant = false);
  
private:
  Type *type; ///< this Value's type
  
  bool isConstantClass;   ///< @see isConstant()
  int numNonConstantUses; ///< @see allUsesConstant()

  List<Value*> users; ///< all Values that use this Value
  List<Value*> uses;  ///< all Values this Value depends on
};

#endif
