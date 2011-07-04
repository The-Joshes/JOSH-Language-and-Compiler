#include "josh/ir/ir.h"

#include <iostream>

namespace josh 
{
  void optimize_highlevel()
  {
      std::cout << "optimizing high level IR...\n";
  }

  void highlevel_to_lowlevel()
  {
      std::cout << "translating highlevel IR to low level IR...\n";
  }

  void optimize_lowlevel()
  {
      std::cout << "optimizing low level IR...\n";
  }
}
