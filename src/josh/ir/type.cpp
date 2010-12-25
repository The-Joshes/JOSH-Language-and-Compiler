#include "josh/ir/type.h"

/* Type
 */
bool Type::isVoidType()
{
  return typeID == VoidTypeID;
}

bool Type::isIntegerType()
{
  return typeID == IntegerTypeID;
}

bool Type::isDecimalType()
{
  return typeID == DecimalTypeID;
}

bool Type::isPointerType()
{
  return typeID == PointerTypeID;
}

bool Type::isArrayType()
{
  return typeID == ArrayTypeID;
}

bool Type::isStructType()
{
  return typeID == StructTypeID;
}
