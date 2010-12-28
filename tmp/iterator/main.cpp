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
}
