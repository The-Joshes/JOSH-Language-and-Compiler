#include "josh/ast/ast.h"

#include <iostream>

namespace josh {
  
  AST::AST() {
    std::cout << "Constructing AST...\n";
  }

  void AST::createIR() {
    std::cout << "Creating IR from AST...\n";
  }
  
}
