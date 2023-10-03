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
