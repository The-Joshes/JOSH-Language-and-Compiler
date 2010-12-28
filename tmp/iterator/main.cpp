#include "array.h"
#include <iostream>

using namespace std;

int main() {
  Array<int> array;
  array.append(3); 
  array.append(1); 
  array.append(4); 
  array.append(1); 
  array.append(5); 
  array.append(9); 
  array.append(2); 
  
  cout << array[1] << '\n';
  cout << array[6] << '\n';
  cout << array[0] << '\n';
  cout << array[2] << '\n';
  cout << array[4] << '\n';

  cout << "Begin iteration:\n";
  Iterator<int> &it1 = array.iterator();
  Iterator<int> &it2 = array.iterator();
  
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

  array.append(6);
  
  Iterator<int> &it3 = array.iterator();
  cout << "Iterator 3: " << &it3 << '\n';
  
}
