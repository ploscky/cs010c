#pragma once
#include <iostream>
#include <string>
#include "Node.h"

using namespace std;

class BSTree {
    private:
        Node* root;

        //preOrder helper-- recursively prints out tree from node that's passed in (root, left, right)
        void preOrder(Node*) const;

        //inOrder helper-- recursively prints out tree from node that's passed in (left, root, right)
        void inOrder(Node*) const;

        //postOrder helper-- recursively prints out tree from node that's passed in (left, right, root)
        void postOrder(Node*) const;

        //returns the node if it's found, returns nullptr otherwise
        Node* search(Node*, const string&) const; //helper function for bool search (recursive)

        //returns height of node passed in
        int height(Node*) const; //helper function for int height (recursive)

        //removes node from tree; if count is > 1, decrement count
        void remove(Node*, const string&); //helper function for void remove (recursive)

        //copy constructor-- declaring it here for rule of 3
        BSTree(const BSTree&);

        //copy assignment-- declaring it here for rule of 3
        BSTree& operator=(const BSTree&);

    public:
        //constructor
        BSTree();

        //destructor
        ~BSTree();

        //insert function-- inserts node into BST (if duplicate, increment count)
        void insert(const string&);

        //prints out nodes-- root, left, right
        void preOrder() const;

        //prints out nodes-- left, root, right
        void inOrder() const;

        //prints out nodes-- left, right, root
        void postOrder() const;

        //searches if an element is in the tree; returns true if string is in tree
        //returns false otherwise
        bool search(const string&) const;

        //find and return the largest value in the tree; return an empty string if the tree is empty
        string largest() const;

        //find and return the smallest value in the tree; return an empty string if the tree is empty
        string smallest() const;

        //compute and return the height of a particular string in the tree
        int height(const string&) const;

        //removes specified string from tree (if duplicate node, decrement count)
        void remove(const string&);
};      