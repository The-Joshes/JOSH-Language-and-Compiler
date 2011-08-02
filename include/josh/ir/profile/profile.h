#ifndef __PROFILE_H__
#define __PROFILE_H__

/// class Profile
/// Contains information regarding the target machine for use in both
/// the HighLevel and LowLevel IR.
/**
 * Profile is an abstract base class.
 */
class Profile
{
public:
  
  int getPointerSize() const; ///< Size of a pointer in bits on the given machine
  int getCharSize() const;    ///< Size of a char in bits on the given machine
  int getShortSize() const;   ///< Size of a short in bits on the given machine
  int getIntSize() const;     ///< Size of an integer in bits on the given machine
  int getLongSize() const;    ///< Size of a long in bits on the given machine

protected:
  Profile();

private:
  int pointerSize, charSize, shortSize, intSize, longSize;
};

#endif
