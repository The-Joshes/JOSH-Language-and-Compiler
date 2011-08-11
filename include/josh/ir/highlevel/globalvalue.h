#ifndef __GLOBALVALUE_H__
#define __GLOBALVALUE_H__

#include "josh/ir/highlevel/immutablevalue.h"

/// class GlobalValue
/// Represents any Value that may be referenced from outside of its Module.
/**
 * GlobalValue includes both Variables and Functions.
 */
class GlobalValue : public ImmutableValue
{
public:
  bool getExternalVisibility()const ;     ///< @see externalVisibility
  void setExternalVisibility(bool);       ///< @see externalVisibility

protected:
  GlobalValue(bool externalVisibility, Type*, const std::string &name = "");

private:
  /// is this GlobalValue visible outside of its Module?
  bool externalVisibility;
};

#endif
