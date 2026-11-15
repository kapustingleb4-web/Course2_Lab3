#include "ForwardList.hpp"
#include "Serializer.hpp"
#include <stdexcept>

ForwardList::ForwardList() : head(nullptr), tail(nullptr), size(0) {}

ForwardList::ForwardList(const ForwardList& other) : head(nullptr), tail(nullptr), size(0) {
    for (Node* cur = other.head; cur; cur = cur->next) push_back(cur->data);
}

ForwardList& ForwardList::operator=(const ForwardList& other) {
    if (this == &other) return *this;
    clear();
    for (Node* cur = other.head; cur; cur = cur->next) push_back(cur->data);
    return *this;
}

ForwardList::~ForwardList() { clear(); }

ForwardList::Node* ForwardList::findNode(const std::string& val) const {
    for (Node* cur = head; cur; cur = cur->next)
        if (cur->data == val) return cur;
    return nullptr;
}

void ForwardList::push_front(const std::string& val) {
    head = new Node(val, head);
    if (!tail) tail = head;
    size++;
}

void ForwardList::push_back(const std::string& val) {
    Node* n = new Node(val);
    if (tail) tail->next = n; else head = n;
    tail = n;
    size++;
}

bool ForwardList::insert_before(const std::string& target, const std::string& val) {
    if (!head) return false;
    if (head->data == target) { push_front(val); return true; }
    Node* prev = head;
    while (prev->next && prev->next->data != target) prev = prev->next;
    if (!prev->next) return false;
    prev->next = new Node(val, prev->next);
    size++;
    return true;
}

bool ForwardList::insert_after(const std::string& target, const std::string& val) {
    Node* cur = findNode(target);
    if (!cur) return false;
    cur->next = new Node(val, cur->next);
    if (cur == tail) tail = cur->next;
    size++;
    return true;
}

void ForwardList::pop_front() {
    if (!head) throw std::runtime_error("List is empty");
    Node* old = head;
    head = head->next;
    if (!head) tail = nullptr;
    delete old;
    size--;
}

void ForwardList::pop_back() {
    if (!head) throw std::runtime_error("List is empty");
    if (head == tail) { pop_front(); return; }
    Node* prev = head;
    while (prev->next != tail) prev = prev->next;  // ищем предпоследний - O(n)
    delete tail;
    prev->next = nullptr;
    tail = prev;
    size--;
}

bool ForwardList::remove_by_value(const std::string& val) {
    if (!head) return false;
    if (head->data == val) { pop_front(); return true; }
    Node* prev = head;
    while (prev->next && prev->next->data != val) prev = prev->next;
    if (!prev->next) return false;
    Node* del = prev->next;
    prev->next = del->next;
    if (del == tail) tail = prev;
    delete del;
    size--;
    return true;
}

bool ForwardList::remove_before(const std::string& target) {
    if (!head || head->data == target) return false;
    if (head->next && head->next->data == target) { pop_front(); return true; }
    Node* pp = head;  // узел перед удаляемым
    while (pp->next && pp->next->next && pp->next->next->data != target) pp = pp->next;
    if (!pp->next || !pp->next->next) return false;
    Node* del = pp->next;
    pp->next = del->next;
    delete del;
    size--;
    return true;
}

bool ForwardList::remove_after(const std::string& target) {
    Node* cur = findNode(target);
    if (!cur || !cur->next) return false;
    Node* del = cur->next;
    cur->next = del->next;
    if (del == tail) tail = cur;
    delete del;
    size--;
    return true;
}

int ForwardList::find(const std::string& val) const {
    int i = 0;
    for (Node* cur = head; cur; cur = cur->next, ++i)
        if (cur->data == val) return i;
    return -1;
}

std::string ForwardList::get(int index) const {
    if (index < 0 || index >= size) throw std::out_of_range("Index out of range");
    Node* cur = head;
    while (index--) cur = cur->next;
    return cur->data;
}

std::vector<std::string> ForwardList::getData() const {
    std::vector<std::string> res;
    for (Node* cur = head; cur; cur = cur->next) res.push_back(cur->data);
    return res;
}

static std::string reverseRec(const std::vector<std::string>& v, int i) {
    if (i < 0) return "";
    return v[i] + (i ? " <- " : "") + reverseRec(v, i - 1);
}

std::string ForwardList::toReverseString() const {
    auto v = getData();
    return "[" + reverseRec(v, (int)v.size() - 1) + "]";
}

int ForwardList::getSize() const { return size; }

void ForwardList::clear() {
    while (head) {
        Node* next = head->next;
        delete head;
        head = next;
    }
    tail = nullptr;
    size = 0;
}

std::string ForwardList::toString() const {
    std::string s = "[";
    for (Node* cur = head; cur; cur = cur->next) s += cur->data + (cur->next ? " -> " : "");
    return s + "]";
}

std::string ForwardList::typeName() const { return "ForwardList"; }

void ForwardList::saveBinary(const std::string& filename) const { Serializer::saveStringsBinary(filename, typeName(), getData()); }

void ForwardList::loadBinary(const std::string& filename) {
    auto items = Serializer::loadStringsBinary(filename, typeName());
    clear();
    for (auto& s : items) push_back(s);
}

void ForwardList::saveText(const std::string& filename) const { Serializer::saveStringsText(filename, typeName(), getData()); }

void ForwardList::loadText(const std::string& filename) {
    auto items = Serializer::loadStringsText(filename, typeName());
    clear();
    for (auto& s : items) push_back(s);
}
