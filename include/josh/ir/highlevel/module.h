#ifndef __HL_MODULE_H__
#define __HL_MODULE_H__

#include <string>

class Constant;
class Function;
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
    static Module* Create(Profile *profile);

    const Profile* getProfile() const; 

    std::string getUniqueName();
    bool isNameUnique(const std::string &name) const;
    Value* removeValueWithName(const std::string &name);

    void addFunction(Function*);
    Function* getFunction(std::string &name);

    /// Global Constants must be of Type PointerType, else 0 is asserted.
    void addGlobal(Constant*);
    Constant* getGlobal(std::string &name);

  private:
    Module(Profile*);

    Profile *profile;
  };
}
#endif
