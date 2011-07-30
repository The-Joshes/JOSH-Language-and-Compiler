#ifndef __VALUE_H__
#define __VALUE_H__

#include <list>

class Type;
class User;

/// class Value
/// A Value is anything computed by the program (either at run time
/// or compile time) that can be used as an operator to another Value.
/** 
 * Value is an abstract base class.
 * All Values have a corresponding Type.  This Type cannot be changed
 * after creation.
 * All Values also keep track of their users; that is, all other Values
 * who depend (use) on this Value.  The list of users is not manually 
 * updated, but is automatically changed as new Values are created, 
 * modified, and destroyed.
 */
class Value
{
public:
  /// returns a pointer to the Value's Type
  const Type* getType() const;
  
  /// Returns an Iterator containing all Values which depend on this Value.
  /// An empty Iterator implies this Value is never used.
  std::list<Value*>::iterator& getUsers();
  
  int getNumUsers() const; ///< returns the number of Values that use this

  /// Replaces all users of this Value with the new Value.
  /// Iterates over the users list and replaces the use of
  /// this Value with the new Value.
  /// for(User u : users) user->replaceUsesOfWith(this, value);
  void replaceAllUsersWith(Value*);

  virtual ~Value();

protected:
  void addUser(Value*);    ///< adds Value to the user list
  bool removeUser(Value*); ///< if Value is in users list, removes and returns true
  
  Value(Type*);
  
private:
  Type *type; ///< this Value's type
  
  std::list<User*> users; ///< all Values that use this Value
};

#endif
