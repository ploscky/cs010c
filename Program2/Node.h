#pragma once
#include <iostream>
#include <string>

using namespace std;

class Node {
    private:
        string payload;
        int count; //amount of nodes that have same payload
        Node* left;
        Node* right;
        Node* parent;
    
    public:
        //parameterized constructor
        Node(string&);

        //accessors
        string getString() const;
        int getCount() const;
        Node* getLeft() const;
        Node* getRight() const;
        Node* getParent() const;

        //mutators
        void setLeft(Node*);
        void setRight(Node*);
        void setParent(Node*);
        void setPayload(const string&);
        void setCount(int);

        //adding or subtracting from a node's count
        void increment();
        void decrement();
};
