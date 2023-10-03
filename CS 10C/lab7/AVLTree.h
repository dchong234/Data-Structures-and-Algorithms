#ifndef AVLTREE_H
#define AVLTREE_H
#include "Node.h"
#include <iostream>
using namespace std;

class AVLTree{
private:
  Node *root;

  void rotate(Node *);
  void rotateLeft(Node *);
  void rotateRight(Node *);
  void setChild(Node *, string, Node *);
  void replaceChild(Node *, Node *, Node *);
  void printBalanceFactors(Node *);
  void visualizeTree(ofstream &, Node *);
  int height(Node *) const;

public:
  AVLTree();
  void insert(const string &);
  int balanceFactor(Node *);
  void printBalanceFactors();
  void visualizeTree(const string &);
};

#endif