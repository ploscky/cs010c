#pragma once
#include <iostream>
#include <string>

using namespace std;

struct Node {
    Node(const string&); //parameterized constructor that takes in a string
    string data;
    int height;
    Node* left;
    Node* right;
    Node* parent;  
};