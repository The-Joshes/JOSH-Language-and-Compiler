#ifndef __TYPE_H__
#define __TYPE_H__

class BinaryOp;

///  class Type
/// Describes a Value's Type.
/**
 * Type is an abstract concept detailing how the software should intrepret
 * a set of bits supplied by the hardware.  JOSH IR is strictly typed;
 * that is, Values of two different Types cannot be used in operations
 * such as BinaryInsts.  Generally, if the specific BaseType has no
 * subclass, it has a factory method inside class Type.  Otherwise,
 * the factory method(s) for a given Type are located inside the
 * subclass' definition.
 */
class Type
{
public:
  /// Describes the underlying type of this Type.
  /// Since not all Types (like VOID) have their own subclass,
  /// dynamic casting cannot be used and therefore this abstraction
  /// is needed to determine a Type's actual type.
  enum BaseType
  {
    VOID, INTEGER, DECIMAL, 
    POINTER,  /*!< a Type that points to an address in memory               */
    COMPLEX,  /*!< a Type composed of multiple other Types, like a a struct */
    FUNCTION, /*!< a Type containing a returnType and argumentTypes         */
    LABEL     /*!< a Type that can be branched to; see BasicBlock           */
  };

  static Type* getVoidType();
  static Type* getIntType(int bitWidth);
  static Type* getLabelType();

  /// Returns an enum detailing the exact type this Type describes.
  /// For example, to check if a type is an integer, do
  /// (type->getBaseType() == Type::INTEGER)
  BaseType getBaseType() const;
  
  int getBitWidth() const; ///< the size of this Type in bits
  
  /// Is it valid to perform op on this type of Type?
  virtual bool isValidFor(BinaryOp op);

protected:
  Type(BaseType baseType);

private:
  BaseType baseType; ///< the exact type this Type describes
};

#endif
