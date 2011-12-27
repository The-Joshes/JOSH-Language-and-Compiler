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

  class IfKeyword : public Keyword {
  public:
    IfKeyword() : Keyword("if") {}
  };

  class ForKeyword : public Keyword {
  public:
    ForKeyword() : Keyword("for") {}
  };

  class WhileKeyword : public Keyword {
  public:
    WhileKeyword() : Keyword("while") {}
  };

  class DoKeyword : public Keyword {
  public:
    DoKeyword() : Keyword("do") {}
  };

  class SwitchKeyword : public Keyword {
  public:
    SwitchKeyword() : Keyword("switch") {}
  };

  class BreakKeyword : public Keyword {
  public:
    BreakKeyword() : Keyword("break") {}
  };


  /************************************************************
   * OO and Polymorphism                                      *
   ************************************************************/

  class ClassKeyword : public Keyword {
  public:
    ClassKeyword() : Keyword("class") {}
  };

  class StructKeyword : public Keyword {
  public:
    StructKeyword() : Keyword("struct") {}
  };

  class ExtendsKeyword : public Keyword {
  public:
    ExtendsKeyword() : Keyword("extends") {}
  };

  class AbstractKeyword : public Keyword {
  public:
    AbstractKeyword() : Keyword("abstract") {}
  };

  class FinalKeyword : public Keyword {
  public:
    FinalKeyword() : Keyword("final") {}
  };

  class ConstKeyword : public Keyword {
  public:
    ConstKeyword() : Keyword("const") {}
  };


  /************************************************************
   * Primitive Types                                          *
   ************************************************************/

  class IntKeyword : public Keyword {
  public:
    IntKeyword() : Keyword("int") {}
  };

  class CharKeyword : public Keyword {
  public:
    CharKeyword() : Keyword("char") {}
  };

  class BoolKeyword : public Keyword {
  public:
    BoolKeyword() : Keyword("bool") {}
  };

}

#endif /* KEYWORDS_H */
