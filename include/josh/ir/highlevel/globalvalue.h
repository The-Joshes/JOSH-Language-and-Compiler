#ifndef __GLOBALVALUE_H__
#define __GLOBALVALUE_H__

#include <string>

#include "josh/ir/highlevel/user.h"
#include "josh/ir/highlevel/module.h"

class Type;

/// class GlobalValue
/// Represents any Value able to be globally assesible.
/** 
 *  
 */
class GlobalValue : public User
{
public:
  /// Sets aside space in the global scope for an unionstant Value.
  /// The created Type is always PointerType, with its pointed to Type
  /// being the type passed in.  This type must be a basic Type 
  /// (INTEGER, FLOAT), a pointer (POINTER), or a user defined Type (COMPLEX).
  /// Else, 0 is asserted. 
  /// If the name is blank, a new name is generated using Module's 
  /// naming functionality.  The GlobalValue is then added to the module.
  /// If the name is not blank and is unique, it is added to the module.
  /// If the name is not unique, 0 is asserted.
  static GlobalValue* CreateVariable(Type *type, 
                                     highlevel::Module*, 
                                     const std::string &name = "");
 
  /// Sets aside and initializies space in the global scope for a Value.
  /// The created Type is always PointerType, with its pointed to Type
  /// being the type passed in.  This type must be a basic Type 
  /// (INTEGER, FLOAT), a pointer (POINTER), or a user defined Type (COMPLEX).
  /// Else, 0 is asserted. 
  /// Creates and returns a constant with a Value that evaulates to value
  /// and a Type of type. Asserts 0 if Type's bit width != sizeof(T).
  /// If the name is blank, a new name is generated using Module's 
  /// naming functionality.  The GlobalValue is then added to the module.
  /// If the name is not blank and is unique, it is added to the module.
  /// If the name is not unique, 0 is asserted.
  template <typename T>
  static GlobalValue* CreateVariable(T value,
                                     Type *type, 
                                     highlevel::Module*, 
                                     const std::string &name = "");

  /// A Constant is a GlobalValue whose value is known at compile time.
  /// Unlike a variable, since the value can never change, the constant
  /// is generally directly substituted into code that utilizes it
  /// rather than making space in memory for it.
  /// Creates and returns a constant with a Value that evaulates to value
  /// and a Type of type. Asserts 0 if Type's bit width != sizeof(T).
  /// The passed in type must be a basic Type (INTEGER, FLOAT), a pointer 
  /// (POINTER) or a user defined Type (COMPLEX).  Else, 0 is asserted.
  template <typename T>
  static GlobalValue* CreateConstant(T value,
                                     Type *type,
                                     const std::string &name = "");
  
  static GlobalValue* getTrue(highlevel::Module*);   ///< returns a Constant equvialent to true
  static GlobalValue* getFalse(highlevel::Module*);  ///< returns a Constant equivalent to false
  static GlobalValue* getZero(highlevel::Module*);   ///< returns a Constant equivalent to 0
  static GlobalValue* getOne(highlevel::Module*);    ///< returns a Constant equivalent to 1
  static GlobalValue* getNegOne(highlevel::Module*); ///< returns a Constant equivalent to -1

  bool isConstant() const;

protected:
  GlobalValue(Type*, bool isConstant, const std::string &name = "");

private:
  bool constant;
};

  /***************************************************************************
   *                           Implementation                                *
   ***************************************************************************/
template <typename T>
class ActualValue : protected GlobalValue
{
public:

protected:
  ActualValue(T value_, Type *type, bool isConstant, const std::string &name = "")
    : GlobalValue(type, isConstant, name), value(value_)
  { }

private:
  T value;
};

template <typename T>
GlobalValue* GlobalValue::CreateConstant(T value, Type *type, const std::string &name)
{ 
  return new ActualValue<T>(value, type, true, name);
}

template <typename T>
GlobalValue* GlobalValue::CreateVariable(T value, Type *type, highlevel::Module *m, const std::string &name)
{
  GlobalValue *gv = new ActualValue<T>(value, type, false, name);
  m->addGlobal(gv);
  return gv;
}


#endif
