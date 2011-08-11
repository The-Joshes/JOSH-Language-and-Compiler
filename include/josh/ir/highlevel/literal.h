#ifndef __LITERAL_H__
#define __LITERAL_H__

#include <list>

#include "josh/ir/highlevel/immutablevalue.h"

namespace highlevel
{
  class Module;
}

class BinaryInst;
class Type;

/// class Literal
/// An ImmutableValue whose actual Value is also known at compile time.
class Literal : public ImmutableValue
{
public:
  union ActualValue
  {
    char char_val;
    int int_val;
    bool bool_val;
    float float_val;
    char *str_val;
  };

  /// The passed in Type is used to determine which field in ActualValue to use.
  static Literal* Create(Type *type, ActualValue *value);
  
  /// Creates a Literal equivalent to BinaryInst
  /// If BinaryInst's Value cannot be determined at compile time, NULL is returned.
  static Literal* CreateEquivalent(BinaryInst*, highlevel::Module*);

  static Literal* getTrue(highlevel::Module*);  ///< returns a Literal equvialent to true
  static Literal* getFalse(highlevel::Module*); ///< returns a Literal equivalent to false
  static Literal* getZero(highlevel::Module*);  ///< returns a Literal equivalent to 0
  static Literal* getOne(highlevel::Module*);   ///< returns a Literal equivalent to 1
  static Literal* getNull(highlevel::Module*);  ///< returns a Literal equivalent to Null

  const ActualValue* getActualValue() const;

protected:
  Literal(Type *type, ActualValue *value);

private:
  ActualValue *value;
};

#endif
