#ifndef DOUBLYLIST_HPP
#define DOUBLYLIST_HPP
#include "Container.hpp"
#include <string>
#include <vector>

using namespace std;

// Двусвязный список строк: у каждого узла есть prev и next.
class DoublyList : public Container {
private:
    struct Node {
        string data;
        Node* prev;
        Node* next;
        Node(const string& val) : data(val), prev(nullptr), next(nullptr) {}
    };
    Node* head;
    Node* tail;
    int size;

    Node* findNode(const string& val) const;
    void unlink(Node* n);  // вырезать узел - O(1)

public:
    DoublyList();
    DoublyList(const DoublyList& other);
    DoublyList& operator=(const DoublyList& other);
    ~DoublyList() override;

    void push_front(const string& val);                                // O(1)
    void push_back(const string& val);                                 // O(1)
    bool insert_before(const string& target, const string& val);  // O(n)
    bool insert_after(const string& target, const string& val);   // O(n)
    void pop_front();                                                       // O(1)
    void pop_back();                                                        // O(1)
    bool remove_by_value(const string& val);                           // O(n)
    bool remove_before(const string& target);                          // O(n)
    bool remove_after(const string& target);                           // O(n)
    int find(const string& val) const;                                 // O(n)
    string get(int index) const;                                       // O(n), с ближнего конца
    vector<string> getData() const;
    string toReverseString() const;                                    // чтение назад по prev

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
