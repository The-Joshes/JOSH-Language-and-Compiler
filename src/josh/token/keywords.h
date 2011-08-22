#ifndef KEYWORDS_H
#define KEYWORDS_H

#include "include/josh/token/token.h"

#include <map>
#include <string>

namespace jtoken {

  class Keyword : public Token {
  public:
    Keyword(const std::string &keyword);
    void print(std::ostream &out) {out << "Keyword " << keyword;}

    static Keyword *getKeyword(const std::string &keyword);

  private:
    std::string keyword;

    static std::map<std::string, (Keyword*)()> keyword_map;
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
