#include <iostream>
#include <string>
#include "Tree.h"

using namespace std;

//constructor
Tree::Tree() : root(nullptr) {}


//recurDelete: helper destructor function
void Tree::recurDelete(Node* curr) {
    //base case: return when curr reaches nullptr
    if (curr == nullptr) {
        return;
    }
    recurDelete(curr->left); //delete left subtree
    recurDelete(curr->middle); //delete middle subtree
    recurDelete(curr->right); //delete right subtree
    delete curr;
}


//destructor
Tree::~Tree() {
    recurDelete(root);
}


//insert: inserts new key into tree
void Tree::insert(const string& key) {
    //if tree is empty, make a root
    if (root == nullptr) {
        root = new Node(key);
    }
    //tree is not empty
    else {
        Node* curr = root;
        //move to end of tree to insert as a leaf
        while (curr->left != nullptr) {
            //if node has 2 strings
            if (!curr->large.empty()) { 
                //if key is smaller than small string, move left
                if (key < curr->small) { 
                    curr = curr->left;
                }
                //if key is larger than large string, move right
                else if (key > curr->large) { 
                    curr = curr->right;
                }
                //if key is between small and large string, move down the middle
                else { 
                    curr = curr->middle; 
                }
            }
            //node only has small string
            else { 
                //if key is smaller than small string, move left
                if (key < curr->small) { 
                    curr = curr->left;
                }
                //if key is larger than small string, move to middle
                else { 
                    curr = curr->middle;
                }
            }
        }

        //easy case: leaf node has only one string-- can add a "small" or "large" string w/o splitting
        if (curr->large.empty()) {
            //key smaller than the string-- reassign small and large
            if (key < curr->small) { 
                curr->large = curr->small;
                curr->small = key;
            }
            //key is larger than the string
            else { 
                curr->large = key;
            }
        }
        //hard case: leaf node is full (has 2 strings)-- need to split
        else {
            //key is smaller than small string
            if (key < curr->small) { 
                //create two new nodes
                Node* leftNode = new Node(key);
                Node* rightNode = new Node(curr->large);

                //assign curr's children-- tree is not level right now; will shift later
                curr->left = leftNode;
                curr->middle = rightNode;
                leftNode->parent = curr;
                rightNode->parent = curr;

                //curr's large string is empty-- has been split into 3 nodes
                curr->large = "";
            }
            //key is larger than large string
            else if (key > curr->large) { 
                //create two new nodes
                Node* rightNode = new Node(key);
                Node* leftNode = new Node(curr->small);

                //assign curr's children-- tree is not level right now; will shift later
                curr->left = leftNode;
                curr->middle = rightNode;
                leftNode->parent = curr;
                rightNode->parent = curr;

                //curr's large string is empty-- has been split into 3 nodes
                curr->small = curr->large;
                curr->large = "";
            }
            //new node's key is between small and large
            else if (key > curr->small && key < curr->large) { 
                //create new nodes
                Node* leftNode = new Node(curr->small);
                Node* rightNode = new Node(curr->large);

                //assign curr's children-- tree is not level right now; will shift later
                curr->left = leftNode;
                curr->middle = rightNode;
                leftNode->parent = curr;
                rightNode->parent = curr;

                //curr's large string is empty-- has been split into 3 nodes
                curr->small = key;
                curr->large = "";
            }

            split(curr); //helper function to shift tree so that it's balanced
        }
    }   
}


//split: helper function for insert (balances the tree)
void Tree::split(Node* curr) {
    Node* parent = curr->parent;
    //splitting the root
    if (parent == nullptr) {
        return;
    }
    //splitting/balancing non-root node (only consideres case where parent has 1 string)
    else {
        //balancing middle subtree (inserting on the middle)
        if (parent->small < curr->small) {
            //assign parent's large so it has 2 strings
            parent->large = curr->small;

            //reassign parent's children and delete curr (not needed)
            parent->middle = curr->left;
            parent->right = curr->middle;
            curr->left->parent = parent;
            curr->middle->parent = parent;
            delete curr;
        }
        //balancing left subtree (inserting on the left)
        else {
            //assign parent's small and large so it has 2 strings
            parent->large = parent->small;
            parent->small = curr->small;
                
            //reassign parent's children and delete curr (not needed)
            parent->left = curr->left;
            parent->right = parent->middle;
            parent->middle = curr->middle;
            curr->left->parent = parent;
            curr->middle->parent = parent;
            delete curr;
        }
    }
}


//preOrder: helper recursive function 
void Tree::preOrder(Node* curr) const {
    //base case: curr reaches nullptr
    if (curr == nullptr) {
        return;
    }
    //recursive case 1: one string
    if (curr->large.empty()) {
        cout << curr->small << ", "; //print out root
        preOrder(curr->left); //print out left subtree
        preOrder(curr->middle); //print out middle subtree
    }
    //recursive case 2: two strings (small, left, large, middle, right)
    else {
        cout << curr->small << ", "; //print out root (small)
        preOrder(curr->left); //print out left subtree
        cout << curr->large << ", "; //print out root (large)
        preOrder(curr->middle); //print out middle subtree
        preOrder(curr->right); //print out right subtree
    }
}


//preOrder: follows logic of helper function
void Tree::preOrder() const {
    preOrder(root);
}


//inOrder: helper recursive function
void Tree::inOrder(Node* curr) const {
    //base case: curr reaches nullptr
    if (curr == nullptr) {
        return;
    }
    //recursive case 1: one string
    if (curr->large.empty()) {
        inOrder(curr->left); //print out left subtree
        cout << curr->small << ", "; //print out root
        inOrder(curr->middle); //print out middle subtree
    }
    //recursive case 2: two strings
    else {
        inOrder(curr->left); //print out left subtree
        cout << curr->small << ", "; //print out root (small)
        inOrder(curr->middle); //print out middle subtree
        cout << curr->large << ", "; //print out root (large)
        inOrder(curr->right); //print out right subtree
    }
}


//inOrder: follows logic of helper function
void Tree::inOrder() const {
    inOrder(root);
}


//postOrder: helper recursive function
void Tree::postOrder(Node* curr) const {
    //base case: curr reaches nullptr
    if (curr == nullptr) {
        return;
    }
    //recursive case 1: one string
    if (curr->large.empty()) {
        postOrder(curr->left); //print out left subtree
        postOrder(curr->middle); //print out middle subtree
        cout << curr->small << ", "; //print out root
    }
    //recursive case 2: two strings (left, middle, small, right, large)
    else {
        postOrder(curr->left); //print out left subtree
        postOrder(curr->middle); //print out middle subtree
        cout << curr->small << ", "; //print out root (small)
        postOrder(curr->right); //print out right subtree
        cout << curr->large << ", "; //print out root (large)
    }
}


//postOrder: follows logic of helper function
void Tree::postOrder() const {
    postOrder(root);
}


//search: returns true if the string passed in is found
bool Tree::search (const string &key) const {
    Node* curr = root;
    //iterate through tree
    while (curr != nullptr) {
        //key is found
        if (curr->small == key || curr->large == key) {
            return true;
        }
        //if key is not found, keep moving through tree
        else {
            //if key is smaller than small string, move left
            if (key < curr->small) {
                curr = curr->left;
            }
            //key is larger than small string
            else {
                //if key is larger than large string, move right
                if (!curr->large.empty() && key > curr->large) {
                    curr = curr->right;
                }
                //if key is between small and large string, move down middle
                else {
                    curr = curr->middle;
                }
            }
        }
    }
    return false; //key is not found-- return false
}


//remove: removes string that's passed in (only does cases w/ height of 1)
void Tree::remove(const string &key) {
    Node* curr = root;
    //bring curr down to the key that needs to be removed
    while (curr != nullptr) {
        //gets to the key that needs to be removed-- break loop
        if (key == curr->small || key == curr->large) {
            break;
        }
        //if key isn't found, move through tree (same logic as search)
        else {
            if (key < curr->small) {
                curr = curr->left;
            }
            else {
                if (!curr->large.empty() && key > curr->large) {
                    curr = curr->right;
                }
                else {
                    curr = curr->middle;
                }
            }
        }
    }

    //node has 2 strings
    if (!curr->large.empty()) { 
        //key is curr's small string-- reassign small and large
        if (key == curr->small) {
            curr->small = curr->large;
            curr->large = "";
        }
        //key is curr's large string-- reassign large string
        else {
            curr->large = "";
        }
    }
    //node has 1 string
    else { 
        Node* parent = curr->parent;
        //root is being removed
        if (parent == nullptr) { 
            //root has children
            if (curr->left != nullptr) { 
                //make new root with keys made up of its children's small strings
                Node* newRoot = new Node(curr->left->small); 
                newRoot->large = curr->middle->small;
                root = newRoot;

                //delete the old nodes (basically creating new tree and deleting old one)
                delete curr->left;
                delete curr->middle;
                delete curr;
            }
            //root has no children; just assign nullptr
            else { 
                root = nullptr;
                delete curr;
            }
        }
        //leaf is being removed
        else { 
            //deleting left node
            if (key < parent->small) { 
                //make new root with keys made up of parent's small string and middle child
                Node* newRoot = new Node(parent->small);
                newRoot->large = parent->middle->small;
                root = newRoot;

                //delete the old nodes (basically creating new tree and deleting old one)
                delete parent->left;
                delete parent->middle;
                delete parent;
            }
            //deleting middle node
            else { 
                //make new root with keys made up of parent's large string and left child
                Node* newRoot = new Node(parent->left->small);
                newRoot->large = parent->small;
                root = newRoot;

                //delete the old nodes (basically creating new tree and deleting old one)
                delete parent->left;
                delete parent->middle;
                delete parent;
            }
        }

    }
}