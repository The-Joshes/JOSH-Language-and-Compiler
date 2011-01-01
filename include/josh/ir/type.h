#ifndef __TYPE_H__
#define __TYPE_H__

//  class Type
/// Describe's a Value's Type.
/// Typically Values of different Types cannot interact with eachother.
/// To check if two types are equal, use the equals(Type*) method.
class Type
{
public:
  //  enum BaseType
  /// Describes the underlying type of this Type.
  enum BaseType
  {
    VOID, INTEGER, DECIMAL,
    POINTER, ARRAY, CUSTOM,
    ERROR
  };

  //  getBaseType()
  /// Returns an enum detailing the exact type this Type describes.
  /// For example, to check if a type is an integer, do
  /// (type->getBaseType() == Type::INTEGER)
  BaseType getBaseType() const;

  //  equals(Type*)
  /// returns true if this and the passed in Type are equivalent; false otherwise
  virtual bool equals(Type*) const;

  /// JUST TO COMPILE, WILL REMOVE
  static Type* GetVoidType() { return 0;}
protected:

private:
  BaseType baseType; ///< the exact type this Type describes @see getBaseType()
};

/// ONLY HERE FOR TESTING/COMPILING REASONS, WILL MOVE SOON 
class PointerType : public Type 
{
public:
  Type* getPointedToType() {return this;} 
};

#endif
