#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;

//declaring functions w/ template

//find the index of the minimum value in vector -- used in selection_sort
template <typename T>
unsigned min_index(const vector<T> &vals, unsigned index);

//selection_sort
template <typename T>
void selection_sort(vector<T> &vals);

//returns element at the index; throws error when index is out of bounds
template <typename T>
T getElement(vector<T> vals, int index);

//copied from instructions to create vector
vector<char> createVector(){
    int vecSize = rand() % 26;
    char c = 'a';
    vector<char> vals;
    for(int i = 0; i < vecSize; i++)
    {
        vals.push_back(c);
        c++;
    }
    return vals;
}

/*------------------------------------------------------------------------------------------*/

int main(){

    //Part B -- copied from instructions
    try { //try/catch block for getElement
        srand(time(0));
        vector<char> vals = createVector();
        char curChar;
        int index;
        int numOfRuns = 10;
        while(--numOfRuns >= 0){
            cout << "Enter a number: " << endl;
            cin >> index;
            curChar = getElement(vals,index);
            cout << "Element located at " << index << ": is " << curChar << endl;
        }
    }
    catch (out_of_range& excpt) { //print out error statement from getElement if index is out of range
        cout << excpt.what() << endl;
    }
    
    cout << endl;

    //my own test harness
    int userNum;
    cout << "Enter a number from 1 - 4: ";
    cin >> userNum;
    cout << endl;

    //testing vector of ints
    if (userNum == 1) {
        vector<int> vals1;
        int size;
        int inputVal;
        cout << "Enter the size of the vector: ";
        cin >> size;
        cout << endl;
        
        //filling the vector with user inputs
        for (int i = 0; i < size; ++i) {
            cout << "Enter an integer: ";
            cin >> inputVal;
            cout << endl;
            vals1.push_back(inputVal);
        }

        //output vector before sorting
        cout << "Vector before selection sort: ";
        for (unsigned int i = 0; i < vals1.size(); ++i) {
            cout << vals1.at(i) << ' ';
        }
        cout << endl;

        //output vector after sorting
        selection_sort(vals1);
        cout << "Vector after selection sort: ";
        for (unsigned int i = 0; i < vals1.size(); ++i) {
            cout << vals1.at(i) << ' ';
        }
        cout << endl;

        //testing getElement on valid index
        cout << getElement(vals1, size - 1) << endl;
        //testing getElement on invalid index -- should throw out of range error
        cout << getElement(vals1, size) << endl;
    }

    //testing vector of chars
    else if (userNum == 2) {
        vector<char> vals2;
        int size;
        char inputVal;
        cout << "Enter the size of the vector: ";
        cin >> size;
        cout << endl;
        
        //filling the vector with user inputs
        for (int i = 0; i < size; ++i) {
            cout << "Enter an character: ";
            cin >> inputVal;
            cout << endl;
            vals2.push_back(inputVal);
        }

        //output vector before sorting
        cout << "Vector before selection sort: ";
        for (unsigned int i = 0; i < vals2.size(); ++i) {
            cout << vals2.at(i) << ' ';
        }
        cout << endl;

        //output vector after sorting
        selection_sort(vals2);
        cout << "Vector after selection sort: ";
        for (unsigned int i = 0; i < vals2.size(); ++i) {
            cout << vals2.at(i) << ' ';
        }
        cout << endl;

        //testing getElement on valid index
        cout << getElement(vals2, size - 2) << endl;
        //testing getElement on invalid index -- should throw out of range error
        cout << getElement(vals2, size) << endl;
    }

    //testing vector of strings
    else if (userNum == 3) {
        vector<string> vals3;
        int size;
        string inputVal;
        cout << "Enter the size of the vector: ";
        cin >> size;
        cout << endl;
        
        //filling the vector with user inputs
        for (int i = 0; i < size; ++i) {
            cout << "Enter a string: ";
            cin >> inputVal;
            cout << endl;
            vals3.push_back(inputVal);
        }

        //output vector before sorting
        cout << "Vector before selection sort: ";
        for (unsigned int i = 0; i < vals3.size(); ++i) {
            cout << vals3.at(i) << ' ';
        }
        cout << endl;

        //output vector after sorting
        selection_sort(vals3);
        cout << "Vector after selection sort: ";
        for (unsigned int i = 0; i < vals3.size(); ++i) {
            cout << vals3.at(i) << ' ';
        }
        cout << endl;

        //testing getElement on valid index
        cout << getElement(vals3, size - 1) << endl;
        //testing getElement on invalid index -- should throw out of range error
        cout << getElement(vals3, size) << endl; 
    }

    //testing getElement on an empty vector
    else {
        vector<int> vals4;
        cout << getElement(vals4, 0) << endl;
    }


    return 0;
}

/*--------------------------------------------------------------------------------------*/

//find the index of the minimum value in vector -- used in selection_sort
template <typename T>
unsigned min_index(const vector<T> &vals, unsigned index) {
    unsigned minIndex = index;
    //iterate through vector to keep comparing value at i and minIndex
    //start from index after minIndex because minIndex doesn't need to be compared to itself
    for (unsigned i = minIndex + 1; i < vals.size(); ++i) { 
        if (vals.at(i) < vals.at(minIndex)) {
            minIndex = i; //if value at i is smaller than value at minIndex, assign accordingly
        }
    }
    return minIndex;
}

//selection sort
template <typename T>
void selection_sort(vector<T> &vals) {
    unsigned minIndex;
    //using loops to iterate through vector -- if a value is smaller than value at i, they are swapped
    //essentially separating vector into unsorted and sorted parts until entire vector is sorted
    for (unsigned i = 0; i < vals.size(); ++i) {
        minIndex = min_index(vals, i); //assign the return value of min_index to a variable for better readability when swapping
        swap(vals.at(i), vals.at(minIndex));
    }
}

//returns element at the index; throws error when index is out of bounds
template <typename T>
T getElement(vector<T> vals, int index) {
    int size = vals.size(); //since index is an int, assign vals.size() to an int variable for easier comparison
    
    //if index is larger than vals.size() or negative, throw an out of range error
    if (index >= size || index < 0) {
        throw out_of_range("out of range exception occured");
    }
    return vals.at(index);
}


