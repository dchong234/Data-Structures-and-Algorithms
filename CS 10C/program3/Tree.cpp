#include <iostream>
#include "Tree.h"
#include "Node.h"
using namespace std;

//Default constructor
Tree::Tree(){
  root = nullptr;
}

//Destructor
Tree::~Tree(){
  delete root;
}

bool Tree::empty(){
  return root == nullptr;
}

//return true or false if wanted string is in tree
bool Tree::search(const string &value) const
{
  //of the tree is empty, end
  if (root == nullptr)
  {
    return false;
  }

  Node* currNode = root;

  while(currNode){
    //if the key matches the given node, return node
    if (currNode->small == value || (currNode->large == value && currNode->twoStrings())){
      return true;
    }

    else{
      //if string is less than small, go left
      if (currNode->small > value){
          currNode = currNode->left;
      }

      else{
        //if string is greater than large, go right
        if (currNode->large < value && currNode->twoStrings()){
          currNode = currNode->right;
        }
        //if only one child or is in between small and large, go middle
        else{
          currNode = currNode->middle;
        }
      }
    }
  }
  return false;
}


void Tree::insert(const string &value){
  if(empty()){
    root = new Node(value);
  }
  else if(!search(value)){
    HelperInsert(root, value);
  }
}
//inserts a new node into the tree
Node* Tree::HelperInsert(Node* currNode, const string &value){
  if(!root){
    //If tree is empty, create a new node as root and set its value
    root = new Node();
    root->small = value;
  }
  else{
    //Traverse the tree to find the correct position for the new value
    while(currNode->left){
      //if current node has twp strings, choose the right subtree
      if(currNode->twoStrings()){
        if(currNode->small > value){
          currNode = currNode->left;
        }
        else if(currNode->large < value){
          currNode = currNode->right;
        }
        else{
          currNode = currNode->middle;
        }
      }
      //if current node has only one string, choose the middle or left subtree based on the value
      else if(currNode->small > value){
        currNode = currNode->left;
      }
      else{
        currNode = currNode->middle;
      }
    }
    //there are two possibilities when the correct node is found
    if(currNode->twoStrings()){
      //three strings to split node into 3 nodes
      string small, middle, large;

      //determone new order of the 3 strings
      if(currNode->small > value){
        small = value;
        middle = currNode->small;
        large = currNode->large;
      }
      else{
        small = currNode->small;
        if(currNode->large < value){
          middle = currNode->large;
          large = value;
        }
        else{
          middle = value;
          large = currNode->large;
        }
      }

      //create two new nodes for the small and large strings
      Node* smallNode = new Node();
      smallNode->small = small;
      Node* largeNode = new Node();
      largeNode->small = large;

      //Update the current node with the middle string and the two new nodes as its children
      currNode->small = middle;
      currNode->large = "";
      currNode->left = smallNode;
      currNode->middle = largeNode;
      currNode->right = nullptr;

      // Update the parent pointers of the two new nodes
      smallNode->parent = currNode;
      largeNode->parent = currNode;

      //rotate to ensure tree remains balanced
      rotate(currNode);
    }
    else{
      //if current node has only one string, add new string as the second string
      if(currNode->small > value){
        currNode->large = currNode->small;
        currNode->small = value;
      }
      else{
        currNode->large = value;
      }
    }
  }
}

//rotates nodes in order to keep the tree balanced
void Tree::rotate(Node* node){
  //needs a parent so that it can move up to its parent
  if(node->parent){
    Node* parent = node->parent;
    if(parent->twoStrings()){
      //if node's value is smaller than the two strings
      if(parent->small > node->small){
        Node* large = new Node();
        //large node takes the parent's middle and right children
        large->left = parent->middle;
        large->left->parent = large;
        large->middle = parent->right;
        large->middle->parent = large;
        large->small = parent->large;

        //reset and insert node
        parent->left = node;
        parent->middle = large;
        parent->right = nullptr;
        parent->large = "";

        //link the two
        large->parent = parent;
      }
      //if node's value is larger than the two strings
      else if(parent->large < node->small){
        Node* small = new Node();
        //small node takes the parent's left and middle children
        small->left = parent->left;
        small->left->parent = small;
        small->middle = parent->middle;
        small->middle->parent = small;
        small->small = parent->small;

        //Reset and insert node
        parent->left = small;
        parent->middle = node; 
        parent->right = nullptr;
        parent->small = parent->large;
        parent->large = ""; 

        //link the two
        small->parent = parent;
      }
      //if node's values are in between the two strings
      else{
        Node* small = new Node();
        small->small = parent->small;
        small->left = parent->left;
        small->left->parent = small;
        small->middle = node->left;
        small->middle->parent = small;

        Node* large = new Node();
        large->small = parent->large;
        large->left = node->middle;
        large->left->parent = large;
        large->middle = parent->middle;
        large->middle->parent = large;

        //reset and insert
        parent->left = small;
        parent->middle = large;
        parent->right = nullptr;
        parent->small = node->small;
        parent->large = ""; // Reset to empty

        //link the two
        small->parent = parent;
        large->parent = parent;

        delete node;
      }
      rotate(parent);
    }

    //
    else{
      //the node's string is smaller
      if (parent->small > node->small)
      {
        parent->large = parent->small;
        parent->small = node->small;

        //the node's left and middle are placed onto the parent's left and middle
        parent->left = node->left;
        parent->right = parent->middle;
        parent->middle = node->middle;
      }
      //the node's string is larger
      else
      {
        parent->large = node->small;
        //the node's left and middle are placed onto the parent's middle and right
        parent->middle = node->left;
        node->left->parent = parent;
        parent->right = node->middle;
        node->middle->parent = parent;
      }

      //Update both the parent pointers
      node->left->parent = parent;
      node->middle->parent = parent;
      delete node;
    }
  }
}

//removes a node from the tree
void Tree::remove(const string &value){
  Node* currNode = root;
  //Traverse the tree to find the Node with the value
  while(currNode){
    //If the Node is found, break out of the loop
    if(currNode->small == value || (currNode->twoStrings() && currNode->large == value)){
      break;
    }
    //Otherwise, continue traversing the tree
    else{
      if(currNode->small > value){
        currNode = currNode->left;
      }
      else{
        if(currNode->twoStrings() && currNode->large < value){
          currNode = currNode->right;
        }
        else{
          currNode = currNode->middle;
        }
      }
    }
  }
  //If the Node with the value was found
  if(currNode){
    //If the Node has two strings
    if(currNode->twoStrings()){
      //If the value is in the smaller string, replace it with the larger string
      if(value == currNode->small){
        currNode->small = currNode->large;
        currNode->large = "";
      }
      //If the value is in the larger string, set the larger string to empty
      else{
        currNode->large = "";
      }
    }
    //If the Node has only one string
    else{
      Node* parent = currNode->parent;
      //If the Node has a parent
      if(parent){
        //If the Node is the left child of the parent
        if(value < parent->small){
          //Remove the Node and adjust the parent's left and middle children
          parent->left = nullptr;
          parent->large = parent->middle->small;
          parent->middle = nullptr;
        }
        //If the Node is the middle child of the parent
        else{
          //Remove the Node and adjust the parent's middle and left children
          parent->middle = nullptr;
          parent->large = parent->small;
          parent->small = parent->left->small;
          parent->left = nullptr;
        }
      }
      //If the Node is the root
      else{
        //If the root has two children
        Node* tempNode = new Node();
        if(root->left){
          //Create a new Node to become the new root and adjust its children
          tempNode->small = root->left->small;
          tempNode->large = root->middle->small;
          root = tempNode;
        }
        //If the root has only one child, set the root to nullptr
        else{
          root = nullptr;
        }
      }
    }
  }
}


void Tree::preOrder() const{
  preOrder(root);
  cout << endl;
}

void Tree::inOrder() const{
  inOrder(root);
  cout << endl;
}

void Tree::postOrder() const{
  postOrder(root);
  cout << endl;
}

void Tree::preOrder(Node *node) const
{
  if(node)
  {
    if (node->twoStrings())
    {
      cout << node->small << ", ";
      preOrder(node->left);
      cout << node->large << ", ";
      preOrder(node->middle);
      preOrder(node->right);
    }
    else
    {
      cout << node->small << ", ";
      preOrder(node->left);
      preOrder(node->middle);
    }
  }
}

void Tree::inOrder(Node *node) const
{
  if(node)
  {
    inOrder(node->left);
    cout << node->small << ", ";
    inOrder(node->middle);

    // There are two strings in the node
    if (node->twoStrings())
    {
      cout << node->large << ", ";
      inOrder(node->right);
    }
  }
}

void Tree::postOrder(Node *node) const
{
  if (node)
  {
    if (node->twoStrings())
    {
      postOrder(node->left);
      postOrder(node->middle);
      cout << node->small << ", ";
      postOrder(node->right);
      cout << node->large << ", ";
    }
    else
    {
      postOrder(node->left);
      postOrder(node->middle);
      cout << node->small << ", ";
    }
  }
}