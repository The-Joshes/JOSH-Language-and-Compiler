#ifndef __HL_MODULE_H__
#define __HL_MODULE_H__

#include <string>

class Function;
class GlobalValue;
class Profile;
class Value;

/// class Module
/// Contains the complete description and all necessary information
/// of the code being compiled in High Level IR.
namespace highlevel
{
  class Module
  {
  public:
    Module(Profile *profile);

    const Profile* getProfile() const; 

    std::string getUniqueName();
    bool isNameUnique(const std::string &name) const;
    Value* removeValueWithName(const std::string &name);

    void addFunction(Function*);
    Function* getFunction(std::string &name);

    /// Sets the entry point to this Module if one exists.
    /// If Function is not a part of this Module, it is added.
    /// A NULL Function indicates this Module has no main Function.
    void setMainFunction(Function*);
    /// Sets the entry point to this Module if one exists.
    /// The Function must be a part of this Module, else 0 is asserted.
    /// An empty name string indicates this Module has no main Function.
    void setMainFunction(const std::string &name);
    Function* getMainFunction(); 

  private:
    Profile *profile;
  };
}
#endif
