#include "IntList.h"
#include <iostream>
using namespace std;

int main() {
    cout << "Enter a test number(1-3): "; //making lists testing different funcitons
	int test;
	cin >> test;
	cout << endl;

    //tests constructor, destructor, push_front, pop_front, empty
    if (test == 1) {
        cout << endl;
        cout << "list1 constructor called" << endl;
        IntList list1;
        cout << "testing if empty list is empty" << endl;
        cout << list1.empty() << endl;

        cout << "pushfront 10" << endl;
        list1.push_front(10);
        cout << "pushfront 20" << endl;
        list1.push_front(20);
        cout << "pushfront 30" << endl;
        list1.push_front(30);

        cout << "testing if non-empty list is empty:" << endl;
        cout << list1.empty() << endl;

        cout << "list1: " << list1 << endl;
        cout << "pop front" << endl;
        list1.pop_front();
        cout << "list1: " << list1 << endl;
        cout << "pop front" << endl;
        list1.pop_front();
        cout << "list1: " << list1 << endl;
        cout << "pop front" << endl;
        list1.pop_front();
        cout << "list1: " << list1 << endl; 
      
        //after the pop_fronts, list is now empty
        cout << "testing if empty list is empty:" << endl;
        cout << list1.empty() << endl;
    }

    if (test == 1) {
        cout << "list1 destructor called" << endl;
    }

    //tests push_back, pop_back, empty
    if (test == 2) {
        cout << endl;
        cout << "list2 constructor called" << endl;
        IntList list2;

        cout << "pushback 10" << endl;
        list2.push_back(10);
        cout << "pushback 20" << endl;
        list2.push_back(20);
        cout << "pushback 30" << endl;
        list2.push_back(30);
        cout << "list2: " << list2 << endl;
      
        cout << "testing if non-empty list is empty:" << endl;
        cout << list2.empty() << endl;

        cout << "pop front" << endl;
        list2.pop_front();
        cout << "list2: " << list2 << endl;
        cout << "pop back" << endl;
        list2.pop_back();
        cout << "list2: " << list2 << endl;
        cout << "pop back" << endl;
        list2.pop_back();
        cout << "list2: " << list2 << endl;

        //list should be empty now
        cout << "testing if empty list is empty: " << endl;
        cout << list2.empty() << endl;

        //checking if pop_back function can handle empty list case
        cout << "pop back" << endl;
        list2.pop_back();
        cout << "list2: " << list2 << endl;

        cout << "testing if empty list is empty: " << endl;
        cout << list2.empty() << endl;
    }

    if (test == 2) {
        cout << "list2 destructor called" << endl;
    }

    //testing printReverse
    if (test == 3) {
        cout << endl;
        cout << "list3 constructor called" << endl;
        IntList list3;

        cout << "printing empty list in reverse:" << endl;
        list3.printReverse();
        cout << endl;

        cout << "pushback 10" << endl;
        list3.push_back(10);
        cout << "pushback 20" << endl;
        list3.push_back(20);
        cout << "pushfront 0" << endl;
        list3.push_front(0);

        cout << "printing list3 in reverse:" << endl;
        list3.printReverse();
        cout << endl;
    }
    return 0;
}
