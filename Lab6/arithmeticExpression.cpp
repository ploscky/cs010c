#include <fstream>
#include <sstream>
#include <stack>
#include <string>
#include "arithmeticExpression.h"

using namespace std;

//constructor
arithmeticExpression::arithmeticExpression(const string &expression) : infixExpression(expression), root(nullptr) {}

//recursive delete function (for destructor)
void arithmeticExpression::recurDelete(TreeNode *curr) {
    //base case: return when curr reaches nullptr
    if (curr != nullptr) {
        recurDelete(curr->left); //delete left subtree
        recurDelete(curr->right); //delete right subtree
        delete curr;
    }
}

//destructor
arithmeticExpression::~arithmeticExpression() {
    recurDelete(root); //calls helper delete function
}

//buildTree function
void arithmeticExpression::buildTree() {
    string postfixEx = infix_to_postfix(); //string converted to postfix so building tree is easier
    stack<TreeNode*> expTree;
    char key = 'a'; //for constructing the TreeNode

    //loop through entire postfix expression to build tree
    for (unsigned int i = 0; i < postfixEx.size(); ++i) {
        TreeNode* newNode = new TreeNode(postfixEx.at(i), key); //construct a new node
        //if the node is an operation (not a letter), pop two on stack and add to the tree
        if (!isalpha(postfixEx.at(i))) {
            newNode->right = expTree.top();
            expTree.pop();
            newNode->left = expTree.top();
            expTree.pop();
        }
        //for all characters in string, add to stack
        expTree.push(newNode);
        root = newNode; //root is assigned to the top of the stack
        ++key; //increment key to loop through again
    }
}

//helper infix function (recursive)
void arithmeticExpression::infix(TreeNode *curr) {
    //base case: curr reaches nullptr
    if (curr != nullptr) {
        //if curr is an operator (internal node), print open parenthesis
        if (curr->left != nullptr) {
            cout << '(';
        }
        infix(curr->left); //print out left subtree
        cout << curr->data;
        infix(curr->right); //print out right subtree
        //print out closed parenthesis if curr is an operator
        if (curr->left != nullptr) {
            cout << ')';
        }
    }
}

//infix function
void arithmeticExpression::infix() {
    infix(root);
}

//helper prefix function (recursive)
void arithmeticExpression::prefix(TreeNode *curr) {
    //base case: curr reaches nullptr
    if (curr != nullptr) {
        cout << curr->data;
        prefix(curr->left); //print out left subtree
        prefix(curr->right); //print out right subtree
    }
}

//prefix function
void arithmeticExpression::prefix() {
    prefix(root);
}

//postfix helper function (recursive)
void arithmeticExpression::postfix(TreeNode *curr) {
    //base case: curr reaches nullptr
    if (curr != nullptr) {
        postfix(curr->left); //print out left subtree
        postfix(curr->right); //print out right subtree
        cout << curr->data;
    }
}

//postfix function
void arithmeticExpression::postfix() {
    postfix(root);
}

//priority function
int arithmeticExpression::priority(char op){
    int priority = 0;
    if(op == '('){
        priority =  3;
    }
    else if(op == '*' || op == '/'){
        priority = 2;
    }
    else if(op == '+' || op == '-'){
        priority = 1;
    }
    return priority;
}

//infix to postfix function
string arithmeticExpression::infix_to_postfix(){
    stack<char> s;
    ostringstream oss;
    char c;
    for(unsigned i = 0; i< infixExpression.size();++i){
        c = infixExpression.at(i);
        if(c == ' '){
            continue;
        }
        if(c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')'){ //c is an operator
            if( c == '('){
                s.push(c);
            }
            else if(c == ')'){
                while(s.top() != '('){
                    oss << s.top();
                    s.pop();
                }
                s.pop();
            }
            else{
                while(!s.empty() && priority(c) <= priority(s.top())){
                    if(s.top() == '('){
                        break;
                    }
                    oss << s.top();
                    s.pop();
                }
                s.push(c);
            }
        }
        else{ //c is an operand
            oss << c;
        }
    }
    while(!s.empty()){
        oss << s.top();
        s.pop();
    }
    return oss.str();
}

