#ifndef DOUBLYLIST_HPP
#define DOUBLYLIST_HPP
#include "Container.hpp"
#include <string>
#include <vector>

// Двусвязный список строк: у каждого узла есть prev и next.
class DoublyList : public Container {
private:
    struct Node {
        std::string data;
        Node* prev;
        Node* next;
        Node(const std::string& val) : data(val), prev(nullptr), next(nullptr) {}
    };
    Node* head;
    Node* tail;
    int size;

    Node* findNode(const std::string& val) const;
    void unlink(Node* n);  // вырезать узел - O(1)

public:
    DoublyList();
    DoublyList(const DoublyList& other);
    DoublyList& operator=(const DoublyList& other);
    ~DoublyList() override;

    void push_front(const std::string& val);                                // O(1)
    void push_back(const std::string& val);                                 // O(1)
    bool insert_before(const std::string& target, const std::string& val);  // O(n)
    bool insert_after(const std::string& target, const std::string& val);   // O(n)
    void pop_front();                                                       // O(1)
    void pop_back();                                                        // O(1)
    bool remove_by_value(const std::string& val);                           // O(n)
    bool remove_before(const std::string& target);                          // O(n)
    bool remove_after(const std::string& target);                           // O(n)
    int find(const std::string& val) const;                                 // O(n)
    std::string get(int index) const;                                       // O(n), с ближнего конца
    std::vector<std::string> getData() const;
    std::string toReverseString() const;                                    // чтение назад по prev

    int getSize() const override;
    void clear() override;
    std::string toString() const override;
    std::string typeName() const override;
    void saveBinary(const std::string& filename) const override;
    void loadBinary(const std::string& filename) override;
    void saveText(const std::string& filename) const override;
    void loadText(const std::string& filename) override;
};
#endif
