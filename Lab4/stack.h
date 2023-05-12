#include <stdexcept>

using namespace std;

const int MAX_SIZE = 20; //declare constant MAX_SIZE (20) for data array

template<typename T> //template class so array can be string and integer

class stack {
    public:
        //stack(): constructs an empty stack (size = 0)
        stack();

        //push(T val): inserts a new element (val) of type T (T could be integer or string) into the data.
        void push(T val);

        //pop(): removes the last element from data.
        void pop();

        //pop_two(): removes the last two elements from data. 
        void pop_two();

        //top(): returns the top element of stack (last inserted element).
        T top() const;

        //empty(): returns true if the stack is empty otherwise it returns false.
        bool empty() const;

    private:
        T data[MAX_SIZE]; //data type is T (template) and set to max_size
        int size;
};

/*---------------------------------------------------------------------------------------------------------*/

//constructor
template<typename T>
stack<T>::stack() : size(0) {}

//push function
template<typename T>
void stack<T>::push(T val) {
    //if size is already at MAX_SIZE, cannot add a value-- throw overflow error
    if (size == MAX_SIZE) {
        throw overflow_error("Called push on full stack.");
    }
    //add value by adding one to size
    else {
        data[size] = val;
        ++size;
        }
}

//pop function
template<typename T>
void stack<T>::pop() {
    //if the array is already empty, element cannot be removed-- throw out of range error
    if (empty()) {
        throw out_of_range("Called pop on empty stack.");
    }
    //otherwise just subtract one from size
    else {
        --size;
    }
}

//pop two function
template<typename T>
void stack<T>::pop_two() {
    //if array is already empty, cannot remove elements-- throw out of range error
    if (empty()) {
        throw out_of_range("Called pop_two on empty stack.");
    }
    //if array only has one element, cannot remove 2 elements-- throw out of range error
    else if (size == 1) {
        throw out_of_range("Called pop_two on a stack of size 1.");
    }
    //otherwise, just subtract 2 from size (removing 2 elements)
    else {
        size -= 2;
    }
}

//return top element
template<typename T>
T stack<T>::top() const {
    //if array is empty, there is no top element-- throw underflow error
    if (empty()) {
        throw underflow_error("Called top on empty stack.");
    }
    //otherwise, the top element is the last element of the array (size - 1)
    else {
        return data[size - 1];
    }
}

//is stack empty
template<typename T>
bool stack<T>::empty() const {
    return (size == 0); //if size is 0, the array is empty
}



