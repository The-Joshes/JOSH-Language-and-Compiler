#ifndef __HL_MODULE_H__
#define __HL_MODULE_H__

#include <string>

class Constant;
class Function;
class Profile;
class Value;

/// class HL_Module
/// Contains the complete description and all necessary information
/// of the code being compiled in High Level IR.
class HL_Module
{
public:
  static HL_Module* Create(Profile *profile);

  const Profile* getProfile() const; 

  std::string getUniqueName();
  bool isNameUsed(const std::string &name) const;
  Value* removeValueWithName(const std::string &name);

  Function* getFunction(std::string &name);
  void addFunction(Function*);

  Constant* getGlobal(std::string &name);
  void addGlobal(Constant*);

private:
  HL_Module(Profile*);

  Profile *profile;
};
#endif
