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
/// Represents a Type that BinaryInst Instructions 
/// (Arithmetic, Compare, and Logical) can be performed on.
class ArithmeticType : public NumericType
{
public:
  /// Represents a float as specified by IEEE 754-2008; see 
  /// http://en.wikipedia.org/wiki/Floating_point#IEEE_754:_floating_point_in_modern_computers
  enum Float
  {
    HALF = 16,      /*!< A 16 bit IEEE Float  */
    SINGLE = 32,    /*!< A 32 bit IEEE Float  */
    DOUBLE = 64,    /*!< A 64 bit IEEE Float  */
    QUAD = 128      /*!< A 128 bit IEEE Float */
  };

  /// Represents the different sizes available for integeral types.
  /// See highlevel::Module for what size is used.
  enum Integeral
  {
    BIT = 1, /*!< UINT and SINT treated the same */
    CHAR,    /*!< defaults to UINT */
    SHORT,   /*!< defaults to SINT */
    INT,     /*!< defaults to SINT */
    LONG     /*!< defaults to SINT */
  };
  
  static Type* getFloat(Float floatType);
  static Type* get(Integeral integerType, highlevel::Module *module); ///< returns the default of signed or unsigned
  static Type* getSigned(Integeral integerType, highlevel::Module *module);
  static Type* getUnsigned(Integeral integerType, highlevel::Module *module);
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
                             bool isImmutable = false);

  Type* getPointedToType();
  
  bool isImmutable() const;

protected:
  PointerType(Type *pointedToType, bool constant);

private:
  Type *pointedToType;
  bool constant;
};

/// class ComplexType
/// Represents a Type composed of multiple other Types, like a struct
class ComplexType : public Type
{
public:
  static ComplexType* Create(const std::list<Type*>::iterator &types);

  std::list<Type*>::iterator getTypes();
  
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

  std::list<Type*>::iterator getArgTypes();
  Type* getReturnType();

protected:
  FunctionType(Type*, std::list<Type*>::iterator);

private:
  std::list<Type*>::iterator argTypes;
  Type *returnType;
};

#endif
