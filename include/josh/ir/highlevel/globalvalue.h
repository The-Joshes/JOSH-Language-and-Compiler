#ifndef __GLOBALVALUE_H__
#define __GLOBALVALUE_H__

#include "josh/ir/highlevel/immutablevalue.h"

/// class GlobalValue
/**
 *
 */
class GlobalValue : public ImmutableValue
{
public:
  bool getExternalVisibility();
  void setExternalVisibility(bool);

protected:
  GlobalValue(bool externalVisibility, Type*, const std::string &name = "");

private:
  bool externalVisibility;
};

#endif
