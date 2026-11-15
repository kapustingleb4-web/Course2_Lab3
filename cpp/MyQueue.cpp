#include "MyQueue.hpp"
#include <stdexcept>

using namespace std;

void MyQueue::push(const string& val) { push_back(val); }

string MyQueue::pop() {
    if (size == 0) throw runtime_error("Queue is empty");
    string v = data[0];
    remove_at(0);
    return v;
}

string MyQueue::front() const {
    if (size == 0) throw runtime_error("Queue is empty");
    return data[0];
}

string MyQueue::toString() const {
    string s = "front> [";
    for (int i = 0; i < size; ++i) s += (i ? ", " : "") + data[i];
    return s + "] <back";
}

string MyQueue::typeName() const { return "MyQueue"; }
