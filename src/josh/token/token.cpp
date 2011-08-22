#include "josh/token/token.h"

#include "keywords.h"

#include <iostream>
#include <string>

using namespace std;

namespace jtoken {
  
  void get_tokens(istream in) {
    string keyword;
    in >> keyword;
    Token *token = Keyword::getKeyword(keyword);
    if (!token) {
      token = new Identifier(keyword);
    }
    cout << token;
  }

  ostream &operator<<(ostream &out, const Token &token) {
    token.print(out);
  }

}
