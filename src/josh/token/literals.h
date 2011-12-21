#ifndef LITERALS_H
#define LITERALS_H

#include "josh/token/token.h"

#include <string>

namespace jtoken {
 
  class Literal : public Token {
  public:
    Literal(const std::string &type, const std::string &value);
    void print(std::ostream&) const;
  private:
    std::string type;
    std::string value;
  };

  class IntLiteral : public Literal {
  public:
    IntLiteral(const std::string &value);
  };

  class FloatLiteral : public Literal {
  public:
    FloatLiteral(const std::string &value);
  };

  class StringLiteral : public Literal {
  public:
    StringLiteral(const std::string &value);
  };

  class CharLiteral : public Literal {
  public:
    CharLiteral(const std::string &value);
  };

  class BoolLiteral : public Literal {
  public:
    BoolLiteral(const std::string &value);
  };

}

#endif /* LITERALS_H */
