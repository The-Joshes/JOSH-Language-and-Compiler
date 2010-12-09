#ifndef __CMD_PARSE_H__
#define __CMD_PARSE_H__

#include <iostream>
#include <string>
#include <vector>

struct CMD_FLAG {
  char flag;
  std::string label;
  bool *flagged;
  std::string help;
};

struct CMD_ARG {
  char flag;
  std::string label;
  std::string *val;
  std::string help;
};

struct CMD_LIST {
  char flag;
  std::string label;
  std::vector<std::string> *list;
  std::string help;
};

//Returns the number of errors found in the command-line arguments.
//Errors include trying to use a flag that doesn't exist and providing
//no argument to flags that require an argument.
int cmd_parse(int argc, char **argv, std::vector<std::string> &list,
	      CMD_FLAG *flags, CMD_ARG *args, CMD_LIST *lists);

//Prints a list of the available command-line arguments and flags
//to the provided output stream (cout by default). 
void cmd_help(CMD_FLAG *flags, CMD_ARG *args, CMD_LIST *lists, 
	      std::ostream &out = std::cout);

#endif

