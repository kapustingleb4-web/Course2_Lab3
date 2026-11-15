#ifndef MYHASHTABLE_HPP
#define MYHASHTABLE_HPP
#include "Container.hpp"
#include <string>
#include <vector>

// Хеш-таблица (метод цепочек), ключ и значение - строки.
class MyHashTable : public Container {
private:
    struct Node {
        std::string key;
        std::string value;
        Node* next;
        Node(const std::string& k, const std::string& v, Node* n) : key(k), value(v), next(n) {}
    };
    Node** buckets;
    int capacity;
    int size;

    int hash(const std::string& key) const;  // djb2 + остаток от деления
    void rehash();                           // удвоение при заполнении > 0.75

public:
    MyHashTable(int cap = 16);
    MyHashTable(const MyHashTable& other);
    MyHashTable& operator=(const MyHashTable& other);
    ~MyHashTable() override;

    void put(const std::string& key, const std::string& value);  // O(1) в среднем
    std::string get(const std::string& key) const;               // исключение, если нет
    bool contains(const std::string& key) const;
    bool remove(const std::string& key);
    int getCapacity() const;
    std::vector<std::string> keys() const;

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
