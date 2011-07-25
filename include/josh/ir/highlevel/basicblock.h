#ifndef __BASICBLOCK_H__
#define __BASICBLOCK_H__

#include "utils/list.h"

class Instruction;
class TerminatorInst;

/// class BasicBlock
/// represents a segment of code that can be entered from the beginning or 
/// exited from the end, but cannot be entered or exited from
/// at any other point.
class BasicBlock : public josh::List<Instruction*>
{
public:
  const josh::List<BasicBlock*>& getPreds(); ///< retrieve the list of predecessors
  const josh::List<BasicBlock*>& getSuccs(); ///< retrieve the list of successors

private:
  josh::List<BasicBlock*> preds, succs;
  josh::List<Instruction*> insts;
  
};

#endif
