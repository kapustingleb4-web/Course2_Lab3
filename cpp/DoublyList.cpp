#include "DoublyList.hpp"
#include "Serializer.hpp"
#include <stdexcept>

DoublyList::DoublyList() : head(nullptr), tail(nullptr), size(0) {}

DoublyList::DoublyList(const DoublyList& other) : head(nullptr), tail(nullptr), size(0) {
    for (Node* cur = other.head; cur; cur = cur->next) push_back(cur->data);
}

DoublyList& DoublyList::operator=(const DoublyList& other) {
    if (this == &other) return *this;
    clear();
    for (Node* cur = other.head; cur; cur = cur->next) push_back(cur->data);
    return *this;
}

DoublyList::~DoublyList() { clear(); }

DoublyList::Node* DoublyList::findNode(const std::string& val) const {
    for (Node* cur = head; cur; cur = cur->next)
        if (cur->data == val) return cur;
    return nullptr;
}

void DoublyList::unlink(Node* n) {
    if (n->prev) n->prev->next = n->next; else head = n->next;
    if (n->next) n->next->prev = n->prev; else tail = n->prev;
    delete n;
    size--;
}

void DoublyList::push_front(const std::string& val) {
    Node* n = new Node(val);
    n->next = head;
    if (head) head->prev = n; else tail = n;
    head = n;
    size++;
}

void DoublyList::push_back(const std::string& val) {
    Node* n = new Node(val);
    n->prev = tail;
    if (tail) tail->next = n; else head = n;
    tail = n;
    size++;
}

bool DoublyList::insert_before(const std::string& target, const std::string& val) {
    Node* t = findNode(target);
    if (!t) return false;
    if (t == head) { push_front(val); return true; }
    Node* n = new Node(val);
    n->prev = t->prev;
    n->next = t;
    t->prev->next = n;
    t->prev = n;
    size++;
    return true;
}

bool DoublyList::insert_after(const std::string& target, const std::string& val) {
    Node* t = findNode(target);
    if (!t) return false;
    if (t == tail) { push_back(val); return true; }
    Node* n = new Node(val);
    n->prev = t;
    n->next = t->next;
    t->next->prev = n;
    t->next = n;
    size++;
    return true;
}

void DoublyList::pop_front() {
    if (!head) throw std::runtime_error("List is empty");
    unlink(head);
}

void DoublyList::pop_back() {
    if (!tail) throw std::runtime_error("List is empty");
    unlink(tail);
}

bool DoublyList::remove_by_value(const std::string& val) {
    Node* t = findNode(val);
    if (!t) return false;
    unlink(t);
    return true;
}

bool DoublyList::remove_before(const std::string& target) {
    Node* t = findNode(target);
    if (!t || !t->prev) return false;
    unlink(t->prev);
    return true;
}

bool DoublyList::remove_after(const std::string& target) {
    Node* t = findNode(target);
    if (!t || !t->next) return false;
    unlink(t->next);
    return true;
}

int DoublyList::find(const std::string& val) const {
    int i = 0;
    for (Node* cur = head; cur; cur = cur->next, ++i)
        if (cur->data == val) return i;
    return -1;
}

std::string DoublyList::get(int index) const {
    if (index < 0 || index >= size) throw std::out_of_range("Index out of range");
    Node* cur;
    if (index < size / 2) {
        cur = head;
        for (int i = 0; i < index; ++i) cur = cur->next;
    } else {
        cur = tail;
        for (int i = size - 1; i > index; --i) cur = cur->prev;
    }
    return cur->data;
}

std::vector<std::string> DoublyList::getData() const {
    std::vector<std::string> res;
    for (Node* cur = head; cur; cur = cur->next) res.push_back(cur->data);
    return res;
}

std::string DoublyList::toReverseString() const {
    std::string s = "[";
    for (Node* cur = tail; cur; cur = cur->prev) s += cur->data + (cur->prev ? " <-> " : "");
    return s + "]";
}

int DoublyList::getSize() const { return size; }

void DoublyList::clear() {
    while (head) {
        Node* next = head->next;
        delete head;
        head = next;
    }
    tail = nullptr;
    size = 0;
}

std::string DoublyList::toString() const {
    std::string s = "[";
    for (Node* cur = head; cur; cur = cur->next) s += cur->data + (cur->next ? " <-> " : "");
    return s + "]";
}

std::string DoublyList::typeName() const { return "DoublyList"; }

void DoublyList::saveBinary(const std::string& filename) const { Serializer::saveStringsBinary(filename, typeName(), getData()); }

void DoublyList::loadBinary(const std::string& filename) {
    auto items = Serializer::loadStringsBinary(filename, typeName());
    clear();
    for (auto& s : items) push_back(s);
}

void DoublyList::saveText(const std::string& filename) const { Serializer::saveStringsText(filename, typeName(), getData()); }

void DoublyList::loadText(const std::string& filename) {
    auto items = Serializer::loadStringsText(filename, typeName());
    clear();
    for (auto& s : items) push_back(s);
}
