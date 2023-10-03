#ifndef NODE_H
#define NODE_H
#include <iostream>
using namespace std;


class Node{
  friend class AVLTree;

  private:
  string value;
  int count;
  Node* left;
  Node* right;
  Node* parent;

  public:
  Node(string);

};
#endif

