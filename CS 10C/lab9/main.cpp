#include <iostream>
using namespace std;

const int NUMBERS_SIZE = 50000;
const int CLOCKS_PER_MS = CLOCKS_PER_SEC/1000; //clock per milliseconds

int genRandInt(int low, int high) {
   return low + rand() % (high - low + 1);
}

void fillArrays(int arr1[], int arr2[],int arr3[]){
    for(int i = 0; i < NUMBERS_SIZE; ++i){
        arr1[i] = genRandInt(0,NUMBERS_SIZE);
        arr2[i] = arr1[i];
        arr3[i] = arr1[i];
    }
}

//divides an array into two partitions based on a pivot element
int partition(int numbers[], int lowIndex, int highIndex){
  int midpoint = lowIndex + (highIndex-lowIndex)/2;
  int pivot = numbers[midpoint];

  bool done = false;

  while(!done){

    while (numbers[lowIndex] < pivot) {
      lowIndex += 1;
    }
    // Decrement highIndex while pivot < numbers[highIndex]
    while (pivot < numbers[highIndex]) {
      highIndex -= 1;
    }
    // If zero or one elements remain, then all numbers are partitioned. Return highIndex.
    if (lowIndex >= highIndex) {
      done = true;
    }
      
    else{
      // Swap numbers[lowIndex] and numbers[highIndex]
      int tempValue = numbers[lowIndex];
      numbers[lowIndex] = numbers[highIndex];
      numbers[highIndex] = tempValue;
      
      // Update lowIndex and highIndex
      lowIndex += 1;
      highIndex -= 1;
    }
  }
    return highIndex;
}

//finds the median given 3 numbers
int median(int num1, int num2, int num3) {
  if (num1 > num2) {
    if (num2 > num3) {
        return num2; //if num2 is less than num1, but greater than num3, num2 is median
    } else if (num1 > num3) {
        return num3; //if num3 is less than num1, num3 is median
    } else {
        return num1; //otherwise, num1 is median
    }
  } else { //if num1 is not greater than num2
    if (num1 > num3) { //if num1 is greater than num3, then then num1 is median
        return num1;
    } else if (num2 > num3) { //If num1 is not greater than num3 and num2 is greater than num3, num2 is median
        return num3;
    } else {
        return num2; //otherwise, num2 is median
    }
  }
}

//partitions an array of integers using the median-of-three pivot selection technique
int partition_medianOfThree(int numbers[], int lowIndex, int highIndex){
  int midpoint = (highIndex+lowIndex)/2;
  int pivot = median(numbers[lowIndex], numbers[midpoint], numbers[highIndex]);

  bool done = false;

  while(!done){

    while (numbers[lowIndex] < pivot) {
      lowIndex += 1;
    }
    // Decrement highIndex while pivot < numbers[highIndex]
    while (pivot < numbers[highIndex]) {
      highIndex -= 1;
    }
    // If zero or one elements remain, then all numbers are partitioned. Return highIndex.
    if (lowIndex >= highIndex) {
      done = true;
    }
      
    else{
      // Swap numbers[lowIndex] and numbers[highIndex]
      int tempValue = numbers[lowIndex];
      numbers[lowIndex] = numbers[highIndex];
      numbers[highIndex] = tempValue;
      
      // Update lowIndex and highIndex
      lowIndex += 1;
      highIndex -= 1;
    }
  }
    return highIndex;
}

//sorts an array of integers in ascending order
void Quicksort_midpoint(int numbers[], int i, int k){
  int j = 0;
  //checks if array is already sorted
  if(i>=k){
    return;
  }
  //splits array into partitions and returns the pivot element
  j = partition(numbers, i, k);
  //recursively sorts the left partition
  Quicksort_midpoint(numbers, i, j);
  //recursively sorts the right partition
  Quicksort_midpoint(numbers, j+1, k);
}

//sorts an array of integers in ascending order using median-of-three pivot selection method
void Quicksort_medianOfThree(int numbers[], int i, int k){
  int j = 0;
  //checks if array is already sorted
  if(i>=k){
    return;
  }
  //splits array into partitions and returns the pivot element
  j = partition_medianOfThree(numbers, i, k);
  //recursively sorts the left partition
  Quicksort_medianOfThree(numbers, i, j);
  //recursively sorts the right partition
  Quicksort_medianOfThree(numbers, j+1, k);
}

//sorts an array of integers in ascending order
void InsertionSort(int numbers[], int numbersSize){
  int i = 0;
  int j = 0;
  int tempValue = 0;

  for (i = 1; i < numbersSize; i++) {
    j = i;
    //loop backwards while the element is smaller than the previous element
    while (j > 0 && numbers[j] < numbers[j - 1]) {
      tempValue = numbers[j];
      //move the previous element forward
      numbers[j] = numbers[j - 1];
      //insert the current element into the correct position
      numbers[j - 1] = tempValue;
      j--;
    }
  }
}


int main(){
  int arr1[NUMBERS_SIZE];
  int arr2[NUMBERS_SIZE];
  int arr3[NUMBERS_SIZE];
  int i = 0;

  int numbersSize = 0;
  int numbers[NUMBERS_SIZE];
  int start = 0;
  int end = 0;
  int elapsed = 0;
  srand(time(0));
  fillArrays(arr1,arr2,arr3);
  numbersSize = NUMBERS_SIZE;
  for (i = 0; i < numbersSize; ++i){
      numbers[i] = arr1[i];
  }
  start = clock();
  Quicksort_midpoint(numbers, 0, numbersSize-1);
  end = clock();
  elapsed = end - start;
  cout << "Quicksort_midpoint elapsed time: " << elapsed/CLOCKS_PER_MS << " ms" << endl;
  for (i = 0; i < numbersSize; ++i){
      numbers[i] = arr2[i];
  }
  start = clock();
  Quicksort_medianOfThree(numbers, 0, numbersSize-1);
  end = clock();
  elapsed = end - start;
  cout << "Quicksort_medianOfThree elapsed time: " << elapsed/CLOCKS_PER_MS << " ms" << endl;
  for (i = 0; i < numbersSize; ++i){
      numbers[i] = arr3[i];
  }
  start = clock();
  InsertionSort(numbers, numbersSize);
  end = clock();
  elapsed = end - start;
  cout << "InsertionSort elapsed time: " << elapsed/CLOCKS_PER_MS << " ms" << endl;
  return 0;
}
