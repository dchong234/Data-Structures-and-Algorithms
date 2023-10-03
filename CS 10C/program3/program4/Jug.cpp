#include "Jug.h"
#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <string>
using namespace std;

//Constructor for the Jug class, initializes the capacities, the final amount, and current amount of the jugs
Jug::Jug(int a, int b, int c, int d, int e, int f, int g, int h, int i){
  capacityA = a;
  capacityB = b;
  finalAmount = c;
  currFillA = d;
  currFillB = e;
  currEmptyA = f;
  currEmptyB = g;
  currPourAB = h;
  currPourBA = i;
  //Create nodes for each action and add them to the action vector
  Node* fillA = new Node("fill A");
  Node* fillB = new Node("fill B");
  Node* emptyA = new Node("empty A");
  Node* emptyB = new Node("empty B");
  Node* pourAB = new Node("pour A B");
  Node* pourBA = new Node("pour B A");
  action.push_back(fillA);
  action.push_back(fillB);
  action.push_back(emptyA);
  action.push_back(emptyB);
  action.push_back(pourAB);
  action.push_back(pourBA);
  //For each action node, create edges to connect it to all the other actions
  for (unsigned i = 0; i < action.size(); ++ i){
    for (unsigned j = 0; j < action.size(); ++j) {
      if (!(i == j)){
        action.at(i)->neighbors.push_back(action.at(j));
      }
    }
  }
  // Create a pair to represent the initial state of the jugs, where both jugs are empty
  pair<int,int> t;
  t.first = 0;
  t.second = 0;
  visitedPairs.push_back(t);
}

//Destructor
Jug::~Jug() {
	for (unsigned i = 0; i < action.size(); ++i){
		delete action.at(i);
	}
}

//returns an integer indicating the success of the function
int Jug::solve(string &solution){
	solution = ""; 
  //Check for invalid input: negative values
	if (currFillA < 0 || currFillB < 0 || currEmptyA < 0 || currEmptyB < 0 || currPourAB < 0 || currPourBA < 0){
		return -1;
	}
  //Check for invalid input: capacityA is not positive or is greater than capacityB
	if (!(0 < capacityA && capacityA <= capacityB)){
		return -1;
	}
  //Check for invalid input: finalAmount is greater than capacityB or capacityB is greater than 1000
	if (!(finalAmount <= capacityB && capacityB <= 1000)){
		return -1;
	}
  //Create a const reference to the solution string and use it to call the solve function recursively
	const string& tempSolution = solution;
	solution = solve(tempSolution);
  //If the recursive call returns an empty string, the function has failed
	if (solution == ""){
		return 0;
	}
	return 1;
}

//returns a string representing the solution to the problem
string Jug::solve(const string &solution){
	queue<Paths> q;
  //Create two Paths representing the starting states of the two jugs, and push them onto the queue
	Paths path1;
	Paths path2;
	pair<int,int> emptyPair;
	emptyPair.first = 0;
  emptyPair.second = 0;
	path1 = takeAction(emptyPair, action.at(0));
	path2 = takeAction(emptyPair, action.at(1));
	visitedPairs.push_back(path1.currPair);
	visitedPairs.push_back(path2.currPair);
	q.push(path1);
	q.push(path2);
	Paths currNode;
	Paths tempPath;
  //continue searching for a solution until the queue is empty
	while (!q.empty()){
		currNode = q.front();
    //Iterate through the neighbors of the current node
		for(unsigned i = 0; i < currNode.node->neighbors.size(); ++i){
      //Take an action on the current node to get a new node
			tempPath = takeAction(currNode.currPair, currNode.node->neighbors.at(i));
      //If the new node is the solution, add it to the list of solutions
			if (tempPath.currPair.second == finalAmount){
				tempPath.cost += currNode.cost;
				tempPath.str = currNode.str + "\n" + tempPath.str;
				if (tempPath.currPair.first != 0){
					tempPath.cost += currEmptyA;
					tempPath.str += "\nempty A";
				}
				tempPath.str = tempPath.str + "\nsuccess " + to_string(tempPath.cost);
				v.push_back(tempPath);
			}
      //If the new node has not been visited, add it to the queue
      else if (!visited(tempPath.currPair)){
				visitedPairs.push_back(tempPath.currPair);
				tempPath.str = currNode.str + "\n" + tempPath.str;
				tempPath.cost += currNode.cost;
				q.push(tempPath);
			}
		}
		q.pop();
	}
  //If there are solutions, find the one with the smallest cost and return it
	if (v.size() != 0){
		int small = 100000;
		int smallIndex = 0;
		for (unsigned i = 0; i < v.size(); ++i){
			if (v.at(i).cost < small){
				small = v.at(i).cost;
				smallIndex = i;
			}
		}
		return v.at(smallIndex).str;
	}
	return "";
}

//checks if pair has been visited before
bool Jug::visited(const pair<int,int> &currPair){
	for (unsigned i = 0; i < visitedPairs.size(); ++i){
    //If currPair is found in the visitedPairs vector, return true
		if (currPair == visitedPairs.at(i)){
			return true;
		}
	}
  //If currPair is not found in the visitedPairs vector, return false
	return false;
}

//returns a Paths object that contains the updated pair of integers, the cost of the action, and a string describing the action taken
Paths Jug::takeAction(const pair<int,int> &Pair, Node* n1){
	Paths tempPair;

	//Set the node in tempPair to n1
  tempPair.node = n1;
    
  //Check what action the node in n1 represents and update tempPair accordingly
	if (n1->action == "fill A"){
    tempPair.currPair = fillA(Pair);
    tempPair.cost = currFillA;
    tempPair.str = "fill A";
    return tempPair;
  } 
  
  if (n1->action == "fill B"){
    tempPair.currPair = fillB(Pair);
    tempPair.cost = currFillB;
    tempPair.str = "fill B";
    return tempPair;
  }
  
  if (n1->action == "empty A"){
    tempPair.currPair = emptyA(Pair);
    tempPair.cost = currEmptyA;
    tempPair.str = "empty A";
    return tempPair;
  }
  
  if (n1->action == "empty B"){
    tempPair.currPair = emptyB(Pair);
    tempPair.cost = currEmptyB;
    tempPair.str = "empty B";
    return tempPair;
  } 
  
  if (n1->action == "pour A B"){
    tempPair.currPair = pourAB(Pair);
    tempPair.cost = currPourAB;
    tempPair.str = "pour A B";
    return tempPair;
  }
  
  //If none of the above actions apply, the node must represent pouring from jug B to jug A, so update tempPair accordingly
  tempPair.currPair = pourBA(Pair);
  tempPair.cost = currPourBA;
  tempPair.str = "pour B A";
  
  return tempPair;
}

//akes two integers as input and returns a pair of integers
pair<int,int> Jug::makePair(int first, int second){
	pair<int,int> tempPair;

	tempPair.first = first;
	tempPair.second = second;
	
	return tempPair;
}

//returns a new pair of integers representing the state after filling jug A to capacity
pair<int,int> Jug::fillA(const pair<int,int> &p){
	pair<int,int> tempPair = p;
	
	tempPair.first = capacityA;
	
	return tempPair;
}

//returns a new pair of integers representing the state after filling jug B to capacity
pair<int,int> Jug::fillB(const pair<int,int> &p){
	pair<int,int> tempPair = p;
	
	tempPair.second = capacityB;
	
	return tempPair;
}

//returns a new pair of integers representing the state after emptying jug A
pair<int,int> Jug::emptyA(const pair<int,int> &p){
	pair<int,int> tempPair = p;
	
	tempPair.first = 0;
	
	return tempPair;
}

//returns a new pair of integers representing the state after emptying jug B
pair<int,int> Jug::emptyB(const pair<int,int> &p){
	pair<int,int> tempPair = p;
	
	tempPair.second = 0;
	
	return tempPair;
}

//returns a new pair of integers representing the state after pouring the contents of jug A into jug B
pair<int,int> Jug::pourAB(const pair<int,int> &p){
	pair<int,int> tempPair;
  //Check if the sum of the current contents of jugs A and B is less than the capacity of B
	if(p.second + p.first < capacityB){
    //empty jug A and pour its contents into jug B
		tempPair.first = 0;
		tempPair.second = p.first + p.second;
	} 
	//If the sum of the contents of jugs A and B is greater than or equal to the capacity of B
	else{
		tempPair.first = (p.first + p.second) - capacityB;
		tempPair.second = capacityB;
	}
	return tempPair;
}

//returns a new pair of integers representing the state after pouring the contents of jug B into jug A
pair<int,int> Jug::pourBA(const pair<int,int> &p){
	pair<int,int> tempPair;
  //check if the sum of the two jugs' volumes is less than the capacity of A
	if(p.second + p.first < capacityA){
		tempPair.first = p.first + p.second;
		tempPair.second = 0;
	}
  //if the sum is greater than or equal to capacityA
	else{
		tempPair.first = capacityA;
		tempPair.second = (p.first + p.second) - capacityA;
	}
	
	return tempPair;
}