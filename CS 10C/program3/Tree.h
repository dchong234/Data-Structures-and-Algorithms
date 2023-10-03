#ifndef __TREE_H
#define __TREE_H

#include "Node.h"

class Tree {
private:
  Node *root;

public:
  Tree( );
  ~Tree( );
  bool empty();
  void insert(const string &);
  void preOrder( ) const;
  void inOrder( ) const;
  void postOrder( ) const;
  void remove(const string &);
  bool search (const string &) const;
  void rotate(Node*);

private:
  // Add additional functions/variables here
  Node* HelperInsert(Node*, const string &);
  void inOrder(Node *) const;
  void postOrder(Node *) const;
  void preOrder(Node *) const;
};

#endif