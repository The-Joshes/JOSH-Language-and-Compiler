#ifndef __IR_H__
#define __IR_H__

class HL_Module;
class LL_Module;

namespace josh 
{
  void optimize_highlevel(HL_Module*);
  LL_Module* highlevel_to_lowlevel(HL_Module*);
  void optimize_lowlevel(LL_Module*);
}

#endif
