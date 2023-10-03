#include <iostream>
#include "BSTree.h"
#include "Node.h"
using namespace std;

//Default constructor
BSTree::BSTree(){
  root = nullptr;
}

//Destructor
BSTree::~BSTree(){
  delete root;
}

//checks if tree is empty
bool BSTree::empty() const{
  return root == nullptr;
}


void BSTree::insert(const string &value){
  Node *currNode = root;

  //Search if the desired node is in tree, if it is increase count by 1
  if (search(value)){
      currNode = HelperSearch(root, value);
      currNode->count++;
  }
  else{
      Node *newNode = new Node(value);

      // If empty, insert new node as the root of the tree
      if (empty()){
          root = newNode;
      }
      else{
          //traverse the tree until the given value is found
          int temp = 0;
          while (temp != 1){
              //if the value is less than the current Node's value, traverse tree left
              if (value < currNode->value){
                  //if the current node is the last, set its left to be the new node
                  if (currNode->left == nullptr){
                      currNode->left = newNode;
                      newNode->parent = currNode;
                      return;
                  }

                  //if current node is not last, keep traversing tree
                  else{
                      currNode = currNode->left;
                  }
              }

              //if the value is greater than the current node's value, traverse tree right
              else{
                  //if the current node is the last, set its right to be the new node
                  if (currNode->right == nullptr){
                      currNode->right = newNode;
                      newNode->parent = currNode;
                      return;
                  }

                  //if current node is not last, keep traversing tree
                  else{
                      currNode = currNode->right;
                  }
              }
          }
      }
  }
  }

//search function that returns true or false if node with given value exists in tree
bool BSTree::search(const string &key) const{
  return HelperSearch(root, key);
}

//Helper function for search 
Node* BSTree::HelperSearch(Node* node, const string &key) const{
  //while the tree is not empty
  if(node != nullptr) {
    //if the key matches the given node, return node
    if(key == node->value){
      return node;
    }
    //otherwise, if the key is less than the node's value, traverse left until found
    else{
      if(key < node->value){
        return HelperSearch(node->left, key);
      }
      //otherwise, if key is greater than than the node's valuye, traverse right until found
      else{
        return HelperSearch(node->right, key);
      }
    }
  }
  //if not found, return null
  else{
    return nullptr;
  }
}


//Returns largest value in tree
string BSTree::largest( ) const{
  // If tree is empty, return empty string
  if (root == nullptr){
    return "";
  }
  else{
    //starts at root
    Node* currNode = root;
    //Traverse to find the rightmost node
    while(currNode->right != nullptr){
      currNode = currNode->right;
    }
    return currNode->value;
  }
}


//Returns smallest value in tree
string BSTree::smallest( ) const{
  // If tree is empty, return empty string
  if (root == nullptr){
        return "";
  }
  else{
    //starts at root
    Node* currNode = root;
    //Traverse to find leftmost node
    while(currNode->left != nullptr){
      currNode = currNode->left;
    }
    return currNode->value;
  }
}

//returns height of a particular string in the tree
int BSTree::height(const string &value) const{
  if(!search(value)){
    return -1;
  }

  Node* findNode = HelperSearch(root, value);
  Node* leftNode = findNode;
  Node* rightNode = findNode;

  int leftHeight = 0;
  int rightHeight = 0;

  //finds height of left subtree
  if(findNode->left != nullptr){
    leftNode = leftNode->left;
    leftHeight++;
    leftHeight = leftHeight + height(leftNode->value);
  }

  //finds height of right subtree
  if(findNode->right != nullptr){
    rightNode = rightNode->right;
    rightHeight++;
    rightHeight = rightHeight + height(rightNode->value);
  }
  //returns the greater height value
  return max(leftHeight, rightHeight);
}


void BSTree::HelperRemove(Node* removeNode){
    Node *currNode = removeNode;
    Node *succNode = nullptr;

    //if the current node is the root, then delete
    if (currNode->left == nullptr && currNode->right == nullptr){
        //as long as the current node's parent is not null
        if (currNode->parent != nullptr){
            //if the current node is the left child, set the left child to null
            if (currNode->parent->left == currNode){
                currNode->parent->left = nullptr;
            }

            //if the current node is the right child, set the right child to null
            else{
                currNode->parent->right = nullptr;
            }
        }

        //if the current node is the root, then set root to null
        else{
            root = nullptr;
        }
        delete currNode;
    }

    //Case 2: If the current node has one child, replace the node with the child
    else if (currNode->left != nullptr){
        succNode = currNode->left;
        while (succNode->right != nullptr){
            succNode = succNode->right;
        }
        *currNode = *succNode;
        HelperRemove(succNode);
    }

    //Case 3: If the current node has two children, replace the node with the successor
    else{
        succNode = currNode->right;
        while (succNode->left != nullptr){
            succNode = succNode->left;
        }
        *currNode = *succNode;
        HelperRemove(succNode);
    }
}


void BSTree::remove(const string &key){
  //if the desired node is in the tree, make a new node with the given value
  if(search(key)){
    Node *removeNode = HelperSearch(root, key);
    // if the node has a count > 1 then decrement
    if(removeNode->count > 1){
      removeNode->count--;
    }
    //otherwise just delete the node
    else{
      HelperRemove(removeNode);
    }
  }
}

//preOrder helper function
void BSTree::preOrder(Node* currNode) const{
  //if node is not null
  if(currNode != nullptr){
    //Print Node
    cout << currNode->value << "(" << currNode->count << "), ";
    //Traverse left subtree
    preOrder(currNode->left);
    //Traverse right subtree
    preOrder(currNode->right);
  }
}

// inorder helper function
void BSTree::inOrder(Node* currNode) const{
  //if node is not null
  if(currNode != nullptr){
    //Traverse left subtree
    inOrder(currNode->left);
    //Print Node
    cout << currNode->value << "(" << currNode->count << "), ";
    //Traverse right subtree
    inOrder(currNode->right);
  }
}

//PostOrder helper function
void BSTree::postOrder(Node* currNode)const{
  //if node is not null
  if(currNode != nullptr){
    //Traverse left subtree
    postOrder(currNode->left);
    //Traverse right subtree
    postOrder(currNode->right);
    //Print Node
    cout << currNode->value << "(" << currNode->count << "), ";
  }
}

// PreOrder Function for BSTree
void BSTree::preOrder() const
{
    preOrder(root);
    cout << endl;
}

// InOrder Function for BSTree
void BSTree::inOrder() const
{
    inOrder(root);
    cout << endl;
}

// PostOrder Function for BSTree
void BSTree::postOrder() const
{
    postOrder(root);
    cout << endl;
}