#ifndef __TREE_H
#define __TREE_H

#include "Node.h"

class Tree {
private:
  Node *root;

public:
  //constructor
  Tree();

  //destructor
  ~Tree();

  //insert: inserts new key into tree
  void insert(const string&);

  //preOrder: prints out nodes
  void preOrder() const;

  //inOrder: prints out nodes
  void inOrder() const;

  //postOrder: prints out nodes
  void postOrder() const;

  //remove: removes key that's passed in
  void remove(const string&);

  //search: returns true if key is found
  bool search (const string&) const;

private:
  // Add additional functions/variables here
  
  //split: helper function for insert
  void split(Node*);

  //preOrder: helper function for preOrder
  void preOrder(Node*) const;

  //inOrder: helper function for inOrder
  void inOrder(Node*) const;

  //postOrder: helper function for postOrder
  void postOrder(Node*) const;

  //recurDelete: helper function for destructor
  void recurDelete(Node*);
    
};

#endif