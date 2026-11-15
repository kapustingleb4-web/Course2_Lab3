#ifndef AVLTREE_HPP
#define AVLTREE_HPP
#include "Container.hpp"
#include <string>
#include <vector>

using namespace std;

enum class Traversal { InOrder, PreOrder, PostOrder, BFS };

// АВЛ-дерево (вариант 2 из ЛР1): |баланс| <= 1 у каждого узла.
class AVLTree : public Container {
private:
    struct Node {
        int key;
        Node* left;
        Node* right;
        int height;
        Node(int k) : key(k), left(nullptr), right(nullptr), height(1) {}
    };
    Node* root;
    int size;

    static int height(Node* n);
    static int getBalance(Node* n);
    static void updateHeight(Node* n);
    static Node* rightRotate(Node* y);
    static Node* leftRotate(Node* x);
    static Node* balance(Node* n);
    Node* insert(Node* n, int key, bool& inserted);
    static Node* insertPlain(Node* n, int key);  // без балансировки - для загрузки из файла
    Node* remove(Node* n, int key, bool& removed);
    static Node* removeMin(Node* n, Node*& minNode);
    static Node* copy(Node* n);
    static void clear(Node* n);
    static void collect(Node* n, Traversal order, vector<int>& out);
    static int checkBalanced(Node* n);

public:
    AVLTree();
    AVLTree(const AVLTree& other);
    AVLTree& operator=(const AVLTree& other);
    ~AVLTree() override;

    bool insert(int key);      // O(log n), false если уже есть
    bool remove(int key);      // O(log n), false если нет
    bool find(int key) const;  // O(log n)
    int getHeight() const;
    bool isBalanced() const;
    vector<int> traverse(Traversal order) const;

    int getSize() const override;
    void clear() override;
    string toString() const override;
    string typeName() const override;
    // сохраняем прямой обход (preorder): при загрузке форма дерева восстанавливается
    void saveBinary(const string& filename) const override;
    void loadBinary(const string& filename) override;
    void saveText(const string& filename) const override;
    void loadText(const string& filename) override;
};
#endif
