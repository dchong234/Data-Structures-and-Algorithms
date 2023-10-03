  #include <iostream>
  #include "Heap.h"
  using namespace std;
  
  /*Initializes an empty heap.*/
  Heap::Heap(){
    numItems = 0;
  }

  //checks if array is empty
  bool Heap::empty(){
    if(numItems == 0){
      return true;
    }
    else{
      return false;
    }
  }

  /*Inserts a PrintJob to the heap without
  violating max-heap properties.*/
  void Heap::enqueue ( PrintJob* newPrintJob){
    //If the heap is not full, the function proceeds to add to heap.
    if(numItems != MAX_HEAP_SIZE){
      //if empty, object is added as the root 
      if(empty()){
        arr[0] = newPrintJob;
        numItems++;
      }

      else{
        int index = numItems;
        //compares priority of object with parent
        while(index > 0 && arr[(index-1)/2]->getPriority() < newPrintJob->getPriority()){
          arr[index] = arr[(index-1)/2];
          index = (index-1)/2;
        }
          // inserts into the heap at the correct position
          arr[index] = newPrintJob;
          numItems++;

    }

  }
  }

  /*Removes the node with highest priority from the heap. 
  Follow the algorithm on priority-queue slides. */
  void Heap::dequeue(){
    //as long as the array is not empty
    if(!empty()){
      //if it the array has more than value, swap with the last element
      if(numItems != 1){
        arr[0] = arr[numItems-1];
      }
      //delete the last element by decreasing size
      numItems--;
      //trickles the first index to its spot
      trickleDown(0);
    }
  }

  /*Returns the node with highest priority.*/
  PrintJob* Heap::highest( ){
    //if empty return null 
    if(empty()){
      return nullptr;
    }
    // else return the first value of the array
    else{
      return arr[0];
    }
  }

  /*Prints the PrintJob with highest priority in the following format:
  Priority: priority, Job Number: jobNum, Number of Pages: numPages
  (Add a new line at the end.)*/
  void Heap::print(){
    if(empty()){
      cout << "The Heap is empty" << endl;
    }
    else{
      cout << "Priority: " << highest()->getPriority() << ", ";
      cout << "Job Number: " << highest()->getJobNumber() << ", ";
      cout << "Number of Pages: " << highest()->getPages() << endl;
    }
  }

  //This function is used by trickleDown function to swap the current item and the desired position 
  void Heap::swap(int currIndex, int newIndex){
    PrintJob *tempIndex = arr[currIndex];
    arr[currIndex] = arr[newIndex];
    arr[newIndex] = tempIndex;
  }

  /*This function is called by dequeue function
  to move the new root down the heap to the 
  appropriare location.*/
  void Heap::trickleDown(int index){
    //if there are no children in the array
    if(numItems < index*2+2){
      return;
    }
    //if there is only one child in the array
    else if(numItems == index*2+2){
      //swap if the current index's priority is less than the child's 
      if(arr[index]->getPriority() < arr[numItems-1]->getPriority()){
        swap(index, numItems-1);
      }
    }
    
    else{
      //if the left child in array is > than right child
      if(arr[index*2+1]->getPriority() > arr[index*2+2]->getPriority()){
        //if the current index is < than the left child
        if(arr[index]->getPriority() < arr[index*2+1]->getPriority()){
          swap(index, index*2+1);
        }
        trickleDown(index*2+1);
      }
      //if the right child in array is > than left child
      else{
        //if the current index is < than the right child then swap
        if(arr[index]->getPriority() < arr[index*2+2]->getPriority()){
          swap(index, index*2+2);
        }
        trickleDown(index*2+2);
      }
    }
  }
  
  