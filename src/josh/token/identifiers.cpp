#include "identifiers.h"

using namespace std;

namespace jtoken {

  Identifier::Identifier(const string &id) :
    identifier(id) {}

  void Identifier::print(ostream &out) const {
    out << "Identifier " << identifier;
  }

}
