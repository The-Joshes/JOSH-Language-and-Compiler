#ifndef __CONSTANT_H__
#define __CONSTANT_H__

#include "josh/ir/highlevel/user.h"

class Type;
class BinaryInst;

/// class Constant
/// Represents all Users whose value and size are known at compile time.
/** 
 * Constant is a User because certain kinds (like arrays) may use other
 * Constants, thus qualifying them as Users.
 */
template <typename T>
class Constant : public User
{
public:
  /// Creates and returns a Constant with a Value that evaulates to value
  /// and a Type of type.
  static Constant<T>* Create(T value, Type *type);

  const T getValue();

private:
  T value;
};

#endif
