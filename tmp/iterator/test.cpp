#include "utils/arraylist.h"
#include <iostream>

using namespace std;
using namespace josh;

int main() {
  ArrayList<int> list;
  list.append(3); 
  list.append(1); 
  list.append(4); 
  list.append(1); 
  list.append(5); 
  list.append(9); 
  list.append(2); 
  
  cout << list[1] << '\n';
  cout << list[6] << '\n';
  cout << list[0] << '\n';
  cout << list[2] << '\n';
  cout << list[4] << '\n';

  cout << "Begin iteration:\n";
  Iterator<int> &it1 = list.iterator();
  Iterator<int> &it2 = list.iterator();
  
  cout << "Iterator1: " << it1.next() << '\n';
  cout << "Iterator1: " << it1.next() << '\n';
  cout << "Iterator1: " << it1.next() << '\n';

  cout << "Iterator2: " << it2.next() << '\n';
  cout << "Iterator2: " << it2.next() << '\n';

  cout << "Iterator1: " << it1.next() << '\n';
  cout << "Iterator1: " << it1.next() << '\n';

  cout << "Iterator2: " << it2.next() << '\n';
  cout << "Iterator2: " << it2.next() << '\n';

  while(it1.hasNext()) 
    cout << "Iterator1: " << it1.next() << '\n';

  while(it2.hasNext())
    cout << "Iterator2: " << it2.next() << '\n';

  cout << "Iterator 1: " << &it1 << '\n';
  cout << "Iterator 2: " << &it2 << '\n';

  list.append(6);
  
  Iterator<int> &it3 = list.iterator();
  cout << "Iterator 3: " << &it3 << '\n';

  while(it1.hasNext())
    cout << "Iterator 1: " << it1.next() << '\n';
  
}
