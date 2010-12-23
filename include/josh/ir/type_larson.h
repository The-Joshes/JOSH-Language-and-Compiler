#ifndef __TYPE_H__
#define __TYPE_H__

enum TypeID
{
  VOIDTYPE, INTEGERTYPE, DECIMALTYPE,
  POINTERTYPE, ARRAYTYPE, CUSTOMTYPE,
  ERRORTYPE
};

class Type
{
public:
  TypeID getTypeID() const;

protected:
  TypeID typeid;
  
};

#endif
