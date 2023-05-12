#include <iostream>
#include <algorithm>
#include "Heap.h"

using namespace std;

//constructor: initialize numItems to 0
Heap::Heap() : numItems(0) {}

//destructor: keep dequeueing until empty
Heap::~Heap() {
    while (!empty()) {
        dequeue();
    }
}

//empty: returns true if heap is empty
bool Heap::empty() const {
    return (numItems == 0);
}

//enqueue: inserts a PrintJob into heap
void Heap::enqueue (PrintJob* curr) {
    //only add to array if it's less than max heap size
    if (numItems < MAX_HEAP_SIZE) {
        //if array is empty, no need to percolate up
        if (empty()) {
            arr[numItems] = curr;
            ++numItems;
        }
        //if array isn't empty, must swap nodes to adhere to max heap properties
        else {
            int nodeIndex = numItems; //keep track of node index that needs to be swapped up
            int parentIndex; //keep track of index of node's parent to swap with nodeIndex
            arr[numItems] = curr; //add curr to end of array
            ++numItems;
            //keep swapping up until nodeIndex reaches 0
            while (nodeIndex > 0) {
                parentIndex = (nodeIndex - 1) / 2; //in the array, curr's parent will be (index - 1) / 2
                //if curr is smaller than its parent, don't swap and terminate loop
                if (curr->getPriority() <= arr[parentIndex]->getPriority()) {
                    return;
                }
                //if curr is larger than its parent, swap
                else {
                    swap(arr[nodeIndex], arr[parentIndex]);
                    nodeIndex = parentIndex;
                }
            }
        }
    }
}

//highest: returns node with highest priority
PrintJob* Heap::highest() {
    //if heap is empty, just return nullptr
    if (empty()) {
        return nullptr;
    }
    //otherwise return first element of array
    else {
        return arr[0];
    }
}

//print: prints node with highest priority
void Heap::print() {
    PrintJob* highestJob = highest(); //get highest priority node
    cout << "Priority: " << highestJob->getPriority();
    cout << ", Job Number: " << highestJob->getJobNumber();
    cout << ", Number of Pages: " << highestJob->getPages() << endl;
}

//dequeue helper function: recursively trickles down node with its index passed in
void Heap::trickleDown(int nodeIndex) {
    //base case 1: node is a leaf; do nothing (already follows max heap properties)
    if (nodeIndex * 2 + 2 > numItems) {
        return;
    }

    //base case 2: node has 1 child; swap node with its child if it is smaller
    else if (nodeIndex * 2 + 2 == numItems) {
        if (arr[nodeIndex]->getPriority() < arr[numItems - 1]->getPriority()) {
            swap(arr[nodeIndex], arr[numItems - 1]);
        }
    }
    
    //recursive case: node has 2 children-- need to swap with larger child
    else {
        int leftChild = nodeIndex * 2 + 1; //left child's index in array
        int rightChild = nodeIndex * 2 + 2; //right child's index in aray

        //right child is greater than left child
        if (arr[rightChild]->getPriority() > arr[leftChild]->getPriority()) {
            //if right child is greater than nodeIndex, swap them (want to bring down lower value)
            if (arr[rightChild]->getPriority() > arr[nodeIndex]->getPriority()) {
                swap(arr[nodeIndex], arr[rightChild]);
            }
            //call trickleDown again with rightChild (keep going until reaching one of the base cases)
            trickleDown(rightChild);
        }
        //left child is greater than right child-- same logic as right child^^
        else {
            if (arr[leftChild]->getPriority() > arr[nodeIndex]->getPriority()) {
                swap(arr[nodeIndex], arr[leftChild]);
            }
            trickleDown(leftChild);
        }
    }
}

//dequeue: removes highest priority node (root)
void Heap::dequeue() {
    //if heap is empty, do nothing
    if (empty()) {
        return;
    }
    //otherwise remove root
    else {
        //only need to swap root with last element if size > 1
        if (numItems > 1) {
            arr[0] = arr[numItems - 1]; //swap root w/ last element to remove
        }
        --numItems; //remove last element (root)
        trickleDown(0); //use trickleDown function to make heap adhere to max heap qualities again
    }
}
