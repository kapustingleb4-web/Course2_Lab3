#include "AVLTree.hpp"
#include "Serializer.hpp"
#include <algorithm>

using namespace std;

AVLTree::AVLTree() : root(nullptr), size(0) {}

AVLTree::AVLTree(const AVLTree& other) : root(copy(other.root)), size(other.size) {}

AVLTree& AVLTree::operator=(const AVLTree& other) {
    if (this == &other) return *this;
    clear();
    root = copy(other.root);
    size = other.size;
    return *this;
}

AVLTree::~AVLTree() { clear(); }

AVLTree::Node* AVLTree::copy(Node* n) {
    if (!n) return nullptr;
    Node* c = new Node(n->key);
    c->height = n->height;
    c->left = copy(n->left);
    c->right = copy(n->right);
    return c;
}

void AVLTree::clear(Node* n) {
    if (!n) return;
    clear(n->left);
    clear(n->right);
    delete n;
}

int AVLTree::height(Node* n) { return n ? n->height : 0; }

int AVLTree::getBalance(Node* n) { return height(n->left) - height(n->right); }

void AVLTree::updateHeight(Node* n) { n->height = 1 + max(height(n->left), height(n->right)); }

AVLTree::Node* AVLTree::rightRotate(Node* y) {
    Node* x = y->left;
    y->left = x->right;
    x->right = y;
    updateHeight(y);
    updateHeight(x);
    return x;
}

AVLTree::Node* AVLTree::leftRotate(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    y->left = x;
    updateHeight(x);
    updateHeight(y);
    return y;
}

AVLTree::Node* AVLTree::balance(Node* n) {
    updateHeight(n);
    int bf = getBalance(n);
    if (bf > 1) {
        if (getBalance(n->left) < 0) n->left = leftRotate(n->left);     // LR
        return rightRotate(n);                                            // LL
    }
    if (bf < -1) {
        if (getBalance(n->right) > 0) n->right = rightRotate(n->right);  // RL
        return leftRotate(n);                                             // RR
    }
    return n;
}

AVLTree::Node* AVLTree::insert(Node* n, int key, bool& inserted) {
    if (!n) { inserted = true; return new Node(key); }
    if (key < n->key) n->left = insert(n->left, key, inserted);
    else if (key > n->key) n->right = insert(n->right, key, inserted);
    else return n;
    return balance(n);
}

// Ключи из файла идут в прямом обходе исходного (уже сбалансированного) дерева,
// поэтому обычная вставка BST без поворотов восстанавливает ту же форму.
AVLTree::Node* AVLTree::insertPlain(Node* n, int key) {
    if (!n) return new Node(key);
    if (key < n->key) n->left = insertPlain(n->left, key);
    else if (key > n->key) n->right = insertPlain(n->right, key);
    updateHeight(n);
    return n;
}

AVLTree::Node* AVLTree::removeMin(Node* n, Node*& minNode) {
    if (!n->left) { minNode = n; return n->right; }
    n->left = removeMin(n->left, minNode);
    return balance(n);
}

AVLTree::Node* AVLTree::remove(Node* n, int key, bool& removed) {
    if (!n) return nullptr;
    if (key < n->key) n->left = remove(n->left, key, removed);
    else if (key > n->key) n->right = remove(n->right, key, removed);
    else {
        removed = true;
        Node* l = n->left;
        Node* r = n->right;
        delete n;
        if (!r) return l;
        Node* m = nullptr;  // два ребёнка: ставим на место минимум правого поддерева
        Node* rest = removeMin(r, m);
        m->right = rest;
        m->left = l;
        return balance(m);
    }
    return balance(n);
}

bool AVLTree::insert(int key) {
    bool inserted = false;
    root = insert(root, key, inserted);
    if (inserted) size++;
    return inserted;
}

bool AVLTree::remove(int key) {
    bool removed = false;
    root = remove(root, key, removed);
    if (removed) size--;
    return removed;
}

bool AVLTree::find(int key) const {
    Node* cur = root;
    while (cur) {
        if (key == cur->key) return true;
        cur = key < cur->key ? cur->left : cur->right;
    }
    return false;
}

int AVLTree::getHeight() const { return height(root); }

int AVLTree::checkBalanced(Node* n) {
    if (!n) return 0;
    int l = checkBalanced(n->left), r = checkBalanced(n->right);
    if (l < 0 || r < 0 || l - r > 1 || r - l > 1) return -1;
    return 1 + max(l, r);
}

bool AVLTree::isBalanced() const { return checkBalanced(root) >= 0; }

void AVLTree::collect(Node* n, Traversal order, vector<int>& out) {
    if (!n) return;
    if (order == Traversal::PreOrder) out.push_back(n->key);
    collect(n->left, order, out);
    if (order == Traversal::InOrder) out.push_back(n->key);
    collect(n->right, order, out);
    if (order == Traversal::PostOrder) out.push_back(n->key);
}

vector<int> AVLTree::traverse(Traversal order) const {
    vector<int> out;
    if (order != Traversal::BFS) {
        collect(root, order, out);
        return out;
    }
    vector<Node*> level;  // обход в ширину по уровням
    if (root) level.push_back(root);
    while (!level.empty()) {
        vector<Node*> next;
        for (Node* n : level) {
            out.push_back(n->key);
            if (n->left) next.push_back(n->left);
            if (n->right) next.push_back(n->right);
        }
        level = next;
    }
    return out;
}

int AVLTree::getSize() const { return size; }

void AVLTree::clear() {
    clear(root);
    root = nullptr;
    size = 0;
}

string AVLTree::toString() const {
    string s = "[";
    auto v = traverse(Traversal::InOrder);
    for (size_t i = 0; i < v.size(); ++i) s += (i ? ", " : "") + to_string(v[i]);
    return s + "]";
}

string AVLTree::typeName() const { return "AVLTree"; }

void AVLTree::saveBinary(const string& filename) const {
    Serializer::saveIntsBinary(filename, typeName(), traverse(Traversal::PreOrder));
}

void AVLTree::loadBinary(const string& filename) {
    auto items = Serializer::loadIntsBinary(filename, typeName());
    clear();
    for (int k : items) {
        if (!find(k)) size++;
        root = insertPlain(root, k);
    }
}

void AVLTree::saveText(const string& filename) const {
    Serializer::saveIntsText(filename, typeName(), traverse(Traversal::PreOrder));
}

void AVLTree::loadText(const string& filename) {
    auto items = Serializer::loadIntsText(filename, typeName());
    clear();
    for (int k : items) {
        if (!find(k)) size++;
        root = insertPlain(root, k);
    }
}
