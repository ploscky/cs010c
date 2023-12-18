#include "Node.h"

Node::Node(const string& key)
    : small(key), 
      large(""), 
      left(nullptr), 
      middle(nullptr), 
      right(nullptr), 
      parent(nullptr) {}