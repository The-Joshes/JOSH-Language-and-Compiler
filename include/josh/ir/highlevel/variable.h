#ifndef __VARIABLE_H__
#define __VARIABLE_H__

#include <list>
#include <string>

#include "josh/ir/highlevel/globalvalue.h"

class Type;
class Module;

namespace highlevel
{
  class Module;
}

/// class Variable
/// A piece of memory allocated globally, either initialized or uninitialized.
/// Variables always have a PointerType.
/** 
 * An initialized Variable contains one or more of either or both 
 * basic types (Literals) and pointers to other Variables.
 */
class Variable : public GlobalValue
{
public:
  /// Creates a new, unitialized variable in the global space.
  static Variable* Create(Type *type, 
                          highlevel::Module*, 
                          const std::string &name = "");
  
  /// Creates a new, initialized variable in the global space.
  static Variable* Create(ImmutableValue *value, 
                          highlevel::Module*, 
                          const std::string &name = "");

  /// Creates a new, uninitialized variable in the global space.
  /// Useful for creating arrays or structs.
  static Variable* Create(const std::list<Type*>::iterator &types,
                          highlevel::Module*, 
                          const std::string &name = "");

  /// Creates a new, initialized variable in the global space.
  /// Useful for creating arrays or structs.
  static Variable* Create(const std::list<ImmutableValue*>::iterator &values,
                          highlevel::Module*, 
                          const std::string &name = "");
 
  int getNumValues() const;
  
  /// for non initialized Values, there will be a default NULL value
  const std::list<Value*>::const_iterator& getValues() const;
  
  /// Changes the Value that this Variable is initialized with.
  /// Asserts 0 if int is out of range.
  /// Asserts 0 if the Type at position int does not match Value.
  void setValue(int, Value*);

protected:
  Variable(bool externalVisibility, Type*, const std::string &name = "");

private:
  std::list<Value*> values;

};

#endif
