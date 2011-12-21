#ifndef KEYWORDS_H
#define KEYWORDS_H

#include "josh/token/token.h"

#include <map>
#include <string>

namespace jtoken {

  class Keyword;
  
  /// This represents a function that returns a Keyword* with no parameters
  /// It is used for the keyword_map
  typedef Keyword* (*keyword_map_fp_t)();
  
  class Keyword : public Token {
  public:
    Keyword(const std::string &keyword) : keyword(keyword) {}
    void print(std::ostream &out) const {out << "Keyword " << keyword;}

    /// Static function to return the keyword corresponding to a given
    /// string or null, if the given string does not correspond to a
    /// keyword.
    static Keyword *getKeyword(const std::string &keyword);

  private:
    std::string keyword;
    
    // Used by the function getKeyword to efficiently return the keyword.
    static std::map<std::string, keyword_map_fp_t> keyword_map;
    static bool init;
  };



  /************************************************************
   * Control Flow                                             *
   ************************************************************/

  class If : public Keyword {
  public:
    If() : Keyword("if") {}
  };

  class For : public Keyword {
  public:
    For() : Keyword("for") {}
  };

  class While : public Keyword {
  public:
    While() : Keyword("while") {}
  };

  class Do : public Keyword {
  public:
    Do() : Keyword("do") {}
  };

  class Switch : public Keyword {
  public:
    Switch() : Keyword("switch") {}
  };

  class Break : public Keyword {
  public:
    Break() : Keyword("break") {}
  };


  /************************************************************
   * OO and Polymorphism                                      *
   ************************************************************/

  class Class : public Keyword {
  public:
    Class() : Keyword("class") {}
  };

  class Struct : public Keyword {
  public:
    Struct() : Keyword("struct") {}
  };

  class Extends : public Keyword {
  public:
    Extends() : Keyword("extends") {}
  };

  class Abstract : public Keyword {
  public:
    Abstract() : Keyword("abstract") {}
  };

  class Final : public Keyword {
  public:
    Final() : Keyword("final") {}
  };

  class Const : public Keyword {
  public:
    Const() : Keyword("const") {}
  };


  /************************************************************
   * Primitive Types                                          *
   ************************************************************/

  class Int : public Keyword {
  public:
    Int() : Keyword("int") {}
  };

  class Char : public Keyword {
  public:
    Char() : Keyword("char") {}
  };

  class Bool : public Keyword {
  public:
    Bool() : Keyword("bool") {}
  };

}

#endif /* KEYWORDS_H */
