#ifndef FORWARDLIST_HPP
#define FORWARDLIST_HPP
#include "Container.hpp"
#include <string>
#include <vector>

// Односвязный список строк (head + tail).
class ForwardList : public Container {
private:
    struct Node {
        std::string data;
        Node* next;
        Node(const std::string& val, Node* n = nullptr) : data(val), next(n) {}
    };
    Node* head;
    Node* tail;
    int size;

    Node* findNode(const std::string& val) const;

public:
    ForwardList();
    ForwardList(const ForwardList& other);
    ForwardList& operator=(const ForwardList& other);
    ~ForwardList() override;

    void push_front(const std::string& val);                                // O(1)
    void push_back(const std::string& val);                                 // O(1)
    bool insert_before(const std::string& target, const std::string& val);  // O(n)
    bool insert_after(const std::string& target, const std::string& val);   // O(n)
    void pop_front();                                                       // O(1)
    void pop_back();                                                        // O(n)
    bool remove_by_value(const std::string& val);                           // O(n)
    bool remove_before(const std::string& target);                          // O(n)
    bool remove_after(const std::string& target);                           // O(n)
    int find(const std::string& val) const;                                 // O(n), -1 если нет
    std::string get(int index) const;                                       // O(n)
    std::vector<std::string> getData() const;
    std::string toReverseString() const;                                    // чтение с конца (рекурсия)

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
