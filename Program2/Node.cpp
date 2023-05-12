#include <iostream>
#include <string>
#include "Node.h"

using namespace std;

Node::Node(string& data)
    : payload(data),
      count(1), //count starts from 1 (when node is first inserted, count = 1)
      left(nullptr),
      right(nullptr),
      parent(nullptr) {}


//accessors
string Node::getString() const {
    return payload;
}

int Node::getCount() const {
    return count;
}

Node* Node::getLeft() const {
    return left;
}

Node* Node::getRight() const {
    return right;
}

Node* Node::getParent() const {
    return parent;
}


//mutators
void Node::setLeft(Node* leftVal) {
    left = leftVal;
}

void Node::setRight(Node* rightVal) {
    right = rightVal;
}

void Node::setParent(Node* parentVal) {
    parent = parentVal;
}

void Node::setPayload(const string& data) {
    payload = data;
}

void Node::setCount(int num) {
    count = num;
}


//adding/subtracting from count
void Node::increment() {
    ++count;
}

void Node::decrement() {
    --count;
}