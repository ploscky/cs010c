#include <iostream>
#include <string>
#include <algorithm> //for finding max in height function
#include "BSTree.h"

using namespace std;

//constructor: empty tree-- root is just nullptr
BSTree::BSTree() : root(nullptr) {}


//destructor: keep removing the root until tree is empty (root = nullptr)
BSTree::~BSTree() { 
    while (root != nullptr) {
        remove(root->getString());
    }
}


//insert function
void BSTree::insert(const string& data) {
    Node* curr = root;
    //if tree is empty, insert first node (root) into tree
    if (root == nullptr) {
        Node* newNode = new Node(data);
        root = newNode;
    }

    //inserting new nodes as leaves (tree is not empty)
    else {
        //keep going through the tree until curr reaches nullptr (go to end of tree)
        while (curr != nullptr) {
            //if new node is a duplicate, just increment the node and return
            if (data == curr->getString()) {
                curr->increment();
                return;
            }
            //if new node is smaller than curr, insert in left subtree
            else if (data < curr->getString()) {
                //node is inserted as leaf-- inserted when curr's left is nullptr
                if (curr->getLeft() == nullptr) {
                    Node* newNode = new Node(data);
                    curr->setLeft(newNode); //set curr's left
                    newNode->setParent(curr); //set new node's parent
                    curr = nullptr;
                }
                //if curr has not reached a leaf, keep going left
                else {
                    curr = curr->getLeft();
                }
            }
            //if new node is greater than current node, insert in right subtree
            else {
                //node is inserted as leaf-- inserted when curr's right is nullptr
                if (curr->getRight() == nullptr) {
                    Node* newNode = new Node(data);
                    curr->setRight(newNode); //set curr's right
                    newNode->setParent(curr); //set new node's parent
                    curr = nullptr;
                }
                //if curr hasn't reached a leaf, keep going right
                else {
                    curr = curr->getRight();
                }
            }
        }
    }
}


//inOrder print helper function (recursive)
void BSTree::inOrder(Node* root) const {
    //base case-- start printing once reaching end of tree (root = nullptr)
    if (root == nullptr) {
        return;
    }
    //basically recursively printing out mini left and right subtrees--
    //once those subtrees become just a single node (root), they're printed
    inOrder(root->getLeft()); //first go through left subtree
    cout << root->getString() << '(' << root->getCount() << ')' << ", "; //print out root
    inOrder(root->getRight()); //go through right subtree
}


//inOrder print function
void BSTree::inOrder() const {
    inOrder(root);
}


//preOrder print helper function (recursive)
//same logic as inOrder, just switching around lines to root, left, right
void BSTree::preOrder(Node* root) const {
    if (root == nullptr) {
        return;
    }
    cout << root->getString() << '(' << root->getCount() << ')' << ", ";
    preOrder(root->getLeft());
    preOrder(root->getRight());
}


//preOrder print function
void BSTree::preOrder() const {
    preOrder(root);
}


//postOrder print helper function (recursive)
//same logic as inOrder, just switching around lines to left, right, root
void BSTree::postOrder(Node* root) const {
    if (root == nullptr) {
        return;
    }
    postOrder(root->getLeft());
    postOrder(root->getRight());
    cout << root->getString() << '(' << root->getCount() << ')' << ", ";
}


//postOrder print function
void BSTree::postOrder() const {
    postOrder(root);
}


//search helper function: finds and returns node with the key that's passed in (recursive)
Node* BSTree::search(Node* curr, const string& key) const {
    //if the tree is empty (node passed in is nullptr)
    if (curr == nullptr) {
        return nullptr; //node passed in is nullptr; just return nullptr
    }

    //if the node passed in holds data
    else {
        //base case: when curr's string equals key, return curr
        if (curr->getString() == key) {
            return curr;
        }
        //searching in right subree (key is larger than curr)
        else if (curr->getString() < key) {
            return search(curr->getRight(), key); //key is larger than curr; keep moving right recursively
        }
        //left subtree (key is smaller than curr)
        else if (curr->getString() > key) {
            return search(curr->getLeft(), key); //key is smaller than curr; keep moving left recursively
        }
        //key is not found in tree: return nullptr
        else {
            return nullptr; 
        }
    }
}


//search function: uses helper search function starting from root
bool BSTree::search(const string& key) const {
    return (search(root, key) != nullptr);
}


//largest string: finds and returns largest string in tree
string BSTree::largest( ) const {
    //if tree is empty, return empty string
    if (root == nullptr) {
        return "";
    }

    //if tree isn't empty
    else {
        Node* curr = root;
        //largest string is the rightmost node-- keep moving right until end of tree
        while (curr->getRight() != nullptr) {
            curr = curr->getRight();
        }
        return curr->getString();
    }
}


//smallest string: finds and returns smallest string in tree
string BSTree::smallest( ) const {
    //if tree is empty, return empty string
    if (root == nullptr) {
        return "";
    }

    //if tree isn't empty
    else {
        Node* curr = root;
        //smallest string is the leftmost node-- keep moving left until end of tree
        while (curr->getLeft() != nullptr) {
            curr = curr->getLeft();
        }
        return curr->getString();
    }
}


//height helper function: finds height of the node passed in (recursive)
int BSTree::height(Node* curr) const {
    //if node passed in equals nullptr (doesn't exist), return -1
    if (curr == nullptr) {
        return -1;
    }

    //base case: if the node passed in is a leaf, return 0
    else if (curr->getLeft() == nullptr && curr->getRight() == nullptr) {
        return 0;
    }

    //if node passed in is an internal node, return height of left or right subtree (whichever is largest)
    else {
        //recursively call the larger height function until reaching a leaf
        //add 1 because started from 0
        return 1 + max(height(curr->getLeft()), height(curr->getRight()));
    }
    return 0;
}


//height of tree: finds height using helper height and helper search function
int BSTree::height(const string& key) const {
    return height(search(root, key)); //use search to find the node that holds the key
}


//remove helper function: removes node that's passed in
void BSTree::remove(Node* curr, const string& key) {
    //node is found
    if (curr->getString() == key) { 
        //case 1 (base case): removing a leaf
        if (curr->getLeft() == nullptr && curr->getRight() == nullptr) { 
            //if node is root-- tree becomes empty
            if (curr->getParent() == nullptr) { 
                root = nullptr;
                delete curr;
            }
            //if curr is a left child of another node
            else if (curr->getParent()->getLeft() == curr) { 
                curr->getParent()->setLeft(nullptr); //just delete curr; no need to replace
                delete curr;
                
            }
            //if curr is a right child of another node
            else { 
                curr->getParent()->setRight(nullptr);
                delete curr;
            }
            return;
        }

        //case 2: removing an internal node with a left child
        else if (curr->getLeft() != nullptr) {
            Node* prev = curr->getLeft(); //going to replace w/ node in left subtree

            //when prev reaches nullptr, prevent continuing with program or else get infinite recursion
            if (prev == nullptr) {
                prev = nullptr;
            }
            //if prev hasn't reached nullptr yet, keep going right (go to rightmost node of left subtree)
            else {
                while (prev->getRight() != nullptr) { 
                    prev = prev->getRight();
                }
            }

            //copy the data from prev (node you want to replace with) to curr (node that will be replaced)
            curr->setPayload(prev->getString());
            curr->setCount(prev->getCount());

            //since prev has been used as replacement, decrement count if it's >1
            if (prev->getCount() > 1) {
                prev->decrement();
            }

            //recursively call remove w/ prev (duplicate node) until reaching base case
            remove(prev, prev->getString());
            return;
        }

        //case 3: removing an internal node that doesn't have left child
        else { 
            Node* succ = curr->getRight(); //going to replace w/ node in right subtree

            //when succ reaches nullptr, prevent continuing with program or else get infinite recursion
            if (succ == nullptr) {
                succ = nullptr;
            }
            //if succ hasn't reached nullptr yet, keep going left (go to leftmost node of right subtree)
            else {
                while (succ->getLeft() != nullptr) { 
                    succ = succ->getLeft();
                }
            }

            //copy the data from succ (node you want to replace with) to curr (node that will be replaced)
            curr->setPayload(succ->getString());
            curr->setCount(succ->getCount());

            //since succ has been used as a replacement, decrement count if it's >1
            if (succ->getCount() > 1) {
                succ->decrement();
            }

            //recursively call remove w/ prev (duplicate node) until reaching base case
            remove(succ, succ->getString());
            return;
        }
    }
}


//remove function: removes node with key that's passed in
void BSTree::remove(const string& key) {
    //first find the node that will be removed with search helper function
    Node* removeNode = search(root, key); 

    //only remove if the node is found
    if (search(key)) {
        //if the count is >1, just decrement count
        if (removeNode->getCount() > 1) {
            removeNode->decrement();
        }
        //otherwise remove the node using remove helper function
        else {
            remove(removeNode, key);
        }
    }
}