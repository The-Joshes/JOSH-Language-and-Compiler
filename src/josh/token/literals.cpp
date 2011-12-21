#include "literals.h"

using namespace std;

namespace jtoken {

  Literal::Literal(const string &type, const string &value)
    : type(type), value(value) {}

  void Literal::print(ostream &out) const {
    out << type << " Literal (" << value << ")\n";
  }

  IntLiteral::IntLiteral(const string &value) 
    : Literal("Int", value) {}

  FloatLiteral::FloatLiteral(const string &value) 
    : Literal("Float", value) {}

  StringLiteral::StringLiteral(const string &value) 
    : Literal("String", value) {}

  CharLiteral::CharLiteral(const string &value) 
    : Literal("Char", value) {}

  BoolLiteral::BoolLiteral(const string &value) 
    : Literal("Bool", value) {}

}
