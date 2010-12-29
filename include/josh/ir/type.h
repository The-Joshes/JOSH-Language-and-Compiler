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
  //  getBaseType()
  /// returns an enum detailing the exact type this Type describes.
  /// for example, to check if a type is an integer, do
  /// (type->getBaseType() == INTEGERTYPE)
  inline BaseType getBaseType() const;

protected:
  BaseType baseType; ///< the exact type this Type describes @see getBaseType()
};

#endif
