#ifndef __TYPES_H__
#define __TYPES_H__

#include <list>

#include "josh/ir/highlevel/type.h"

namespace highlevel
{
  class Module;
}

/// class NumericType
/// Any type that can be represented by a basic number (INTEGER, FLOAT, POINTER)
class NumericType : public Type
{
protected:
  NumericType(BaseType baseType, int bitWidth);
};

/// clsas ArithmeticType
/// Represents a Type (INTEGER and FLOAT) that BinaryInst Instructions 
/// (Arithmetic, Compare, and Logical) can be performed on.
class ArithmeticType : public NumericType
{
public:
  /// for creating custom width IntTypes
  static Type* getIntegeral(int bitWidth, bool isSigned = true);

protected:
  ArithmeticType(BaseType baseType, int bitWidth);
};

/// class FloatType
/// Represents a float as specified by IEEE 754-2008; see 
/// http://en.wikipedia.org/wiki/Floating_point#IEEE_754:_floating_point_in_modern_computers
class FloatType : public ArithmeticType
{
public:
  enum FloatTypes
  {
    HALF = 16,      /*!< A 16 bit IEEE Float  */
    SINGLE = 32,    /*!< A 32 bit IEEE Float  */
    DOUBLE = 64,    /*!< A 64 bit IEEE Float  */
    EXTENDED = 80,  /*!< A 80 bit IEEE Float  */
    QUAD = 128      /*!< A 128 bit IEEE Float */
  };
  
  static Type* get(FloatTypes floatType, highlevel::Module*);
  static Type* getHalf(highlevel::Module*);
  static Type* getSingle(highlevel::Module*);
  static Type* getDouble(highlevel::Module*);
  static Type* getExtended(highlevel::Module*);
  static Type* getQuad(highlevel::Module*);

protected:
  FloatType(int bitWidth);
};

class IntType : public ArithmeticType
{
public:
  enum IntTypes
  {
    CHAR  = 8,   /*!< defaults to UINT */
    SHORT = 8,   /*!< defaults to SINT */
    INT   = 16,  /*!< defaults to SINT */
    LONG  = 32   /*!< defaults to SINT */
  };

  static Type* getChar(highlevel::Module*);  
  static Type* getShort(highlevel::Module*); 
  static Type* getInt(highlevel::Module*);   
  static Type* getLong(highlevel::Module*);  

  static Type* getSigned(IntTypes intType, highlevel::Module*);
  static Type* getUnsigned(IntTypes intType, highlevel::Module*);

protected:
  IntType(BaseType baseType, int bitWidth);
};


/// class PointerType
/// Represents a pointer to a location in memory.
/** 
 *  If a PointerType is constant, it is illegal to perform a StoreInst
 *  on the Value containing it.
 */
class PointerType : public NumericType
{
public:
  static PointerType* Create(Type *pointedTo,
                             highlevel::Module*, 
                             bool isConstant = false);

  Type* getPointedToType();
  
  bool isConstant() const;

protected:
  PointerType(Type *pointedToType, bool constant);

private:
  Type *pointedToType;
  bool constant;
};

/// class ComplexType
/// Represents a Type composed of multiple other Types, essentially a struct
class ComplexType : public Type
{
public:
  static ComplexType* Create(const std::list<Type*>::iterator &types);

  std::list<Type*>::const_iterator& getTypes() const;
  
protected:
  ComplexType(std::list<Type*>::iterator);

private:
  std::list<Type*>::iterator types();
};

/// class FunctionType
/// Contains the necessary return Type and arg Types characteristic of a Function.
class FunctionType : public Type
{
public:
  static FunctionType* Create(const std::list<Type*>::iterator &argTypes,
                              Type *returnType = Type::getVoidType());

  static FunctionType* Create(Type *returnType = Type::getVoidType());

  std::list<Type*>::const_iterator& getArgTypes() const;
  Type* getReturnType() const;

protected:
  FunctionType(Type *returnType, std::list<Type*>::iterator argTypes);

private:
  std::list<Type*>::iterator argTypes;
  Type *returnType;
};

#endif
