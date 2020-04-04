#ifndef GENSTACK_H
#define GENSTACK_H

#include <iostream>

using namespace std;

template<typename T>
class GenStack{
public:

  GenStack();
  GenStack(int size);
  ~GenStack();
  void push(T v);
  T pop();
  bool isEmpty();
  bool isFull();
  void grow();
  int getSize();
  T peek();


private:
  int front;
  int size;
  int arraySize;
  T* array;
};

template<typename T>
GenStack<T>::GenStack(){
  //default constructor
  arraySize = 10;
  array = new T[arraySize];
  size = 0;
  front = -1;
}

template<typename T>
GenStack<T>::GenStack(int size){
  //overloaded constructor
  arraySize = size;
  array = new T[arraySize];
  size = 0;
  front = -1;
}

template<typename T>
GenStack<T>::~GenStack(){
  //delete stuff
  delete array;
}

template<typename T>
void GenStack<T>::push(T v){
  if(isFull()){
    //cout << "stack is full" << endl;
    grow();
  }
  array[++front] = v;
  size++;
}

template<typename T>
T GenStack<T>::pop(){
  if(isEmpty()){
    throw "empty stack exception";
  }
  size--;
  return array[front--];
}

template<typename T>
bool GenStack<T>::isEmpty(){
  return (size == 0);
}

template<typename T>
bool GenStack<T>::isFull(){
  return (arraySize == size);
}

template<typename T>
void GenStack<T>::grow(){
  arraySize*=2;
  T* newArray = new T[arraySize];
  for(int i=0; i<size; ++i){
    newArray[i]= array[i];
  }
  array = newArray;
}

template<typename T>
int GenStack<T>::getSize(){
  return size;
}

template<typename T>
T GenStack<T>::peek(){
  return array[front];
}

#endif
