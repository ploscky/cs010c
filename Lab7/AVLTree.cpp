#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include "AVLTree.h"

using namespace std;

//constructor
AVLTree::AVLTree() : root(nullptr) {}


//recurDelete: helps destructor
void AVLTree::recurDelete(Node* curr) {
    if (curr != nullptr) {
        recurDelete(curr->left); //deletes left subtree
        recurDelete(curr->right); //deletes right subtree
        delete curr;
    }
}


//destructor
AVLTree::~AVLTree() {
    recurDelete(root);
}


//insert: inserts new string as leaf
void AVLTree::insert(const string& key) {
    Node* newNode = new Node(key); //create new node
    //if tree is empty, add root
    if (root == nullptr) {
        root = newNode;
        newNode->parent = nullptr;
        return;
    }

    //iterate through tree until reaching a leaf so node can be inserted
    Node* curr = root;
    while (curr != nullptr) {
        //if key is smaller than curr, go left
        if (key < curr->data) { 
            //insert as leaf if at end of tree
            if (curr->left == nullptr) { 
                curr->left = newNode;
                newNode->parent = curr;
                curr = nullptr;
            }
            //otherwise keep going left
            else {
                curr = curr->left;
            }
        }
        //if key is larger than curr, go right
        else if (key > curr->data) { 
            //insert as leaf if at end of tree
            if (curr->right == nullptr) { 
                curr->right = newNode;
                newNode->parent = curr;
                curr = nullptr;
            }
            //otherwise keep going right
            else {
                curr = curr->right;
            } 
        }
        //duplicate case-- just return (doesn't have duplicates)
        else { 
            return;
        }
    }
    
    //now need to rotate to balance tree-- rotate "at" newNode's parent
    newNode = newNode->parent; 
    //keep rotating up the tree until reaching the root
    while (newNode != nullptr) {
        rotate(newNode); //using rotate helper function
        newNode = newNode->parent;
    }
}


//rotate: takes care of the 4 rotation cases to balance the tree
void AVLTree::rotate(Node* curr) {
    heightHelper(curr); //call heightHelper to add 1 to height (from the insertion)
    //right-right and right-left case
    if (balanceFactor(curr) <= -2) { 
        //right-right case-- need to rotate left once to balance
        if (balanceFactor(curr->right) <= -1) { 
            rotateLeft(curr);
        }
        //right-left case-- need to rotate twice
        else if (balanceFactor(curr->right) >= 1) { 
            rotateRight(curr->right); //first rotate right-- still unbalanced
            rotateLeft(curr); //rotate left to get valid balance factor
        }
    }
    //left-left and left-right case
    else if (balanceFactor(curr) >= 2) { 
        //left-left case-- need to rotate right once to balance
        if (balanceFactor(curr->left) >= 1) { 
            rotateRight(curr);
        }
        //left-right case
        else if (balanceFactor(curr->left) <= -1) { 
            rotateLeft(curr->left); //first rotate left-- still unbalanced
            rotateRight(curr); //rotate right to get valid balance factor
        }
    }
}


//rotateLeft: helper for rotate function
void AVLTree::rotateLeft(Node* curr) {
    Node* updateChild = curr->right->left; //declare the right-left child that will be set after rotating
    //rotate at root
    if (curr->parent == nullptr) { 
        root = curr->right; //root needs to be reassigned because it was rotated left
        root->parent = nullptr;
    }
    //not rotating at root
    else {
        replaceChild(curr->parent, curr, curr->right); //use replaceChild to replace curr with its right child
    }
    setChild(curr->right, "left", curr); //set curr as curr->right's left child (rotated left)
    setChild(curr, "right",  updateChild); //update curr's new subtree if its replacement had children
}


//rotateRight: helper for rotate function
void AVLTree::rotateRight(Node* curr) {
    Node* updateChild = curr->left->right; //declare the left-right child that will be set after rotating
    //rotate at root
    if (curr->parent == nullptr) {
        root = curr->left; //root needs to be reassigned because it was rotated right
        root->parent = nullptr;
    }
    //not rotating at root
    else {
        replaceChild(curr->parent, curr, curr->left); //use replaceChild to replace curr with its left child
    }
    setChild(curr->left, "right", curr); //set curr as curr->left's child (rotated right)
    setChild(curr, "left", updateChild); //update curr's new subtree if its replacement had children
}


//heightHelper: updates height
void AVLTree::heightHelper(Node* curr) {
    //initialize left and right subtree height to default of -1 (doesn't exist)
    int leftHeight = -1; 
    int rightHeight = -1;
    //if left subtree exists, update its height
    if (curr->left != nullptr) {
        leftHeight = curr->left->height;
    }
    //if right subtree exists, update its height
    if (curr->right != nullptr) {
        rightHeight = curr->right->height;
    }

    //update curr's height to the maximum of the two subtrees (+1 because counting levels)
    curr->height = max(leftHeight, rightHeight) + 1;
}


//setChild: sets child of parent (logic from zybooks)
void AVLTree::setChild(Node* parent, const string& key, Node* child) {
    //if the key isn't explicitly left or right, just return
    if (key != "left" && key != "right") {
        return;
    }

    //set left child
    if (key == "left") {
        parent->left = child;
    }
    //set right child
    else {
        parent->right = child;
    }

    //set child's parent if it's not the root
    if (child != nullptr) {
        child->parent = parent;
    }
    //update height
    heightHelper(parent);
}


//replaceChild: replaces currChild with newChild (logic from zybooks)
void AVLTree::replaceChild(Node* parent, Node* currChild, Node* newChild) {
    //replace left child using setChild
    if (parent->left == currChild) {
        setChild(parent, "left", newChild);
    }
    //replace right child using setChild
    else if (parent->right == currChild) {
        setChild(parent, "right", newChild);
    }
}


//balanceFactor: returns balance factor of a node
int AVLTree::balanceFactor(Node* curr) const {
    int leftHeight = -1; //initialze left height to -1 (doesn't exist)
    //update leftHeight if left subtree exists
    if (curr->left != nullptr) {
        leftHeight = curr->left->height;
    }

    int rightHeight = -1;
    //update rightHeight if right subtree exists
    if (curr->right != nullptr) {
        rightHeight = curr->right->height;
    }

    //return their difference
    return leftHeight - rightHeight;
}


//printBalanceFactors: helper function-- prints the nodes' data and their balance factors
void AVLTree::printBalanceFactors(Node* curr) const {
    if (curr != nullptr) {
        printBalanceFactors(curr->left); //print left subtreee
        cout << curr->data << "(" << balanceFactor(curr) << "), ";
        printBalanceFactors(curr->right); //print right subtree
    }
}


//printBalanceFactors
void AVLTree::printBalanceFactors() const {
    printBalanceFactors(root);
    cout << endl;
}


//visualizeTree
void AVLTree::visualizeTree(const string &outputFilename) {
    ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){
        cout<<"Error"<<endl;
        return;
    }
    outFS<<"digraph G {"<<endl;
    visualizeTree(outFS,root);
    outFS<<"}";
    outFS.close();
    string jpgFilename = outputFilename.substr(0,outputFilename.size()-4)+".jpg";
    string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
}


//visualizeTree
void AVLTree::visualizeTree(ofstream & outFS, Node *n){
    if(n){
        if(n->left){
            visualizeTree(outFS,n->left);
            outFS<<n->data <<" -> " <<n->left->data<<";"<<endl;    
        }

        if(n->right){
            visualizeTree(outFS,n->right);
            outFS<<n->data <<" -> " <<n->right->data<<";"<<endl;    
        }
    }
}