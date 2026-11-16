#include "MyQueue.hpp"
#include "Serializer.hpp"
#include <stdexcept>

using namespace std;

MyQueue::MyQueue() : head(nullptr), tail(nullptr), size(0) {}

MyQueue::MyQueue(const MyQueue& other) : head(nullptr), tail(nullptr), size(0) {
    for (Node* cur = other.head; cur; cur = cur->next) push(cur->val);
}

MyQueue& MyQueue::operator=(const MyQueue& other) {
    if (this != &other) {
        clear();
        for (Node* cur = other.head; cur; cur = cur->next) push(cur->val);
    }
    return *this;
}

MyQueue::~MyQueue() { clear(); }

void MyQueue::push(const string& val) {
    Node* n = new Node(val);
    if (tail) tail->next = n;
    else head = n;
    tail = n;
    size++;
}

string MyQueue::pop() {
    if (!head) throw runtime_error("Queue is empty");
    Node* n = head;
    string v = n->val;
    head = head->next;
    if (!head) tail = nullptr;
    delete n;
    size--;
    return v;
}

string MyQueue::front() const {
    if (!head) throw runtime_error("Queue is empty");
    return head->val;
}

vector<string> MyQueue::getData() const {
    vector<string> v;
    for (Node* cur = head; cur; cur = cur->next) v.push_back(cur->val);
    return v;
}

int MyQueue::getSize() const { return size; }

void MyQueue::clear() {
    while (head) {
        Node* n = head;
        head = head->next;
        delete n;
    }
    tail = nullptr;
    size = 0;
}

string MyQueue::toString() const {
    string s = "front> [";
    for (Node* cur = head; cur; cur = cur->next) s += (cur == head ? "" : ", ") + cur->val;
    return s + "] <back";
}

string MyQueue::typeName() const { return "MyQueue"; }

void MyQueue::saveBinary(const string& filename) const { Serializer::saveStringsBinary(filename, typeName(), getData()); }

void MyQueue::loadBinary(const string& filename) {
    auto items = Serializer::loadStringsBinary(filename, typeName());
    clear();
    for (auto& s : items) push(s);
}

void MyQueue::saveText(const string& filename) const { Serializer::saveStringsText(filename, typeName(), getData()); }

void MyQueue::loadText(const string& filename) {
    auto items = Serializer::loadStringsText(filename, typeName());
    clear();
    for (auto& s : items) push(s);
}
