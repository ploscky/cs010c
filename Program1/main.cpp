#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct Node {
    string payload;
    Node* next;
};

//create new node in circular list
Node* newNode(string payload) {
    Node* addNode = new Node; //construct Node

    //initialize payload and next variables
    addNode->payload = payload;
    addNode->next = nullptr;
    return addNode;
}

//create nodes in the list to load the game
Node* loadGame(int n, vector<string> names) {
    Node* head = nullptr;
    Node* prev = nullptr;
    string name;
   
   //use for loop to create n amount of names in the list
    for (int i = 0; i < n; ++i) {
        name = names.at(i);

        //create first node in list
        if (head == nullptr) {
            head = newNode(name); // initialize head specially
            prev = head; //initialize prev so it can be moved

        //creating the other nodes in the list (move prev through list until the end)
        } else {
            prev->next = newNode(name); //keep creating new nodes until end of names
            prev = prev->next;
        }
    }
    
    //if there is at least one node in the list, prev's next is always the head (circular)
    if (prev != nullptr) {
        prev->next = head; // make circular
    }
    return head;
}

void print(Node* start) { // prints list
    Node* curr = start;
    while (curr != nullptr) {
        cout << curr->payload << endl;
        curr = curr->next;
        if (curr == start) {
            break; // exit circular list
        }
    }
}

Node* runGame(Node* start, int k) { // josephus w circular list, k = num skips
    Node* curr = start;
    Node* prev = curr;

    //while loop terminates if there's only one person left -- curr's next is curr itself
    while (curr->next != curr) { // exit condition, last person standing
        for (int i = 0; i < k; ++i) { // find kth node
          //move prev and curr parallel through list until reaching kth node
          prev = curr;
          curr = curr->next;
        }

        //delete the kth node and move prev and curr so they are still next to each other
        prev->next = curr->next; // delete kth node
        delete curr;
        curr = prev->next;
    }

    return curr; // last person standing
}

/* Driver program to test above functions */
int main() {
    int n=1, k=1; // n = num names; k = num skips (minus 1)
    string name;
    vector<string> names;

    // get inputs
    cin >> n >> k;
    while (cin >> name && name != ".") { names.push_back(name); } // EOF or . ends input

    // initialize and run game
    Node* startPerson = loadGame(n, names);
    Node* lastPerson = runGame(startPerson, k);

    if (lastPerson != nullptr) {
        cout << lastPerson->payload << " wins!" << endl;
    } else {
        cout << "error: null game" << endl;
    }
    delete lastPerson; //delete last person in the list to prevent memory leaks

    return 0;
}

