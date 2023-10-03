#ifndef BSTREE_H
#define BSTREE_H
#include "Node.h"
#include <iostream>
using namespace std;

class BSTree{
  private:
  Node* root;
  // void HelperInsert(Node*, Node*);
  Node* HelperSearch(Node*, const string &)const;
  void HelperRemove(Node*);
  void inOrder(Node *) const;
  void postOrder(Node *) const;
  void preOrder(Node *) const;

  public:
  BSTree();
  ~BSTree();
  bool empty() const;
  void insert(const string &);
  bool search(const string &) const;
  string largest( ) const;
  string smallest( ) const;
  int height(const string &) const;
  void remove(const string &);
  void preOrder() const;
  void postOrder() const;
  void inOrder() const;
};
#endif