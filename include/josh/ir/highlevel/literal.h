#ifndef __LITERAL_H__
#define __LITERAL_H__

#include <list>

#include "josh/ir/highlevel/immutablevalue.h"

namespace highlevel
{
  class Module;
}

class ActualValue;
class BinaryInst;
class Type;

/// class Literal
/** 
 *  
 */
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

  static Literal* Create(Type *type, ActualValue *value);
  static Literal* CreateEquivalent(BinaryInst*, highlevel::Module*);
  static Literal* getTrue(highlevel::Module*);  ///< returns a Literal equvialent to true
  static Literal* getFalse(highlevel::Module*); ///< returns a Literal equivalent to false
  static Literal* getZero(highlevel::Module*);  ///< returns a Literal equivalent to 0
  static Literal* getOne(highlevel::Module*);   ///< returns a Literal equivalent to 1
  static Literal* getNull(highlevel::Module*);  ///< returns a Literal equivalent to Null

  const ActualValue* getActualValue();

protected:
  Literal(Type *type, ActualValue *value);

private:
  ActualValue *value;
};

#endif
