#include "josh/system/system.h"

#include <iostream>

namespace josh
{
  void lowlevel_to_assembly()
  {
      std::cout << "translating lowlevel IR to assembly...\n";
  }

  void assemble()
  {
      std::cout << "assembling the assembly file to machine code...\n";
  }

  void link()
  {
      std::cout << "linking the object files to form an executable...\n";
  }

  void save_to_file()
  {
      std::cout << "saving the jobj file or library for later use...\n";
  }
}
