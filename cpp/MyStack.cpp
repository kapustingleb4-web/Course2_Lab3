#include "MyStack.hpp"
#include <stdexcept>

using namespace std;

void MyStack::push(const string& val) { push_back(val); }

string MyStack::pop() {
    if (size == 0) throw runtime_error("Stack is empty");
    string v = data[size - 1];
    size--;
    return v;
}

string MyStack::peek() const {
    if (size == 0) throw runtime_error("Stack is empty");
    return data[size - 1];
}

string MyStack::toString() const {
    string s = "top> [";
    for (int i = size - 1; i >= 0; --i) s += data[i] + (i ? ", " : "");
    return s + "]";
}

string MyStack::typeName() const { return "MyStack"; }
