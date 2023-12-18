#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "Node.h"

using namespace std;

class AVLTree {
    private:
        Node* root;

        //implement four possible imbalance cases and update the parent of the given node
        void rotate(Node*); 

        //rotate the subtree to left at the given node and returns the new subroot
        void rotateLeft(Node*);

        //rotate the subtree to right at the given node and returns the new subroot
        void rotateRight(Node*);

        //helper recursive function for printing balance factors
        void printBalanceFactors(Node*) const;

        //visualeTree helper
        void visualizeTree(ofstream&, Node*);

        //updates height of tree
        void heightHelper(Node*);

        //sets a node as the parent's left or right child, updates the child's parent pointer, and updates the parent node's height
        void setChild(Node*, const string&, Node*);

        //replaces one of a node's existing child pointers with a new value, utilizing AVLTreeSetChild to perform the replacement
        void replaceChild(Node*, Node*, Node*);

        //helper delete function for destructor
        void recurDelete(Node*);

    public:
        //constructor
        AVLTree();

        //destructor
        ~AVLTree();

        //insert an item to the binary search tree and perform rotation if necessary
        void insert(const string&);

        //return the balance factor of a given node
        int balanceFactor(Node*) const;

        //traverse and print the tree in inorder notation
        //print the string followed by its balance factor in parentheses followed by a , and one space
        void printBalanceFactors() const;

        //generate dotty file and visualize the tree using dotty program
        void visualizeTree(const string&);
};