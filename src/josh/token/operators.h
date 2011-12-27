#ifndef OPERATORS_H
#define OPERATORS_H

#include "josh/token/token.h"

#include <map>
#include <string>

namespace jtoken {

  class Operator;

  typedef Operator* (*operator_fp_t)();

  class Operator : public Token {
  public:
    Operator(const std::string &opstring) : opstring(opstring) {}
    void print(std::ostream &out) const {out << "Operator " << opstring;}

    static Operator *getSingleOperator(char opchar);
    static Operator *getDoubleOperator(const std::string &opstring);

  private:
    std::string opstring;

    static std::map<char, operator_fp_t> single_operator_map;
    static bool single_init;

    static std::map<std::string, operator_fp_t> double_operator_map;
    static bool double_init;
  };


  /************************************************************
   * Single-Char Operators                                    *
   ************************************************************/

  class PlusOperator : public Operator {
  public:
    PlusOperator() : Operator("+") {}
  };

  class SubtractOperator : public Operator {
  public:
    SubtractOperator() : Operator("-") {}
  };

  class StarOperator : public Operator {
  public:
    StarOperator() : Operator("*") {}
  };

  class SlashOperator : public Operator {
  public:
    SlashOperator() : Operator("/") {}
  };

  class AssignOperator : public Operator {
  public:
    AssignOperator() : Operator("=") {}
  };

  class LessOperator : public Operator {
  public:
    LessOperator() : Operator("<") {}
  };

  class GreaterOperator : public Operator {
  public:
    GreaterOperator() : Operator(">") {}
  };

  class AmpersandOperator : public Operator {
  public:
    AmpersandOperator() : Operator("&") {}
  };

  class CaratOperator : public Operator {
  public:
    CaratOperator() : Operator("^") {}
  };

  class PercentOperator : public Operator {
  public:
    PercentOperator() : Operator("%") {}
  };

  class DollarOperator : public Operator {
  public:
    DollarOperator() : Operator("$") {}
  };

  class PoundOperator : public Operator {
  public:
    PoundOperator() : Operator("#") {}
  };

  class AtOperator : public Operator {
  public:
    AtOperator() : Operator("@") {}
  };

  class BangOperator : public Operator {
  public:
    BangOperator() : Operator("!") {}
  };

  class BarOperator : public Operator {
  public:
    BarOperator() : Operator("|") {}
  };

  class SemicolonOperator : public Operator {
  public:
    SemicolonOperator() : Operator(";") {}
  };

  class ColonOperator : public Operator {
  public:
    ColonOperator() : Operator(":") {}
  };

  class DotOperator : public Operator {
  public:
    DotOperator() : Operator(".") {}
  };

  class CommaOperator : public Operator {
  public:
    CommaOperator() : Operator(",") {}
  };

  class QuestionOperator : public Operator {
  public:
    QuestionOperator() : Operator("?") {}
  };

  class TildeOperator : public Operator {
  public:
    TildeOperator() : Operator("~") {}
  };

  class OpenParenOperator : public Operator {
  public:
    OpenParenOperator() : Operator("(") {}
  };

  class CloseParenOperator : public Operator {
  public:
    CloseParenOperator() : Operator(")") {}
  };

  class OpenBracketOperator : public Operator {
  public:
    OpenBracketOperator() : Operator("[") {}
  };

  class CloseBracketOperator : public Operator {
  public:
    CloseBracketOperator() : Operator("]") {}
  };

  class OpenBraceOperator : public Operator {
  public:
    OpenBraceOperator() : Operator("{") {}
  };

  class CloseBraceOperator : public Operator {
  public:
    CloseBraceOperator() : Operator("}") {}
  };



  /************************************************************
   * Double-Char Operators                                    *
   ************************************************************/

  class IncrementOperator : public Operator {
  public:
    IncrementOperator() : Operator("++") {}
  };

  class DecrementOperator : public Operator {
  public:
    DecrementOperator() : Operator("--") {}
  };

  class EqualsOperator : public Operator {
  public:
    EqualsOperator() : Operator("==") {}
  };

  class NotEqualOperator : public Operator {
  public:
    NotEqualOperator() : Operator("!=") {}
  };

  class LTEOperator : public Operator {
  public:
    LTEOperator() : Operator("<=") {}
  };

  class GTEOperator : public Operator {
  public:
    GTEOperator() : Operator(">=") {}
  };

  class AndOperator : public Operator {
  public:
    AndOperator() : Operator("&&") {}
  };

  class OrOperator : public Operator {
  public:
    OrOperator() : Operator("||") {}
  };

  class PlusEqualsOperator : public Operator {
  public:
    PlusEqualsOperator() : Operator("+=") {}
  };

  class MinusEqualsOperator : public Operator {
  public:
    MinusEqualsOperator() : Operator("-=") {}
  };

  class TimesEqualsOperator : public Operator {
  public:
    TimesEqualsOperator() : Operator("*=") {}
  };

  class DivideEqualsOperator : public Operator {
  public:
    DivideEqualsOperator() : Operator("/=") {}
  };

  class ModEqualsOperator : public Operator {
  public:
    ModEqualsOperator() : Operator("%=") {}
  };

  class AndEqualsOperator : public Operator {
  public:
    AndEqualsOperator() : Operator("&=") {}
  };

  class OrEqualsOperator : public Operator {
  public:
    OrEqualsOperator() : Operator("|=") {}
  };

  class CaratEqualsOperator : public Operator {
  public:
    CaratEqualsOperator() : Operator("^=") {}
  };

  class InsertionOperator : public Operator {
  public:
    InsertionOperator() : Operator("<<") {}
  };

  class ExtractionOperator : public Operator {
  public:
    ExtractionOperator() : Operator(">>") {}
  };

  class ArrowOperator : public Operator {
  public:
    ArrowOperator() : Operator("->") {}
  };

  class ScopeOperator : public Operator {
  public:
    ScopeOperator() : Operator("::") {}
  };

}

#endif /* OPERATORS_H */
