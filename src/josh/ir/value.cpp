#include "josh/ir/value.h"

#include <assert.h>

Type* Value::getType()
{
  return type;
}

bool Value::isConstant()
{
  return isConstantClass;
}

Iterator<Value*>& Value::getUsers()
{
  assert(0 && "Not implemented yet!");
//  return users.iterator();
}

int Value::getNumUsers()
{
  assert(0 && "Not implemented yet!");
}

Iterator<Value*>& Value::getUses()
{
  assert(0 && "Not implemented yet!");
//  return uses.iterator();
}

void Value::replaceAllUsesWith(Value *v)
{
  assert(0 && "Not implemented yet!");
}

Value::~Value()
{
  assert(0 && "Not implemented yet!");
}

void Value::addUser(Value *newUser)
{
  users.append(newUser);
}

bool Value::removeUser(Value *oldUser)
{
  assert(0 && "Not implemented yet!");
}

void Value::addUse(Value *newUse)
{
  // add newUse to the uses list
  uses.append(newUse);

  // add this to newUse's user list
  newUse->addUser(this);
  
  // if newUse is not constant, one more non constant use
  if(!newUse->isConstant())
    numNonConstantUses++;
}

bool Value::removeUse(Value *oldUse)
{
  // remove oldUse from the uses list
  assert(0 && "Not implemented yet!");

  // remove this from oldUse's user list
  oldUse->removeUser(this);

  // if oldUse is not constant, one less non constant use
  if(!oldUse->isConstant())
    numNonConstantUses--;
}

bool Value::allUsesConstant()
{
  return (numNonConstantUses == 0);
}

Value::Value(Type *type, bool isConstant)
{
  // initialize member variables
  // users and uses automatically initialized to empty
  this->type = type;
  this->isConstantClass = isConstant;
  this->numNonConstantUses = 0;
}

int main()
{
  return 0;
}
