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

josh::Iterator<Value*>& Value::getUsers()
{
  return users.iterator();
}

int Value::getNumUsers()
{
  assert(0 && "Not implemented yet!");
}

josh::Iterator<Value*>& Value::getUses()
{
  return uses.iterator();
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
}

bool Value::removeUse(Value *oldUse)
{
  // remove oldUse from the uses list
  assert(0 && "Not implemented yet!");

  // remove this from oldUse's user list
  oldUse->removeUser(this);
}

Value::Value(Type *type, bool isConstant)
{
  // initialize member variables
  // users and uses automatically initialized to empty
  this->type = type;
  this->isConstantClass = isConstant;
}
