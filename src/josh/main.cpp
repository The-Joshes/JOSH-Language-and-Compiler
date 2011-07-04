#include "josh/ast/ast.h" 
#include "josh/ir/ir.h"
#include "josh/token/token.h"

using namespace josh;

int main() {
  get_tokens();
  AST ast;
  ast.createIR();
  ir_optimize();
}
