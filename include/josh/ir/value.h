#ifndef __VALUE_H__
#define __VALUE_H__

#include "josh/type.h"

class Value
{
public:
  const Type* getType();
private:
  Type *type;
};

#endif
