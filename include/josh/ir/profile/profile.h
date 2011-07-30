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
  /// Returns the size of a pointer in bits on the given system.
  int getPointerSize() const;

protected:
  Profile();

private:
};


#endif
