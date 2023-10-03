#include "IntList.h"
int main(){
  cout << "New IntList" << endl;
  IntList *test = new IntList();

  cout << "Testing empty output" << endl;
  cout << *test << endl;

  cout << "Testing empty()" << endl;
  if (test->empty())
  {
      cout << "IntList is empty" << endl;
  }

  else
  {
      cout << "IntList is not empty" << endl;
  }
  cout << endl;


  cout << "Testing pop_back() when empty" << endl;
  test->pop_back();
  cout << *test << endl << endl;

  cout << "Testing pop_front() when empty" << endl;
  test->pop_front();
  cout << *test << endl << endl;

  cout << "Testing printReverse() when empty" << endl;
  test->printReverse();
  cout << endl;

  cout << "Testing push_front()" << endl;
  test->push_front(1);
  test->push_front(2);
  cout << endl;

  cout << "Testing push_back()" << endl;
  test->push_back(3);
  test->push_back(4);
  cout << endl;

  cout << "Testing output operator" << endl;
  cout << *test << endl << endl;

  cout << "Testing printReverse()" << endl;
  test->printReverse();
  cout << endl << endl;

  cout << "Testing pop_back()" << endl;
  test->pop_back();
  cout << *test << endl<< endl;

  cout << "Testing pop_back()" << endl;
  test->pop_back();
  cout << *test << endl<< endl;

  cout << "Testing pop_front()" << endl;
  test->pop_front();
  cout << *test << endl<< endl;

  cout << "Testing pop_front()" << endl;
  test->pop_front();
  cout << *test << endl<< endl;

  cout << "Testing destructor" << endl;
  delete test;


  return 0;
}