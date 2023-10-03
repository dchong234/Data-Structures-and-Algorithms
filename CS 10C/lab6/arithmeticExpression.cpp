#include <iostream>
#include <stack>
#include <fstream>
#include <sstream>
#include "arithmeticExpression.h"
using namespace std;

int arithmeticExpression::priority(char op){
    int priority = 0;
    if(op == '('){
        priority =  3;
    }
    else if(op == '*' || op == '/'){
        priority = 2;
    }
    else if(op == '+' || op == '-'){
        priority = 1;
    }
    return priority;
}

string arithmeticExpression::infix_to_postfix(){
    stack<char> s;
    ostringstream oss;
    char c;
    for(unsigned i = 0; i< infixExpression.size();++i){
        c = infixExpression.at(i);
        if(c == ' '){
            continue;
        }
        if(c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')'){ //c is an operator
            if( c == '('){
                s.push(c);
            }
            else if(c == ')'){
                while(s.top() != '('){
                    oss << s.top();
                    s.pop();
                }
                s.pop();
            }
            else{
                while(!s.empty() && priority(c) <= priority(s.top())){
                    if(s.top() == '('){
                        break;
                    }
                    oss << s.top();
                    s.pop();
                }
                s.push(c);
            }
        }
        else{ //c is an operand
            oss << c;
        }
    }
    while(!s.empty()){
        oss << s.top();
        s.pop();
    }
    return oss.str();
}

void arithmeticExpression::visualizeTree(const string &outputFilename){
    ofstream fout(outputFilename.c_str());
    if(!fout.is_open()){
        cout<<"Error opening "<< outputFilename<<endl;
        return;
    }
    fout<<"digraph G {"<<endl;
    visualizeTree(fout,root);
    fout<<"}";
    fout.close();
    string jpgFilename = outputFilename.substr(0,outputFilename.size()-4)+".jpg";
    string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
}

//Default constructor
arithmeticExpression::arithmeticExpression(const string &value){
    infixExpression = value;
    root = nullptr;
}

//buildTree function
void arithmeticExpression::buildTree(){
    infixExpression = infix_to_postfix();
    stack <TreeNode*> s;

    //traverse each character in the postfix expression
    for(unsigned i = 0; i < infixExpression.size(); ++i){
    TreeNode *newNode = new TreeNode(infixExpression.at(i), 'a' + i);
    //if the current character has priority 0, push the node onto the stack
    if (priority(infixExpression.at(i)) == 0) {
        s.push(newNode);
    }
    //if priority greater than 0, pop the two nodes from stack and make them left/right children
    else if (priority(infixExpression.at(i)) > 0) {
        newNode->right = s.top();
        s.pop();
        newNode->left = s.top();
        s.pop();
        //push operator node onto stack
        s.push(newNode);
        root = newNode;
    }
    }
}

//infix function
void arithmeticExpression::infix(){
   infix(root);
}
//prefix function
void arithmeticExpression::prefix(){
   prefix(root);
}
//postfix function
void arithmeticExpression::postfix(){
   postfix(root);
}

void arithmeticExpression::infix(TreeNode* currNode){
    //base case if node is null, return
    if(currNode == nullptr){
        return;
    }
    //if current node is operator, print '(' and traverse left subtree and print
    if(priority(currNode->data)){
        cout << "(";
        infix(currNode->left);
        cout << currNode->data;
        //traverse right subtree, print operator, end with ')'
        infix(currNode->right);
        cout << ")";      
    }
    //if current node is an operand, print value and traverse subtrees
    else{
        infix(currNode->left);
        cout << currNode->data;
        infix(currNode->right);
    }
}

void arithmeticExpression::prefix(TreeNode* currNode){
    //base case if null then return
    if(currNode == nullptr){
        return;
    }
    //print value of current node
    cout << currNode->data;
    //traverse left and right subtrees of node
    prefix(currNode->left);
    prefix(currNode->right);
}

void arithmeticExpression::postfix(TreeNode* currNode){
    //base case if null then return
    if(currNode == nullptr){
        return;
    }
    //traverse left and right subtrees of node
    postfix(currNode->left);
    postfix(currNode->right);
    //print value of left and right subtrees of node
    cout << currNode->data;
}

void arithmeticExpression::visualizeTree(ofstream& fout, TreeNode* currNode){
    //if currrent node is not null, write DOT language to label node
    if(currNode){
        fout << currNode->key << "[ label = " << "\"" << currNode->data << "\"" << " ]" << endl;
    }
    //if the node has a left child, write the DOT langauge to label left child
    if(currNode->left) {
    fout  << currNode->key <<  "->" << currNode->left->key << "[ label = " << "\"" << currNode->left->data << "\"" << " ]" << endl;
    visualizeTree(fout, currNode->left);
   }
    //if the node has a right child, write the DOT langauge to label right child
   if(currNode->right) {
      fout  << currNode->key << " -> " << currNode->right->key << "[ label =  " << "\"" << currNode->right->data << "\"" << " ]" << endl;
      visualizeTree(fout, currNode->right);
   }
    fout << endl;
}