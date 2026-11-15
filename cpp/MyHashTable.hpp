#ifndef MYHASHTABLE_HPP
#define MYHASHTABLE_HPP
#include "Container.hpp"
#include <string>
#include <vector>

using namespace std;

// Хеш-таблица (метод цепочек), ключ и значение - строки.
class MyHashTable : public Container {
private:
    struct Node {
        string key;
        string value;
        Node* next;
        Node(const string& k, const string& v, Node* n) : key(k), value(v), next(n) {}
    };
    Node** buckets;
    int capacity;
    int size;

    int hash(const string& key) const;  // djb2 + остаток от деления
    void rehash();                           // удвоение при заполнении > 0.75

public:
    MyHashTable(int cap = 16);
    MyHashTable(const MyHashTable& other);
    MyHashTable& operator=(const MyHashTable& other);
    ~MyHashTable() override;

    void put(const string& key, const string& value);  // O(1) в среднем
    string get(const string& key) const;               // исключение, если нет
    bool contains(const string& key) const;
    bool remove(const string& key);
    int getCapacity() const;
    vector<string> keys() const;

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
