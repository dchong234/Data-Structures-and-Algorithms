#include <iostream>
#include "Node.h"
using namespace std;

//Default Constructor
Node::Node(string data){
  value = data;
  count = 1;
  left = nullptr;
  right = nullptr;
  parent = nullptr;
}

// Overloaded assignment operator
Node &Node::operator=(const Node &data){
    if (this != &data){
        this->value = data.value;
        this->count = data.count;
    }

    return *this;
}
