#ifndef JUG_H
#define JUG_H

#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <string>
using namespace std;

struct Node{
	vector<Node*> neighbors;
	string action;
	Node(string s){
		action = s;
	}
};

struct Paths{
  pair<int,int> currPair;
	string str;
  int cost;
  Node* node;
	Paths(){
	  pair<int,int> temp;
    temp.first = 0;
    temp.second = 0;
    str = "";
    cost = 0;
    node = NULL;
	}
};

class Jug{
    public:
        Jug(int,int,int,int,int,int,int,int,int);
        ~Jug();

        //solve is used to check input and find the solution if one exists
        //returns -1 if invalid inputs. solution set to empty string.
        //returns 0 if inputs are valid but a solution does not exist. solution set to empty string.
        //returns 1 if solution is found and stores solution steps in solution string.
        int solve(string &solution);
    private:
        //anything else you need
        pair<int,int> fillA(const pair<int,int> &);
        pair<int,int> fillB(const pair<int,int> &);
        pair<int,int> emptyA(const pair<int,int> &);
        pair<int,int> emptyB(const pair<int,int> &);
        pair<int,int> pourAB(const pair<int,int> &);
        pair<int,int> pourBA(const pair<int,int> &);
        pair<int,int> makePair(int, int);
        Paths takeAction(const pair<int,int> &p, Node* n1);
        bool visited(const pair<int,int> &p);
        string solve(const string &solution);
        vector <Node*> action;
        vector<pair<int,int> > visitedPairs;
        vector<Paths> v;
        int capacityA;
        int capacityB;
        int finalAmount;
        int currFillA;
        int currFillB;
        int currEmptyA;
        int currEmptyB;
        int currPourAB;
        int currPourBA;
};
#endif