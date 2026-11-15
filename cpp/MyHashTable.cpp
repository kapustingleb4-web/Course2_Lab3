#include "MyHashTable.hpp"
#include "Serializer.hpp"
#include <stdexcept>

using namespace std;

MyHashTable::MyHashTable(int cap) : capacity(cap < 1 ? 1 : cap), size(0) {
    buckets = new Node*[capacity];
    for (int i = 0; i < capacity; ++i) buckets[i] = nullptr;
}

MyHashTable::MyHashTable(const MyHashTable& other) : MyHashTable(other.capacity) {
    for (int i = 0; i < other.capacity; ++i)
        for (Node* cur = other.buckets[i]; cur; cur = cur->next) put(cur->key, cur->value);
}

MyHashTable& MyHashTable::operator=(const MyHashTable& other) {
    if (this == &other) return *this;
    clear();
    for (int i = 0; i < other.capacity; ++i)
        for (Node* cur = other.buckets[i]; cur; cur = cur->next) put(cur->key, cur->value);
    return *this;
}

MyHashTable::~MyHashTable() {
    clear();
    delete[] buckets;
}

int MyHashTable::hash(const string& key) const {
    unsigned long long h = 5381;
    for (unsigned char c : key) h = h * 33 + c;
    return static_cast<int>(h % capacity);
}

void MyHashTable::rehash() {
    Node** old = buckets;
    int oldCap = capacity;
    capacity *= 2;
    buckets = new Node*[capacity];
    for (int i = 0; i < capacity; ++i) buckets[i] = nullptr;
    for (int i = 0; i < oldCap; ++i) {
        Node* cur = old[i];
        while (cur) {
            Node* next = cur->next;
            int idx = hash(cur->key);
            cur->next = buckets[idx];
            buckets[idx] = cur;
            cur = next;
        }
    }
    delete[] old;
}

void MyHashTable::put(const string& key, const string& value) {
    int idx = hash(key);
    for (Node* cur = buckets[idx]; cur; cur = cur->next)
        if (cur->key == key) { cur->value = value; return; }
    buckets[idx] = new Node(key, value, buckets[idx]);
    size++;
    if (size * 4 > capacity * 3) rehash();
}

string MyHashTable::get(const string& key) const {
    for (Node* cur = buckets[hash(key)]; cur; cur = cur->next)
        if (cur->key == key) return cur->value;
    throw out_of_range("Key not found: " + key);
}

bool MyHashTable::contains(const string& key) const {
    for (Node* cur = buckets[hash(key)]; cur; cur = cur->next)
        if (cur->key == key) return true;
    return false;
}

bool MyHashTable::remove(const string& key) {
    int idx = hash(key);
    Node* prev = nullptr;
    for (Node* cur = buckets[idx]; cur; prev = cur, cur = cur->next) {
        if (cur->key == key) {
            if (prev) prev->next = cur->next; else buckets[idx] = cur->next;
            delete cur;
            size--;
            return true;
        }
    }
    return false;
}

int MyHashTable::getCapacity() const { return capacity; }

vector<string> MyHashTable::keys() const {
    vector<string> res;
    for (int i = 0; i < capacity; ++i)
        for (Node* cur = buckets[i]; cur; cur = cur->next) res.push_back(cur->key);
    return res;
}

int MyHashTable::getSize() const { return size; }

void MyHashTable::clear() {
    for (int i = 0; i < capacity; ++i) {
        Node* cur = buckets[i];
        while (cur) {
            Node* next = cur->next;
            delete cur;
            cur = next;
        }
        buckets[i] = nullptr;
    }
    size = 0;
}

string MyHashTable::toString() const {
    string s = "{";
    bool first = true;
    for (int i = 0; i < capacity; ++i)
        for (Node* cur = buckets[i]; cur; cur = cur->next) {
            s += (first ? "" : ", ") + cur->key + ": " + cur->value;
            first = false;
        }
    return s + "}";
}

string MyHashTable::typeName() const { return "MyHashTable"; }

// В файл пишем пары подряд: ключ1, значение1, ключ2, значение2, ...
static vector<string> pairs(const MyHashTable& t) {
    vector<string> res;
    for (auto& k : t.keys()) {
        res.push_back(k);
        res.push_back(t.get(k));
    }
    return res;
}

void MyHashTable::saveBinary(const string& filename) const { Serializer::saveStringsBinary(filename, typeName(), pairs(*this)); }

void MyHashTable::loadBinary(const string& filename) {
    auto items = Serializer::loadStringsBinary(filename, typeName());
    clear();
    for (size_t i = 0; i + 1 < items.size(); i += 2) put(items[i], items[i + 1]);
}

void MyHashTable::saveText(const string& filename) const { Serializer::saveStringsText(filename, typeName(), pairs(*this)); }

void MyHashTable::loadText(const string& filename) {
    auto items = Serializer::loadStringsText(filename, typeName());
    clear();
    for (size_t i = 0; i + 1 < items.size(); i += 2) put(items[i], items[i + 1]);
}
