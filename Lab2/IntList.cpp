#include "IntList.h"
#include <iostream>
using namespace std;

//constructor
IntList::IntList()
    //construct new nodes for dummyHead and dummyTail -- help with edge cases
    //value for the nodes are 0 as placeholder data
    : dummyHead(new IntNode(0)), //dummyHead->next points to first node in list
      dummyTail(new IntNode(0)) //dummyTail->prev points to last node in list
{
    //if list is empty, only nodes are dummyHead and dummyTail
    dummyHead->next = dummyTail;
    dummyTail->prev = dummyHead;
}

//destructor
IntList::~IntList() {
    //using pop_front function to remove first node until the list is empty
    while (!empty()) {
        pop_front();
    }
}

//push_front    
void IntList::push_front(int value) {
     //create new node to push front
    IntNode* newNode = new IntNode(value);

    //declare a pointer that points to the first node of linked list (after dummyHead)
    IntNode* firstNode = dummyHead->next; 

    newNode->next = dummyHead->next; //newNode's next will point to the first node of linked list
    newNode->prev = dummyHead; //newNode is now the first node, so its prev points to dummyHead
    firstNode->prev = newNode; //firstNode is now second node of list; its prev points to newNode
    dummyHead->next = newNode; //dummyHead's next now points to the first node (newNode)
}

//pop_front
void IntList::pop_front() {
    //if list is empty, do nothing
    if (empty()) {
        return;
    }

    //create pointers for the first and second nodes of the list -- helps readability
    IntNode* firstNode = dummyHead->next; //firstNode will be deleted
    IntNode* secondNode = firstNode->next;

    dummyHead->next = secondNode; //since firstNode will be deleted, dummyHead points to the new first node (secondNode)
    secondNode->prev = dummyHead; //secondNode is now the new first node -- its prev points to dummyHead
    delete firstNode; //remove firstNode
}

//push_back
void IntList::push_back(int value) {
    //create new node to pushback
    IntNode* newNode = new IntNode(value);

    //in case the list is empty -- need to reassign node after dummyHead and node before dummyTail
    if (empty()) {
        //list is dummyHead -> newNode -> dummyTail
        dummyHead->next = newNode; //newNode is only node in list -- dummyHead's next points to it
        dummyTail->prev = newNode; //newNode is before dummyTail -- dummyTail's prev points to it
        newNode->next = dummyTail; //need to assign newNode's next pointer to dummyTail
        newNode->prev = dummyHead; //assign newNode's prev pointer to dummyHead
    }
    else {
        IntNode* lastNode = dummyTail->prev; //create lastNode pointer to make readability easier
        lastNode->next = newNode; //newNode is inserted after lastNode -- lastNode's next points to newNode
        newNode->prev = lastNode; //newNode is after lastNode, so its prev points to lastNode
        newNode->next = dummyTail; //newNode is now last node in list, so its next points to dummyTail
        dummyTail->prev = newNode; //dummyTail's prev pointer is reassigned to newNode
    }
}

//pop_back
void IntList::pop_back() {
    //if list is empty, do nothing
    if (empty()) {
        return;
    }

    IntNode* lastNode = dummyTail->prev; //lastNode is the pointer that will be deleted
    IntNode* lastNodePrev = lastNode->prev; //create lastNodePrev pointer to make readability easier
    dummyTail->prev = lastNodePrev; //dummyTail's prev points to second to last node of the list
    lastNodePrev->next = dummyTail; //second to last node of list is now the last node -- its next points to dummyTail
    delete lastNode; //remove lastNode 
}

//empty
bool IntList::empty() const {
    //if list is empty, only dummyHead and dummyTail exist
    return (dummyHead->next == dummyTail);
}

//print forward
ostream & operator<<(ostream &out, const IntList &rhs) {
    //for loop starting from the node after dummyHead and terminates when it reaches dummyTail
    for (IntNode* curr = rhs.dummyHead->next; curr != rhs.dummyTail; curr = curr->next) {
        //if the node is not the last node of the list, it prints out the value and a space
        if (curr != rhs.dummyTail->prev) {
            out << curr->data << ' ';
        }
        //if the node is the last node of the list, it just prints out the value
        else {
            out << curr->data;
        }
    }
    return out;
}

//print reverse
void IntList::printReverse() const {
    //for loop starting from the node before dummyTail and terminates when it reaches dummyHead
    //uses prev to iterate backwards through the list
    for (IntNode* curr = dummyTail->prev; curr != dummyHead; curr = curr->prev) {
        //if the node is not the first node of the list, it prints out the value and a space
        if (curr != dummyHead->next) {
            cout << curr->data << ' ';
        }
        //if the node is the first node of the list, it just prints out the value
        else {
            cout << curr->data;
        }
    }
}



