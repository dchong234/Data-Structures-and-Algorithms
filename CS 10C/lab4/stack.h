#ifndef STACK_H
#define STACK_H
#include <stdexcept>
using namespace std;

template <typename T>
class stack{
private:
  int size;
  static const int MAX_SIZE = 20;
  T data[MAX_SIZE];

public: 
//Stack Constructor
stack(){
  size = 0;
}
//Pushes value into stack
void push(T val){
  //if the stack is full
  if(size == MAX_SIZE){
    throw out_of_range("Called push on full stack.");
  }
  else{
    data[size] = val;
    size++;
  }
}

//removes the last value in stack
void pop(){
  //if the stack is empty then error
  if(empty()){
    throw out_of_range("Called pop on empty stack.");
  }
  else{
    size--;
  }
}

//Removes the last two values in stack
void pop_two(){
  //if stack is empty
  if(empty()){
    throw out_of_range("Called pop_two on empty stack.");
  }
  //if stack only has 1 item
  else if(size == 1){
    throw out_of_range("Called pop_two on a stack of size 1.");
  }
  else{
    size -= 2;
  }
}

//Returns the last element (top)
T top() const{
  //if stack is empty
  if(empty()){
    throw underflow_error("Called top on empty stack.");
  }
  else{
    return data[size-1];
  }
}
//returns if stack is empty or not
bool empty() const{
  if(size == 0){
    return true;
  }
  else{
    return false;
  }
}
};
#endif