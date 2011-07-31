#ifndef __IR_H__
#define __IR_H__

namespace highlevel
{
  class Module;
}

namespace lowlevel
{
  class Module;
}

namespace josh 
{
  void optimize_highlevel(highlevel::Module*);
  lowlevel::Module* highlevel_to_lowlevel(highlevel::Module*);
  void optimize_lowlevel(lowlevel::Module*);
}

#endif
