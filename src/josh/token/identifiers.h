#ifndef IDENTIFIERS_H
#define IDENTIFIERS_H

namespace jtoken {

  class Identifier : public Token {
  public:
    Identifier(const string &identifier);
    void print(std::ostream&);
  private:
    string identifier;
  };

}

#endif /* IDENTIFIERS_H */
