#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <list>

namespace jtoken {

  /// class Token
  /// Represents a JOSH token. Subclasses of class Token represent different
  /// kinds of tokens.
  class Token {
  public:
    virtual void print(std::ostream&) const = 0;
  };

  void get_tokens(std::istream&, std::list<Token*>&);
  std::ostream &operator<<(std::ostream&, const Token&);

}

#endif /* TOKEN_H */
