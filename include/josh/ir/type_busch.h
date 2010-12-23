#ifndef __TYPE_H__
#define __TYPE_H__

class Type
{
public:
  bool isVoidType();
  bool isIntegerType();
  bool isDecimalType();
  bool isPointerType();
  bool isArrayType();
  bool isStructType();
protected:
  enum TypeID
  {
    VoidTypeID, IntegerTypeID, DecimalTypeID, 
    PointerTypeID, ArrayTypeID, StructTypeID
  } typeID;
};

#endif
