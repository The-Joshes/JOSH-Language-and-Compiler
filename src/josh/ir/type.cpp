#include "josh/ir/type.h"

#include <assert.h>

Type::BaseType Type::getBaseType() const
{
  return baseType;
}

bool Type::equals(Type *t) const
{
  assert(0 && "Not implemented yet");
}
