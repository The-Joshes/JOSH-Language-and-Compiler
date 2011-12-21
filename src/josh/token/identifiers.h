#ifndef IDENTIFIERS_H
#define IDENTIFIERS_H

#include "josh/token/token.h"

#include <string>

namespace jtoken {

  class Identifier : public Token {
  public:
    Identifier(const std::string &identifier);
    void print(std::ostream&) const;
  private:
    std::string identifier;
  };

}

#endif /* IDENTIFIERS_H */
