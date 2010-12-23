#ifndef __VALUE_H__
#define __VALUE_H__

#include "josh/ir/type.h"

class Value
{
public:
  const Type* getType();
private:
  Type *type;
};

#endif
