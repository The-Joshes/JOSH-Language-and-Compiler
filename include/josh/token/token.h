#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>

namespace jtoken {

  enum TokenType {
    /* Identifiers */
    
    /// This token type corresponds to any token that is a valid variable name,
    /// beginning with a letter or underscore (a-z, A-Z, _), and continuing with
    /// a sequence of letters, numbers, and underscores until the next character
    /// is not one of those (operator or space, most likely)
    TT_IDENTIFIER,
    
    
    /* Literals */
    
    /// One of two options
    /// ', then a single character other than \, followed by a closing '
    /// '\, then a single valid escape character (\nt0), followed by a closing '
    TT_CHAR_LITERAL,
    TT_INT_LITERAL,
    TT_BOOL_LITERAL,
    TT_FLOAT_LITERAL,
    TT_STRING_LITERAL,
  
    
    /* Operators */
    TT_PLUS,
    TT_MINUS,
    TT_STAR,
    TT_SLASH,
    TT_ASSIGN,
    
  };
    
  struct Token {
    TokenType type;
    union {
      char char_val;
      int int_val;
      bool bool_val;
      float float_val;
      char *str_val;
    };
  };

  void get_tokens(std::istream&);
}

#endif /* TOKEN_H */
