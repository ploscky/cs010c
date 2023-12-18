#include <iostream>
#include <string>
#include "Node.h"

using namespace std;

Node::Node(const string& payload)
    : data(payload),
      height(0),
      left(nullptr),
      right(nullptr),
      parent(nullptr) {}