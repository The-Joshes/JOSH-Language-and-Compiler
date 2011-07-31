#ifndef __CONSTANT_H__
#define __CONSTANT_H__

#include "josh/ir/highlevel/user.h"

class Profile;
class Type;

/// class Constant
/// Represents all Users whose value and size are known at compile time.
/** 
 * Constant is a User because certain kinds (like arrays) may use other
 * Constants, thus qualifying them as Users.
 */
class Constant : public User
{
public:
  /// Creates and returns a Constant with a Value that evaulates to value
  /// and a Type of type. Asserts 0 if Type's bit width != sizeof(T)
  template <typename T>
  static Constant* Create(T value, Type *type);
  
  static Constant* getTrue(Profile*);
  static Constant* getFalse(Profile*);
  static Constant* getZero(Profile*);
  static Constant* getOne(Profile*);
  static Constant* getNegOne(Profile*);

protected:
  Constant(Type*, const std::string &name = "");
};

  /***************************************************************************
   *                           Implementation                                *
   ***************************************************************************/
template <typename T>
class ActualValue : protected Constant
{
public:

protected:
  ActualValue(T value_, Type *type)
    : Constant(type, ""), value(value_)
  {
  }

private:
  T value;
};

template <typename T>
Constant* Constant::Create(T value, Type *type)
{
  return new ActualValue<T>(value, type);
}

#endif
