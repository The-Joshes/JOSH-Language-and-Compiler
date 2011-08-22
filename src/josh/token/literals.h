#ifndef LITERALS_H
#define LITERALS_H

#include "josh/token/token.h"
#include <string>

namespace jtoken {
 
  class IntLiteral : public Token {
  public:
    IntLiteral(int value);
    void print(std::ostream&);
  private:
    int value;
  };

  class FloatLiteral : public Token {
  public:
    FloatLiteral(float value);
    void print(std::ostream&);
  private:
    float value;
  };

  class StringLiteral : public Token {
  public:
    StringLiteral(const string &value);
    void print(std::ostream&);
  private:
    string value;
  };

  class CharLiteral : public Token {
  public:
    CharLiteral(char value);
    void print(std::ostream&);
  private:
    char value;
  };

  class BoolLiteral : public Token {
  public:
    BoolLiteral(bool value);
    void print(std::ostream&);
  private:
    bool value;
  };

}

#endif /* LITERALS_H */
