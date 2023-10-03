#include <iostream>
#include "Node.h"
using namespace std;

//Default Constructor
Node::Node(){
  left = nullptr;
  right = nullptr;
  middle = nullptr;
  parent = nullptr;
  small = "";
  large = "";
}

Node::Node(const string& value){
  left = nullptr;
  right = nullptr;
  middle = nullptr;
  parent = nullptr;
  small = value;
  large = "";
}

bool Node::twoStrings()const{
  return !large.empty();
}