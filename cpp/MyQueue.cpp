#include "MyQueue.hpp"
#include <stdexcept>

void MyQueue::push(const std::string& val) { push_back(val); }

std::string MyQueue::pop() {
    if (size == 0) throw std::runtime_error("Queue is empty");
    std::string v = data[0];
    remove_at(0);
    return v;
}

std::string MyQueue::front() const {
    if (size == 0) throw std::runtime_error("Queue is empty");
    return data[0];
}

std::string MyQueue::toString() const {
    std::string s = "front> [";
    for (int i = 0; i < size; ++i) s += (i ? ", " : "") + data[i];
    return s + "] <back";
}

std::string MyQueue::typeName() const { return "MyQueue"; }
