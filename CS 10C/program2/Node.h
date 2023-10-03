#ifndef NODE_H
#define NODE_H
#include <iostream>
using namespace std;


class Node{
  friend class BSTree;

  private:
  string value;
  int count;
  Node* left;
  Node* right;
  Node* parent;

  public:
  Node(string);
  Node &operator=(const Node &data);

};
#endif

