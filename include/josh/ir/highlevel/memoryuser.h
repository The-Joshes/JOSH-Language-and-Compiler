#ifndef __MEMORYUSER_H__
#define __MEMORYUSER_H__

/// class MemoryUser
/// Represents any object which may read or write to memory.
/**
 * If any of the three functions returns false, it is guaranteed
 * that the object in question does not perform that memory related task.
 * If any of the three functions returns true, there is a possibility that
 * memory is used in that way, but no guarantee.
 */
class MemoryUser
{
public:
  /// returns true if the object in question may write to memory 
  /// false otherwise
  bool mayWriteMemory() const;
  
  /// returns true if the object in question may read from memory 
  /// false otherwise
  bool mayReadMemory() const;
 
  /// returns true if the object in question may read or write to memory
  /// false otherwise
  bool mayUseMemory() const;

protected:
  MemoryUser(int numReaders, int numWriters);
  
  void addWriter(int num=1);
  bool removeWriter(int num=1); ///< returns true if there are now 0 writers

  void addReader(int num=1);
  bool removeReader(int num=1); ///< returns true if there are now 0 readers

private:
  int numReaders, numWriters;
};

#endif
