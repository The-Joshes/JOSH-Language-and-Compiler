#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <vector>

namespace josh
{
  template <typename T>
  class Vector
  {
  public:
    unsigned int getSize();
    T get(unsigned int n);
    void insert(unsigned int index, T element);
    void append(T element);
    void prepend(T element);
    void removeAll();
    T &operator[](unsigned int index);
  private:
    std::vector<T> fakeVector;
  };
}

using josh::Vector;

template <typename T> 
unsigned int Vector<T>::getSize()
{
  return fakeVector.size();
}

template <typename T> 
T Vector<T>::get(unsigned int n) 
{
  return fakeVector[n];
}

template <typename T>
void Vector<T>::insert(unsigned int index, T element)
{
  fakeVector[index] = element;
}

template <typename T>
void Vector<T>::append(T element)
{
  fakeVector.push_back(element);
}

template <typename T>
void Vector<T>::prepend(T element)
{
  fakeVector.push_front(element);
}

template <typename T>
void Vector<T>::removeAll()
{
  fakeVector.clear();
}

template <typename T>
T& Vector<T>::operator[](unsigned int index)
{
  return fakeVector[index];
}
#endif
