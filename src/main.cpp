#include "josh/ast/ast.h" 
//#include "josh/ir/ir.h"
#include "josh/system/system.h"
#include "josh/token/token.h"
#include <iostream>
#include "config.h"

using namespace std;
using namespace josh;
using namespace jtoken;

int main() {
  cout << "Welcome to " << PACKAGE_STRING  << "\n";

  list<Token*> token_list;
  get_tokens(cin, token_list);
  AST ast;
  ast.createIR();

  /*optimize_highlevel();
  highlevel_to_lowlevel();
  optimize_lowlevel();
  */

  lowlevel_to_assembly();
  assemble();
  //link(); // you don't both link and save to file
  save_to_file();

  return 0;
}
