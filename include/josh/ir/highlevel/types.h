#ifndef __TYPES_H__
#define __TYPES_H__

#include <list>

#include "josh/ir/highlevel/type.h"

class Profile;

/// class NumericType
/// Represents INTEGER and FLOAT Types.
class NumericType : public Type
{
public:
  /// Represents a float as specified by IEEE 754-2008; see 
  /// http://en.wikipedia.org/wiki/Floating_point#IEEE_754:_floating_point_in_modern_computers
  enum IEEFloat
  {
    HALF = 16,      /*!< A 16 bit IEEE Float  */
    SINGLE = 32,    /*!< A 32 bit IEEE Float  */
    DOUBLE = 64,    /*!< A 64 bit IEEE Float  */
    QUAD = 128      /*!< A 128 bit IEEE Float */
  };

  /// Represents the different sizes available for integeral types.
  /// See Profile for what size is used.
  enum Integeral
  {
    BIT = 1,
    CHAR,
    SHORT,
    INT,
    LONG
  };
  
  static Type* getIEEFloat(IEEFloat floatType);
  static Type* getIntegerType(Integeral integerType, Profile *profile);
};


/// class PointerType
/// Represents a pointer to a location in memory.
class PointerType : public Type
{
public:
  static PointerType* Create(Type *pointedTo);

  Type* getPointedToType();

protected:
  PointerType(Type *pointedToType);

private:
  Type *pointedToType;
};

/// class ComplexType
/// Represents a Type composed of multiple other Types, like a struct
class ComplexType : public Type
{
public:
  /// If canPack is true, the Types are rearranged to try minimizing the
  /// memory footprint of the ComplexType.  Otherwise, the Types are left
  /// in their original order.
  /// If more fine tuned control is needed (ex can do ADD but not DIVIDE),
  /// then we'll have to figure out an additional factory method.
  static ComplexType* Create(const std::list<Type*>::iterator &types,
                             bool validForArithmeticOp,
                             bool validForCompareOp,
                             bool canPack = false);

  std::list<Type*>::iterator getTypes();
  
  /// Is it valid to perform op on this type of Type?
  virtual bool isValidFor(BinaryOp op);

protected:
  ComplexType(std::list<Type*>::iterator);
  bool validForArithmeticOp, validForCompareOp;

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

  std::list<Type*>::iterator getArgTypes();
  Type* getReturnType();

protected:
  FunctionType(Type*, std::list<Type*>::iterator);

private:
  std::list<Type*>::iterator argTypes;
  Type *returnType;
};

#endif
