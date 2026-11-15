#include "MyStack.hpp"
#include <stdexcept>

void MyStack::push(const std::string& val) { push_back(val); }

std::string MyStack::pop() {
    if (size == 0) throw std::runtime_error("Stack is empty");
    std::string v = data[size - 1];
    size--;
    return v;
}

std::string MyStack::peek() const {
    if (size == 0) throw std::runtime_error("Stack is empty");
    return data[size - 1];
}

std::string MyStack::toString() const {
    std::string s = "top> [";
    for (int i = size - 1; i >= 0; --i) s += data[i] + (i ? ", " : "");
    return s + "]";
}

std::string MyStack::typeName() const { return "MyStack"; }
