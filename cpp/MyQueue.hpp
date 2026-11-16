#ifndef MYQUEUE_HPP
#define MYQUEUE_HPP
#include "Container.hpp"
#include <string>
#include <vector>

using namespace std;

class MyQueue : public Container {
private:
    struct Node {
        string val;
        Node* next;
        explicit Node(const string& v) : val(v), next(nullptr) {}
    };
    Node* head;
    Node* tail;
    int size;

public:
    MyQueue();
    MyQueue(const MyQueue& other);
    MyQueue& operator=(const MyQueue& other);
    ~MyQueue() override;

    void push(const string& val);
    string pop();
    string front() const;
    vector<string> getData() const;

    int getSize() const override;
    void clear() override;
    string toString() const override;
    string typeName() const override;
    void saveBinary(const string& filename) const override;
    void loadBinary(const string& filename) override;
    void saveText(const string& filename) const override;
    void loadText(const string& filename) override;
};
#endif
