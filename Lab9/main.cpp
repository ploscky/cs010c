#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

//declare const variables
const int NUMBERS_SIZE = 50000;
const int CLOCKS_PER_MS = CLOCKS_PER_SEC/1000; //clock per milliseconds

//given functions
int GenRandInt(int low, int high) {
   return low + rand() % (high - low + 1);
}
void FillArrays(int arr1[], int arr2[],int arr3[]){
    for(int i = 0; i < NUMBERS_SIZE; ++i){
        arr1[i] = GenRandInt(0,NUMBERS_SIZE);
        arr2[i] = arr1[i];
        arr3[i] = arr1[i];
    }
}

/*-------------------------------------------------------------------------------------*/

//helper partition function for Quicksort_midpoint
int MidpointPartition(int numbers[], int i, int k) {
    int pivot = numbers[i + (k - i) / 2]; //pivot is the midpoint of the array (from i to k)
    bool done = false; //keeps track of when to stop iterating low and high index

    //temp variables to not mess with i or k
    int low = i;
    int high = k;
    //keep either incrementing low or decrementing high until the indexes meet
    while (!done) {
        //increment low index while numbers[low] is less than pivot
        while (numbers[low] < pivot) {
            ++low;
        }
        //decrement high index while numbers[high] is more than pivot
        while (numbers[high] > pivot) {
            --high;
        }

        //if 0 or 1 elements remain, all numbers are already partitioned and loop is broken
        if (low >= high) {
            done = true;
        }
        //more than 1 element remains-- keep swapping the numbers at low and high index while updating them
        else {
            swap(numbers[low], numbers[high]);
            ++low;
            --high;
        }
    }
    return high;
}

//quicksort midpoint: quicksort with midpoint as pivot
void Quicksort_midpoint(int numbers[], int i, int k) {
    //base case: partition size is 0 or 1 (already sorted)
    if (i >= k) {
        return;
    }

    //lowIndex is index of lower partition's last element
    int lowIndex = MidpointPartition(numbers, i, k);
    Quicksort_midpoint(numbers, i, lowIndex); //sorting the lower partition
    Quicksort_midpoint(numbers, lowIndex + 1, k); //sorting the higher partition
}

//helper partition function for Quicksort_medianOfThree
int MedianOfThreePartition(int numbers[], int i, int k) {
    int midpoint = i + (k - i) / 2; //find the midpoint of the array so you have 3 values-- i, k, midpoint
    int median; //declare median (to be set later)

    //find median of 3 values
    //if numbers[i] between numbers[midpoint] and numbers[k]
    if ((numbers[i] <= numbers[midpoint] && numbers[i] >= numbers[k]) || (numbers[i] <= numbers[k] && numbers[i] >= numbers[midpoint])) {
        median = i;
    }
    //if numbers[k] between numbers[midoint] and numbers[i]
    else if ((numbers[k] <= numbers[midpoint] && numbers[k] >= numbers[i]) || (numbers[k] <= numbers[i] && numbers[k] >= numbers[midpoint])) {
        median = k;
    }
    //if numbers[midpoint] between numbers[i] and numbers[k]
    else if ((numbers[midpoint] <= numbers[i] && numbers[midpoint] >= numbers[k]) || (numbers[midpoint] <= numbers[k] && numbers[midpoint] >= numbers[i])) {
        median = midpoint;
    }

    int pivot = numbers[median]; //set pivot as the median of the array

    //same process as the midpoint partition function, only that the pivot is the median
    int low = i;
    int high = k;
    bool done = false;

    while (!done) {
        while (numbers[low] < pivot) {
            ++low;
        }
        while (numbers[high] > pivot) {
            --high;
        }
        if (low >= high) {
            done = true;
        }
        else {
            swap (numbers[low], numbers[high]);
            ++low;
            --high;
        }
    }
    return high;
}

//quicksort median of three: quicksort with median as pivot
void Quicksort_medianOfThree(int numbers[], int i, int k) {
    //base case: partition size is 0 or 1 (already sorted)
    if (i >= k) {
        return;
    }

    //lowIndex is index of lower partition's last element
    int lowIndex = MedianOfThreePartition(numbers, i, k);
    Quicksort_medianOfThree(numbers, i, lowIndex); //sorting lower partition
    Quicksort_medianOfThree(numbers, lowIndex + 1, k); //sorting higher partition
}

//insertion sort
void InsertionSort(int numbers[], int numbersSize) {
    //outer and inner loop iterators
    int outer = 0;
    int inner = 0;

    //outer loop iterates until reaching end of array
    for (outer = 1; outer < numbersSize; ++outer) {
        inner = outer; //set inner loop iterator to outer loop iterator (basically traversing n^2^ times)
        //while value at index left of inner is greater than inner, swap the two values
        while (inner > 0 && numbers[inner] < numbers[inner - 1]) {
            swap (numbers[inner], numbers[inner - 1]);
            --inner; //decrement inner until it reaches 0
        }
    }
}

/*-------------------------------------------------------------------------------------*/

int main() {
    //filling arrays
    int midpointArray[NUMBERS_SIZE];
    int medianArray[NUMBERS_SIZE];
    int insertionArray[NUMBERS_SIZE];
    FillArrays(midpointArray, medianArray, insertionArray);

    //sorting midpointArray
    clock_t midpointStart = clock();
    Quicksort_midpoint(midpointArray, 0, NUMBERS_SIZE - 1);
    clock_t midpointEnd = clock();
    int midpointElapsedTime = (midpointEnd - midpointStart)/CLOCKS_PER_MS; // converts elapsed time from microseconds to milliseconds.
    cout << "Quicksort (midpoint): " << midpointElapsedTime << "ms" << endl;

    //sorting medianArray
    clock_t medianStart = clock();
    Quicksort_medianOfThree(medianArray, 0, NUMBERS_SIZE - 1);
    clock_t medianEnd = clock();
    int medianElapsedTime = (medianEnd - medianStart)/CLOCKS_PER_MS; // converts elapsed time from microseconds to milliseconds.
    cout << "Quicksort (median): " << medianElapsedTime << "ms" << endl;

    //sorting insertionArray
    clock_t insertionStart = clock();
    InsertionSort(insertionArray, NUMBERS_SIZE);
    clock_t insertionEnd = clock();
    int insertionElapsedTime = (insertionEnd - insertionStart)/CLOCKS_PER_MS; // converts elapsed time from microseconds to milliseconds.
    cout << "Insertion Sort: " << insertionElapsedTime << "ms" << endl;
    return 0;
}