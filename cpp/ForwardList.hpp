#ifndef FORWARDLIST_HPP
#define FORWARDLIST_HPP
#include "Container.hpp"
#include <string>
#include <vector>

using namespace std;

// Односвязный список строк (head + tail).
class ForwardList : public Container {
private:
    struct Node {
        string data;
        Node* next;
        Node(const string& val, Node* n = nullptr) : data(val), next(n) {}
    };
    Node* head;
    Node* tail;
    int size;

    Node* findNode(const string& val) const;

public:
    ForwardList();
    ForwardList(const ForwardList& other);
    ForwardList& operator=(const ForwardList& other);
    ~ForwardList() override;

    void push_front(const string& val);                                // O(1)
    void push_back(const string& val);                                 // O(1)
    bool insert_before(const string& target, const string& val);  // O(n)
    bool insert_after(const string& target, const string& val);   // O(n)
    void pop_front();                                                       // O(1)
    void pop_back();                                                        // O(n)
    bool remove_by_value(const string& val);                           // O(n)
    bool remove_before(const string& target);                          // O(n)
    bool remove_after(const string& target);                           // O(n)
    int find(const string& val) const;                                 // O(n), -1 если нет
    string get(int index) const;                                       // O(n)
    vector<string> getData() const;
    string toReverseString() const;                                    // чтение с конца (рекурсия)

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
