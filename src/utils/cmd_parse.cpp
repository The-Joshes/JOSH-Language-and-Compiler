#include "josh/utils/cmd_parse.h"
#include <cstring>

using namespace std;

static CMD_FLAG *find_flag(char *label, CMD_FLAG *flags);
static CMD_FLAG *find_flag(char label, CMD_FLAG *flags);
static CMD_ARG *find_arg(char *label, CMD_ARG *args);
static CMD_ARG *find_arg(char label, CMD_ARG *args);
static CMD_LIST *find_list(char *label, CMD_LIST *lists);
static CMD_LIST *find_list(char label, CMD_LIST *lists);

int cmd_parse(int argc, char **argv, vector<string> &list, 
              CMD_FLAG *flags, CMD_ARG *args, CMD_LIST *lists) {
  int num_errors = 0;
  for(int i = 1; i < argc; i++) {
    char *param = argv[i];
    int paramlen = strlen(param);
    if(param[0] == '-') {
      if(paramlen > 2 && param[1] == '-') {
        CMD_FLAG *flag = find_flag(param+2, flags);
        CMD_ARG *arg = find_arg(param+2, args);
        CMD_LIST *c_list = find_list(param+2, lists);
        if(flag) 
          *(flag->flagged) = true;
        if(arg) {
          if(i + 1 < argc)
            *(arg->val) = string(argv[++i]);
          else {
            num_errors++;
            cerr << argv[0] << ": Missing argument after " << param << "\n";
          }
        }
        if(c_list) {
          if(i + 1 << argc)
            c_list->list->push_back(string(argv[++i]));
          else {
            num_errors++;
            cerr << argv[0] << ": Missing argument after " << param << "\n";
          }
        }
      if(!flag && !arg && !c_list) {
          num_errors++;
          cerr << argv[0] << ": Invalid argument \"" << param << "\"\n";
        }
      }
      else {
        for(char *c = param + 1; *c; c++) {
          CMD_FLAG *flag = find_flag(*c, flags);
          CMD_ARG *arg = find_arg(*c, args);
          CMD_LIST *c_list = find_list(*c, lists);
          if(flag) 
            *(flag->flagged) = true;
          if(arg) {
            if(i + 1 < argc)
              *(arg->val) = string(argv[++i]);
            else {
              num_errors++;
              cerr << argv[0] << ": Missing argument after -" << *c << "\n";
            }
          }
          if(c_list) {
            if(i + 1 < argc) 
              c_list->list->push_back(string(argv[++i]));
            else {
              num_errors++;
              cerr << argv[0] << ": Missing argument after -" << *c << "\n";
            }
          }
          if(!flag && !arg && !c_list) {
            num_errors++;
            cerr << argv[0] << ": Invalid flag \"-" << *c << "\"\n";
          }     
        }
      }
    }
    else 
      list.push_back(string(param));
  }
  return num_errors;
}

void cmd_help(CMD_FLAG *flags, CMD_ARG *args, CMD_LIST *lists, ostream &out) {
  if(flags) {
    CMD_FLAG *flag = flags;
    if(flag->flag || flag->label != "")
      out << "Flags:\n";
    for(; flag->flag || flag->label != ""; flag++) {
      out << "\t";
      if(flag->flag)
        out << "-" << flag->flag;
      if(flag->label != "") {
        if(flag->flag) 
          out << ", ";
      out << "--" << flag->label;
      }
      out << ": " << flag->help << "\n";
    }
  }

  if(args) {
    CMD_ARG *arg = args;
    if(arg->flag || arg->label != "") 
      out << "Arguments:\n";
    for(; arg->flag || arg->label != ""; arg++) {
      out << "\t";
      if(arg->flag)
        out << "-" << arg->flag;
      if(arg->label != "") {
        if(arg->flag)
          out << ", ";
        out << "--" << arg->label;
    }
      out << " (\"" << *(arg->val) << "\"): " << arg->help << "\n";
    }
  }
   
  if(lists) { 
    CMD_LIST *list = lists;
    if(list->flag || list->label != "")
      out << "Argument Lists:\n";
    for(; list->flag || list->label != ""; list++) {
        out << "\t";
      if(list->flag)
        out << "-" << list->flag;
      if(list->label != "") {
        if(list->flag)
          out << ", ";
        out << "--" << list->label;
      }
      out << ": " << list->help << "\n";
    }
  }
}

static CMD_FLAG *find_flag(char *label, CMD_FLAG *flags) {
  if(flags)
    for(CMD_FLAG *flag = flags; flag->flag || flag->label != ""; flag++)
      if(!strcmp(label, flag->label.c_str()))
        return flag;
  return NULL;
}

static CMD_FLAG *find_flag(char label, CMD_FLAG *flags) {
  if(flags)
    for(CMD_FLAG *flag = flags; flag->flag || flag->label != ""; flag++)
      if(label == flag->flag)
        return flag;
  return NULL;
}

static CMD_ARG *find_arg(char *label, CMD_ARG *args) {
  if(args)
    for(CMD_ARG *arg = args; arg->flag || arg->label != ""; arg++)
      if(!strcmp(label, arg->label.c_str()))
        return arg;
  return NULL;
}

static CMD_ARG *find_arg(char label, CMD_ARG *args) {
  if(args)
    for(CMD_ARG *arg = args; arg->flag || arg->label != ""; arg++)
      if(label == arg->flag)
	return arg;
  return NULL;
}

static CMD_LIST *find_list(char *label, CMD_LIST *lists) {
  if(lists)
    for(CMD_LIST *list = lists; list->flag || list->label != ""; list++)
      if(!strcmp(label, list->label.c_str()))
        return list;
  return NULL;
}

static CMD_LIST *find_list(char label, CMD_LIST *lists) {
  if(lists)
    for(CMD_LIST *list = lists; list->flag || list->label != ""; list++)
      if(label == list->flag)
        return list;
  return NULL;
}

