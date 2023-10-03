#include <iostream>
#include <stdexcept>
#include <vector>
using namespace std;

//Declarations
template<typename T>
unsigned min_index(const vector<T> &vals, unsigned index);
template<typename T>
void selection_sort(vector<T> &vals);
template<typename T>
T getElement(vector<T> vals, int index);

//createVector() function
vector<char> createVector(){
    int vecSize = rand() % 26;
    char c = 'a';
    vector<char> vals;
    for(int i = 0; i < vecSize; i++)
    {
        vals.push_back(c);
        c++;
    }
    return vals;
}

//finds the min value index starting at the given index
template<typename T>
unsigned min_index(const vector<T> &vals, unsigned index){
  unsigned min = index;
  for(unsigned i = index+1; i<vals.size(); i++){
    if(vals.at(i) < vals.at(min)){
      min = i;
    }
  }
  return min;
}

//sorts vector
template<typename T>
void selection_sort(vector<T> &vals){
  for(unsigned i = 0; i<vals.size(); i++){
      unsigned min = min_index(vals, i);
        swap(vals.at(i),vals.at(min));
      }
}

//gets eleent at given index
template<typename T>
T getElement(vector<T> vals, int index){
  unsigned invalid = index;
  if(invalid < 0 || invalid > vals.size()){
    throw out_of_range("out of range exception occured");
  }
  return vals.at(index);
}

int main(){

    //Part A test
    //testing ints
    cout << "Testing selection_sort with type int" << endl;
    vector<int> intVect;
    intVect.push_back(1);
    intVect.push_back(4);
    intVect.push_back(3);
    intVect.push_back(5);
    intVect.push_back(2);
    selection_sort(intVect);

    for(unsigned i = 0; i<intVect.size(); i++){
      cout << intVect.at(i) << endl;
    }
    cout << endl;

    //testing strings
    cout << "Testing selection_sort with type string" << endl;
    vector<string> stringVect;
    stringVect.push_back("mom");
    stringVect.push_back("water");
    stringVect.push_back("coffee");
    stringVect.push_back("television");
    stringVect.push_back("couch");
    selection_sort(stringVect);

    for(unsigned i = 0; i<stringVect.size(); i++){
      cout << stringVect.at(i) << endl;
    }
    cout << endl;

    //testing doubles
    cout << "Testing selection_sort with type double" << endl;
    vector<double> doubleVect;
    doubleVect.push_back(10);
    doubleVect.push_back(4.4);
    doubleVect.push_back(3.3);
    doubleVect.push_back(5.5);
    doubleVect.push_back(2.2);
    selection_sort(doubleVect);

    for(unsigned i = 0; i<doubleVect.size(); i++){
      cout << doubleVect.at(i) << endl;
    }
    cout << endl;


    //Part B
    try{
     srand(time(0));
     vector<char> vals = createVector();
     char curChar;
     int index;
     int numOfRuns = 10;
     while(--numOfRuns >= 0){
         cout << "Enter a number: " << endl;
         cin >> index;
         curChar = getElement(vals,index);
         cout << "Eleent located at " << index << ": is " << curChar << endl;
     }
    }
    catch (runtime_error& excpt){
      cout << excpt.what() << endl;
    }

    return 0;
}