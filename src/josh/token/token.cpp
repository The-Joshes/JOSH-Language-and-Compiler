#include "josh/token/token.h"

#include "identifiers.h"
#include "keywords.h"
#include "literals.h"
#include "operators.h"

#include <iostream>
#include <string>

using namespace std;

namespace jtoken {
  enum TokenState {
    /// The machine has just finished reading a token and is moving onto the
    /// next.
    DEFAULT,

    /// The machine is in the middle of reading an integer value
    INTEGER,

    /// The machine is in the middle of reading a floating point number
    FLOAT,

    /// The machine is in the middle of reading a string literal (between
    /// double quotes)
    STRING,

    /// The machine is in the middle of reading a string literal and has just
    /// read a backslash
    STRINGBACKSLASH,

    /// The machine is in the middle of reading anything that could be a valid
    /// identifier or keyword
    IDENTIFIER,

    /// The machine has just read an operator and is waiting to see if the next
    /// character will form a valid two-character operator
    OPERATOR,

    /// The machine has just read a slash
    SLASH,

    /// The machine is reading a single-line comment and will skip the rest of
    /// the line
    ONELINECOMMENT,

    /// The machine is reading a multi-line comment and will ignore until it 
    /// reaches "*/"
    MULTILINECOMMENT,

    /// The machine is reading a multi-line comment and has just reached a '*'
    MULTILINECOMMENTSTAR, 
  };

  void get_tokens(istream &in, list<Token*> &token_list) {
    TokenState state = DEFAULT;
    char input;
    string token;
    
    input = in.get();
    while(!in.fail()) {

      switch(state) {
	
      case DEFAULT:
	break;

      }
      
      input = in.get();
    }
  }

  ostream &operator<<(ostream &out, const Token &token) {
    token.print(out);
  }

}
