#ifndef __TYPE_H__
#define __TYPE_H__

enum BaseType
{
  VOIDTYPE, INTEGERTYPE, DECIMALTYPE,
  POINTERTYPE, ARRAYTYPE, CUSTOMTYPE,
  ERRORTYPE
};

class Type
{
public:
  inline BaseType getBaseType() const;

protected:
  BaseType basicType;
};

#endif
