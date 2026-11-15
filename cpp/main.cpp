// ЛР3 (C++): демонстрация классов, полиморфизма и сериализации.
#include "AVLTree.hpp"
#include "DoublyList.hpp"
#include "ForwardList.hpp"
#include "MyArray.hpp"
#include "MyHashTable.hpp"
#include "MyQueue.hpp"
#include "MyStack.hpp"
#include <iostream>
#include <vector>

int main() {
    MyArray arr;
    for (auto s : {"10", "20", "30"}) arr.push_back(s);
    arr.insert_at(1, "15");

    ForwardList fl;
    fl.push_back("b");
    fl.push_front("a");
    fl.insert_after("b", "c");

    DoublyList dl;
    for (auto s : {"1", "2", "3"}) dl.push_back(s);

    MyStack st;
    st.push("x");
    st.push("y");

    MyQueue q;
    q.push("first");
    q.push("second");

    MyHashTable ht;
    ht.put("one", "1");
    ht.put("two", "2");

    AVLTree tree;
    for (int v : {7, 3, 2, 1, 9, 5, 4, 6, 8}) tree.insert(v);

    // Полиморфизм: работаем со всеми структурами через указатель на базовый класс
    std::vector<Container*> all = {&arr, &fl, &dl, &st, &q, &ht, &tree};
    for (Container* c : all)
        std::cout << c->typeName() << " (size " << c->getSize() << "): " << c->toString() << std::endl;

    std::cout << "Дерево BFS: ";
    for (int v : tree.traverse(Traversal::BFS)) std::cout << v << " ";
    std::cout << "| высота " << tree.getHeight() << ", сбалансировано: " << (tree.isBalanced() ? "да" : "нет") << std::endl;

    // Сериализация: бинарный и текстовый формат
    tree.saveBinary("tree.bin");
    ht.saveText("table.json");
    AVLTree tree2;
    MyHashTable ht2;
    tree2.loadBinary("tree.bin");
    ht2.loadText("table.json");
    std::cout << "Загружено из tree.bin (BFS): ";
    for (int v : tree2.traverse(Traversal::BFS)) std::cout << v << " ";
    std::cout << std::endl << "Загружено из table.json: " << ht2.toString() << std::endl;
    return 0;
}
