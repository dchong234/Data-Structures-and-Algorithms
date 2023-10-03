#include "AVLTree.h"
#include <fstream>
using namespace std;

AVLTree::AVLTree(){
  root = nullptr;
}

//Returns the Height of a Node
int AVLTree::height(Node *node) const{
  //if node is null
  if (node == nullptr){
      return -1;
  }
  //if the node is a leaf
  else if (node->left == nullptr && node->right == nullptr){
      return 0;
  }

  int leftHeight = height(node->left);
  int rightHeight = height(node->right);

  // returns the height of the node
  if (leftHeight > rightHeight){
      return leftHeight + 1;
  }
  else{
      return rightHeight + 1;
  }
  return 0;
}

//returns the balance factor of a node
int AVLTree::balanceFactor(Node* currNode){

  int leftHeight = 0;
  int rightHeight = 0;

  //if currentNode is null
  if(currNode == nullptr){
    return -1;
  }

  //if the currentNode's left child exists
  if(currNode->left){
    leftHeight = height(currNode->left);
  }
  //if it doesn't exist, then height = -1
  else{
    leftHeight = -1;
  }

  //if the currentNode's right child exists
  if(currNode->right){
    rightHeight = height(currNode->right);
  }
  //if it doesn't exist, then height = -1
  else{
    rightHeight = -1;
  }

  return leftHeight - rightHeight;
}

void AVLTree::insert(const string &value){
  //creates a new node
  Node *newNode = new Node(value);

  //if the tree is empty then sets root to new node
  if (!root){
    root = newNode;
    root->parent = nullptr;
    return;
  }

  //node that will traverse the tree
  Node *currNode = root;

  //while the node is travesing the tree
  while (currNode){
    //if node already exists then increments count
    if (value == currNode->value){
        currNode->count++;
        currNode = nullptr;
    }

    //if value is less than current node's value
    else if (value < currNode->value){
      //if currNode's left node is empty then insert
      if (currNode->left == nullptr){
          currNode->left = newNode;
          newNode->parent = currNode;
          currNode = nullptr;
      }
      // otherwise move pointer to left
      else{
          currNode = currNode->left;
      }
    }

    //if value is greater than current node's value
    else{
        //if the current node's right node is empty then insert
        if (currNode->right == nullptr){
            currNode->right = newNode;
            newNode->parent = currNode;
            currNode = nullptr;
        }

        // otherwise move pointer to right
        else{
            currNode = currNode->right;
        }
    }
  }

    //rebalances the tree
  newNode = newNode->parent;
  while (newNode){
    rotate(newNode);
    newNode = newNode->parent;
  }
}

//rotate function
void AVLTree::rotate(Node *currNode){
  if(balanceFactor(currNode) == 2){
    if(balanceFactor(currNode->left) == -1){
      rotateLeft(currNode->left);
    }
    rotateRight(currNode);
  }
  else if(balanceFactor(currNode) == -2){
    if(balanceFactor(currNode->right) == 1){
      rotateRight(currNode->right);
    } 
    rotateLeft(currNode);
  }
}

//rotate left
void AVLTree::rotateLeft(Node *currNode){
  Node* rotateNode = currNode->right->left;
  //if currNode is not the root
  if(currNode->parent){
    replaceChild(currNode->parent, currNode, currNode->right);
  }
  //if currNode is root
  else{
    root = currNode->right;
    root->parent = 0;
  }

  setChild(currNode->right, "left", currNode);
  setChild(currNode, "right", rotateNode);
}


//rotate right
void AVLTree::rotateRight(Node *currNode){
  Node *rotateNode = currNode->left->right;
  //if currNode is not root
  if(currNode->parent){
    replaceChild(currNode->parent, currNode, currNode->left);
  }

  //if currNode is root, set root to currNode's left
  else{
    root = currNode->left;
    root->parent = 0;
  }
  setChild(currNode->left, "right", currNode);
  setChild(currNode, "left", rotateNode);
}

//sets node's child
void AVLTree::setChild(Node *parent, string location, Node *child){
  if(location == "left"){
    parent->left = child;
  }
  else{
    parent->right = child;
  }
  if(child){
    child->parent = parent;
  }
}

//replaces node's child
void AVLTree::replaceChild(Node *parent, Node *currNode, Node *newChild){
  //if parent's right child is the desired node
  if(parent->right == currNode){
    setChild(parent, "right", newChild);
  }
  //if parent's left child is the desired node
  else if(parent->left == currNode){
    setChild(parent, "left", newChild);
  }
}


//Prints tree in GraphViz 
void AVLTree::visualizeTree(ofstream & outFS, Node *n){
  if(n){
    if(n->left){
      visualizeTree(outFS,n->left);
      outFS<<n->value <<" -> " <<n->left->value<<";"<<endl;    
    }

    if(n->right){
      visualizeTree(outFS,n->right);
      outFS<<n->value <<" -> " <<n->right->value<<";"<<endl;    
    }
  }
}

//prints out all of the balance factors
void AVLTree::printBalanceFactors(){
  printBalanceFactors(root);
  cout << endl;
}

//prints out the balance factor of a ndoe
void AVLTree::printBalanceFactors(Node *currNode){
  //if node exists
  if(currNode != nullptr){
    printBalanceFactors(currNode->left);
    cout << currNode->value << "(" << balanceFactor(currNode) << "), ";
    printBalanceFactors(currNode->right);
  }
}

//creates a dot file for GraphViz
void AVLTree::visualizeTree(const string &outputFilename){
  ofstream outFS(outputFilename.c_str());
  if(!outFS.is_open()){
    cout<<"Error"<<endl;
    return;
  }
  outFS<<"digraph G {"<<endl;
  visualizeTree(outFS,root);
  outFS<<"}";
  outFS.close();
  string jpgFilename = outputFilename.substr(0,outputFilename.size()-4)+".jpg";
  string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
  system(command.c_str());
}