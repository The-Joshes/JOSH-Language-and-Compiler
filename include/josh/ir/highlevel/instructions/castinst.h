#ifndef __CAST_H__
#define __CAST_H__

#include "josh/ir/highlevel/instruction.h"

class BasicBlock;
class NumericType;

  /***************************************************************************
   *                          CastInst                                       *
   ***************************************************************************/
/// Does a cast on a Value from one Type to another.
class CastInst : public Instruction
{
public:
  Value* beingCasted(); ///< returns the Value that is being casted

protected:
  CastInst(Value *toCast, Type *newType, BasicBlock *insertAtEnd);

private:
  Value *toCast;
};

  /***************************************************************************
   *                          BitCast                                        *
   ***************************************************************************/
/// class BitCast
class BitCast : public CastInst
{
public:
  enum BitCastType
  {
    UNMODIFIED, /*!< The cast does not modify toCast's bits, but how it is intrepreted by the IR */
    TRUNCTUATE, /*!< Truncuates toCast to newType   */
    ZEXTEND,    /*!< Zero extends toCast to newType */
    SEXTEND     /*!< Sign extends toCast to newType */
  };

  /// if UNMODIFIED: Asserts 0 if toCast's Type and newType have different bit widths.
  /// if TRUNCTUATE: Asserts 0 if toCast's Type has a shorter bitwidth than newType.
  /// if ZEXTEND:    Asserts 0 if toCast's Type has a longer bitwidth than newType.
  /// if SEXTEND:    Asserts 0 if toCast's Type has a longer bitwidth than newType.
  static BitCast* Create(Value *toCast, 
                         Type *newType, 
                         BitCastType castType,
                         BasicBlock *insertAtEnd);

  BitCastType getCastType() const;

protected:
  BitCast(Value *toCast, Type *newType, BitCastType, BasicBlock *insertAtEnd);

private:
  BitCastType castType;
};

  /***************************************************************************
   *                          NumericCast                                    *
   ***************************************************************************/
/// Useful for casting between different numeric and pointer types.
class NumericCast : public CastInst
{
public:
  enum NumericCastType
  {
    IntToFloat, FloatToInt,
    IntToPointer, PointerToInt,
  };
  
  /// If toCast's Type or newType have different bit widths, 0 is asserted.
  /// If toCast's Type or newType are incorrect Types according to the chosen
  /// NumericCastType, 0 is asserted.
  static NumericCast* Create(Value *toCast,
                             Type *newType,
                             NumericCastType castType,
                             BasicBlock *insertAtEnd);

  NumericCastType getCastType() const;

protected:
  NumericCast(Value *toCast, Type *newType, NumericCastType, BasicBlock *insertAtEnd);

private:
  NumericCastType castType;
};

#endif
