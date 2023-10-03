#include <iostream>
#include "IntList.h"
using namespace std;

//Default constructor
IntList::IntList(){
  dummyHead = new IntNode(0);
  dummyTail = new IntNode(0);
  dummyHead->next = dummyTail;
  dummyHead->prev = dummyTail;
  dummyTail->prev = dummyHead;
  dummyTail->next = dummyHead;
}
//Destructor
IntList::~IntList(){
  IntNode* curr = dummyHead->next;
  while(curr != dummyTail){
    IntNode* temp = curr->next;
    delete curr;
    curr = temp;
  }
}
//push_front function
void IntList::push_front(int value){
  IntNode* node = new IntNode(value);
  if(empty()){
    dummyHead->next = node;
    node->next = dummyTail;
    dummyTail->prev = node;
    node->prev = dummyHead;
  }
  else{
  IntNode* curr = dummyHead->next;
  dummyHead->next = node;
  node->next = curr;
  curr->prev = node;
  node->prev = dummyHead;
  }
}
//pop_front function
void IntList::pop_front(){
  if(!empty()){
    IntNode* curr = dummyHead->next;
    dummyHead->next = curr->next;
    curr->next->prev = dummyHead;
    delete curr;
  }
}
//push_back function
void IntList::push_back(int value){
  IntNode *node = new IntNode(value);
  if (empty())
    {
        dummyHead->next = node;
        node->next = dummyTail;
        dummyTail->prev = node;
        node->prev = dummyHead;
    }

    else
    {
        IntNode *curr = dummyTail->prev;
        curr->next = node;
        node->next = dummyTail;
        dummyTail->prev = node;
        node->prev = curr;
    }
}
//pop_back function
void IntList::pop_back(){
  if(!empty()){
    IntNode* curr = dummyTail->prev;
    dummyTail->prev = curr->prev;
    curr->prev->next = dummyTail;
    delete curr;
  }
}
//empty function
bool IntList::empty() const{
  if(dummyHead->next != dummyTail){
    return false;
  }
  else{
    return true;
  }
}
//friend fucntion
ostream & operator<<(ostream &out, const IntList &rhs){
  if(!rhs.empty()){
    IntNode* curr = rhs.dummyHead->next;
    while(curr->next != rhs.dummyTail){
      out << curr->data << " ";
      curr = curr->next;
    }
    out << curr->data;
  }
  return out;
}
//printReverse function
void IntList::printReverse() const{
  IntNode* curr = dummyTail->prev;
  while(curr != dummyHead){
    cout << curr->data << " ";
    curr = curr->prev;
  }
}