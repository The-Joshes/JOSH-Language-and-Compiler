#ifndef __TYPE_H__
#define __TYPE_H__

enum TypeID
{
  VoidTypeID, IntegerTypeID, DecimalTypeID, 
  PointerTypeID, ArrayTypeID, StructTypeID
};

class Type
{
public:
  TypeID getTypeID() const;

protected:
  TypeID typeid;
  
};

#endif
