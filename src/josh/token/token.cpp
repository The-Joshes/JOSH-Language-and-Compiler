#include "josh/token/token.h"

#include "identifiers.h"
#include "keywords.h"
#include "literals.h"
#include "operators.h"

#include <cctype>
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

  const string state_strings[] = {
    "DEFAULT",
    "INTEGER",
    "FLOAT",
    "STRING",
    "STRINGBACKSLASH",
    "IDENTIFIER",
    "OPERATOR",
    "SLASH",
    "ONELINECOMMENT",
    "MULTILINECOMMENT",
    "MULTILINECOMMENTSTAR", 
  };


  void get_tokens(istream &in, list<Token*> &token_list) {
    TokenState state = DEFAULT;
    char input;
    string token;
    
    input = in.get();
    // Cycles through each character in the input file and separates them
    // into tokens, using the TokenStates to determine how to treat each
    // input character
    while(!in.fail()) {

      cout << "State: " << state_strings[state] << ", Token: \"" << token 
	   << "\", Input: '" << input << '\'' << endl;

      switch(state) {
	
      case DEFAULT:

	if (isdigit(input)) {
	  token.push_back(input);
	  state = INTEGER;
	} else if (isalpha(input) || input == '_') {
	  token.push_back(input);
	  state = IDENTIFIER;
	} else if (input == '"') {
	  state = STRING;
	} else if (input == '/') {
	  state = SLASH;
	} else if (isspace(input)) {
	} else {
	  token.push_back(input);
	  state = OPERATOR;
	}
	
	break;

      case INTEGER:

	if (isdigit(input)) {
	  token.push_back(input);
	} else if (input == '.') {
	  token.push_back(input);
	  state = FLOAT;
	} else {
	  token_list.push_back(new IntLiteral(token));
	  token.clear();
	  state = DEFAULT;
	  in.putback(input);
	}

	break;

      case FLOAT:
	
	if (isdigit(input)) {
	  token.push_back(input);
	} else {
	  token_list.push_back(new FloatLiteral(token));
	  token.clear();
	  state = DEFAULT;
	  in.putback(input);
	}
	
	break;

      case STRING:

	if (input == '\\') {
	  state = STRINGBACKSLASH;
	} else if (input == '\"') {
	  token_list.push_back(new StringLiteral(token));
	  token.clear();
	  state = DEFAULT;
	} else {
	  token.push_back(input);
	}

	break;

      case STRINGBACKSLASH:
	
	switch (input) {
	case 'n':
	  token.push_back('\n');
	  break;

	case 't':
	  token.push_back('\t');
	  break;

	case 'r':
	  token.push_back('\r');
	  break;
	 
	case '0':
	  token.push_back('\0');
	  break;

	default:
	  break;
	}

	state = STRING;

	break;

      case IDENTIFIER:

	if (isalpha(input) || isdigit(input) || input == '_') {
	  token.push_back(input);
	} else {
	  Token *next = Keyword::getKeyword(token);
	  if (!next) {
	    next = new Identifier(token);
	  }
	  token_list.push_back(next);
	  token.clear();
	  state = DEFAULT;
	  in.putback(input);
	}

	break;

      case OPERATOR:

	token.push_back(input);
	if (token.size() == 2) {
	  Token *next = Operator::getDoubleOperator(token);
	  if (next) {
	    token_list.push_back(next);
	    token.clear();
	    state = DEFAULT;
	  } else {
	    next = Operator::getSingleOperator(token[0]);
	    token_list.push_back(next);
	    token.clear();
	    in.putback(input);
	    state = DEFAULT;
	  }
	}

	break;

      case SLASH:

	if (input == '*') {
	  state = MULTILINECOMMENT;
	} else if (input == '/') {
	  state = ONELINECOMMENT;
	} else {
	  in.putback(input);
	  token = "/";
	  state = OPERATOR;
	}

	break;

      case ONELINECOMMENT:

	if (input == '\n') {
	  state = DEFAULT;
	}

	break;

      case MULTILINECOMMENT:

	if (input == '*') {
	  state = MULTILINECOMMENTSTAR;
	}

	break;

      case MULTILINECOMMENTSTAR:

	if (input == '/') {
	  state = DEFAULT;
	} else if (input != '*') {
	  state = MULTILINECOMMENT;
	}

	break;

      }
      
      input = in.get();
    }

    for (list<Token*>::iterator it = token_list.begin();
	 it != token_list.end();
	 it++)
      cout << *(*it) << endl;

  }

  ostream &operator<<(ostream &out, const Token &token) {
    token.print(out);
    return out;
  }

}
