// Модульные тесты на Catch2 (основной набор). catch.hpp - однофайловая версия Catch2 v2.
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "AVLTree.hpp"
#include "DoublyList.hpp"
#include "ForwardList.hpp"
#include "MyArray.hpp"
#include "MyHashTable.hpp"
#include "MyQueue.hpp"
#include "MyStack.hpp"
#include <cstdio>
#include <fstream>

TEST_CASE("MyArray: добавление, вставка, получение, удаление", "[array]") {
    MyArray a;
    REQUIRE(a.isEmpty());
    for (int i = 0; i < 10; ++i) a.push_back(std::to_string(i));
    REQUIRE(a.length() == 10);
    a.insert_at(0, "start");
    a.insert_at(a.length(), "end");
    REQUIRE(a.get(0) == "start");
    REQUIRE(a.get(11) == "end");
    a.update_at(1, "zero");
    REQUIRE(a.get(1) == "zero");
    a.remove_at(0);
    REQUIRE(a.get(0) == "zero");
    REQUIRE(a.find("5") == 5);
    REQUIRE(a.find("nope") == -1);
    REQUIRE_THROWS_AS(a.get(100), std::out_of_range);
    REQUIRE_THROWS_AS(a.insert_at(-1, "x"), std::out_of_range);
    REQUIRE_THROWS_AS(a.remove_at(100), std::out_of_range);
    REQUIRE_THROWS_AS(a.update_at(100, "x"), std::out_of_range);
    REQUIRE(a.typeName() == "MyArray");
}

TEST_CASE("MyArray: копирование и toString", "[array]") {
    MyArray a;
    a.push_back("a");
    a.push_back("b");
    MyArray b(a);
    MyArray c;
    c = a;
    c = c;  // присваивание самому себе
    b.push_back("c");
    REQUIRE(a.toString() == "[a, b]");
    REQUIRE(b.toString() == "[a, b, c]");
    REQUIRE(c.toString() == "[a, b]");
    a.clear();
    REQUIRE(a.getSize() == 0);
}

TEST_CASE("ForwardList: 4 способа вставки и удаления", "[list]") {
    ForwardList l;
    l.push_back("b");
    l.push_front("a");
    REQUIRE(l.insert_after("b", "d"));
    REQUIRE(l.insert_before("d", "c"));
    REQUIRE(l.insert_before("a", "start"));
    REQUIRE_FALSE(l.insert_before("zzz", "x"));
    REQUIRE_FALSE(l.insert_after("zzz", "x"));
    REQUIRE(l.toString() == "[start -> a -> b -> c -> d]");
    REQUIRE(l.toReverseString() == "[d <- c <- b <- a <- start]");
    REQUIRE(l.find("c") == 3);
    REQUIRE(l.find("zzz") == -1);
    REQUIRE(l.get(1) == "a");
    REQUIRE_THROWS_AS(l.get(10), std::out_of_range);
    l.pop_front();
    l.pop_back();
    REQUIRE(l.toString() == "[a -> b -> c]");
    REQUIRE(l.remove_before("c"));   // удаляет b
    REQUIRE(l.remove_after("a"));    // удаляет c
    REQUIRE_FALSE(l.remove_after("a"));
    REQUIRE_FALSE(l.remove_before("a"));
    l.push_back("x");
    l.push_back("y");
    REQUIRE(l.remove_before("y"));   // удаляет x (не голову)
    REQUIRE(l.remove_by_value("y"));
    REQUIRE(l.remove_by_value("a"));
    REQUIRE_FALSE(l.remove_by_value("a"));
    REQUIRE(l.isEmpty());
    REQUIRE_THROWS(l.pop_front());
    REQUIRE_THROWS(l.pop_back());
    l.push_back("only");
    l.pop_back();
    REQUIRE(l.getSize() == 0);
    REQUIRE(l.typeName() == "ForwardList");
}

TEST_CASE("ForwardList: копирование и удаление хвоста по значению", "[list]") {
    ForwardList a;
    for (auto s : {"1", "2", "3"}) a.push_back(s);
    ForwardList b(a), c;
    c = a;
    c = c;
    REQUIRE(b.remove_by_value("3"));  // удаление хвоста по значению
    b.push_back("4");
    REQUIRE(b.toString() == "[1 -> 2 -> 4]");
    REQUIRE(c.toString() == "[1 -> 2 -> 3]");
    REQUIRE(a.remove_after("2"));
    a.push_back("5");
    REQUIRE(a.toString() == "[1 -> 2 -> 5]");
}

TEST_CASE("DoublyList: вставка, удаление, чтение в обе стороны", "[list]") {
    DoublyList l;
    l.push_back("2");
    l.push_front("1");
    l.push_back("4");
    REQUIRE(l.insert_before("4", "3"));
    REQUIRE(l.insert_after("4", "5"));
    REQUIRE(l.insert_before("1", "0"));
    REQUIRE(l.insert_after("2", "2.5"));
    REQUIRE_FALSE(l.insert_before("x", "y"));
    REQUIRE_FALSE(l.insert_after("x", "y"));
    REQUIRE(l.toString() == "[0 <-> 1 <-> 2 <-> 2.5 <-> 3 <-> 4 <-> 5]");
    REQUIRE(l.toReverseString() == "[5 <-> 4 <-> 3 <-> 2.5 <-> 2 <-> 1 <-> 0]");
    REQUIRE(l.get(1) == "1");
    REQUIRE(l.get(5) == "4");
    REQUIRE_THROWS_AS(l.get(-1), std::out_of_range);
    REQUIRE(l.find("3") == 4);
    REQUIRE(l.find("x") == -1);
    REQUIRE(l.remove_by_value("2.5"));
    REQUIRE_FALSE(l.remove_by_value("2.5"));
    REQUIRE(l.remove_before("2"));
    REQUIRE(l.remove_after("4"));
    REQUIRE_FALSE(l.remove_before("0"));
    REQUIRE_FALSE(l.remove_after("4"));
    l.pop_front();
    l.pop_back();
    REQUIRE(l.toString() == "[2 <-> 3]");
    DoublyList c(l), d;
    d = l;
    d = d;
    l.clear();
    REQUIRE(c.getSize() == 2);
    REQUIRE(d.toString() == "[2 <-> 3]");
    REQUIRE_THROWS(l.pop_front());
    REQUIRE_THROWS(l.pop_back());
    REQUIRE(l.typeName() == "DoublyList");
}

TEST_CASE("MyStack и MyQueue", "[stack][queue]") {
    MyStack s;
    REQUIRE_THROWS(s.pop());
    REQUIRE_THROWS(s.peek());
    s.push("1");
    s.push("2");
    s.push("3");
    REQUIRE(s.peek() == "3");
    REQUIRE(s.toString() == "top> [3, 2, 1]");
    REQUIRE(s.pop() == "3");
    REQUIRE(s.getSize() == 2);
    REQUIRE(s.typeName() == "MyStack");

    MyQueue q;
    REQUIRE_THROWS(q.pop());
    REQUIRE_THROWS(q.front());
    q.push("a");
    q.push("b");
    REQUIRE(q.front() == "a");
    REQUIRE(q.toString() == "front> [a, b] <back");
    REQUIRE(q.pop() == "a");
    REQUIRE(q.getSize() == 1);
    REQUIRE(q.typeName() == "MyQueue");
}

TEST_CASE("MyHashTable: put, get, remove, рехеширование", "[hash]") {
    MyHashTable t(2);
    for (int i = 0; i < 50; ++i) t.put("k" + std::to_string(i), std::to_string(i * i));
    REQUIRE(t.getSize() == 50);
    REQUIRE(t.getCapacity() > 50);
    REQUIRE(t.get("k7") == "49");
    t.put("k7", "seven");
    REQUIRE(t.get("k7") == "seven");
    REQUIRE(t.contains("k3"));
    REQUIRE_FALSE(t.contains("nope"));
    REQUIRE_THROWS_AS(t.get("nope"), std::out_of_range);
    REQUIRE(t.remove("k3"));
    REQUIRE_FALSE(t.remove("k3"));
    REQUIRE(t.keys().size() == 49);
    MyHashTable c(t), d;
    d = t;
    d = d;
    t.clear();
    REQUIRE(t.isEmpty());
    REQUIRE(c.getSize() == 49);
    REQUIRE(d.get("k10") == "100");
    MyHashTable one(0);
    one.put("a", "1");
    REQUIRE(one.toString() == "{a: 1}");
    REQUIRE(one.typeName() == "MyHashTable");
}

TEST_CASE("AVLTree: повороты, обходы, удаление", "[tree]") {
    AVLTree t;
    for (int v : {7, 3, 2, 1, 9, 5, 4, 6, 8}) REQUIRE(t.insert(v));
    REQUIRE_FALSE(t.insert(5));
    REQUIRE(t.getSize() == 9);
    REQUIRE(t.isBalanced());
    REQUIRE(t.traverse(Traversal::InOrder) == std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9});
    REQUIRE(t.traverse(Traversal::BFS) == std::vector<int>{3, 2, 7, 1, 5, 9, 4, 6, 8});
    REQUIRE(t.traverse(Traversal::PreOrder) == std::vector<int>{3, 2, 1, 7, 5, 4, 6, 9, 8});
    REQUIRE(t.traverse(Traversal::PostOrder) == std::vector<int>{1, 2, 4, 6, 5, 8, 9, 7, 3});
    REQUIRE(t.find(6));
    REQUIRE_FALSE(t.find(100));
    REQUIRE(t.remove(3));   // два ребёнка
    REQUIRE(t.remove(1));   // лист
    REQUIRE(t.remove(2));   // после этого нужен поворот
    REQUIRE_FALSE(t.remove(42));
    REQUIRE(t.isBalanced());
    REQUIRE(t.toString() == "[4, 5, 6, 7, 8, 9]");
    // правые повороты: вставка по убыванию
    AVLTree r;
    for (int v = 10; v > 0; --v) r.insert(v);
    REQUIRE(r.isBalanced());
    REQUIRE(r.getHeight() <= 4);
    // LR и RL случаи
    AVLTree lr;
    for (int v : {30, 10, 20}) lr.insert(v);
    REQUIRE(lr.traverse(Traversal::PreOrder) == std::vector<int>{20, 10, 30});
    AVLTree rl;
    for (int v : {10, 30, 20}) rl.insert(v);
    REQUIRE(rl.traverse(Traversal::PreOrder) == std::vector<int>{20, 10, 30});
    AVLTree c(t), d;
    d = t;
    d = d;
    t.clear();
    REQUIRE(t.isEmpty());
    REQUIRE(c.getSize() == 6);
    REQUIRE(d.toString() == "[4, 5, 6, 7, 8, 9]");
    REQUIRE(c.typeName() == "AVLTree");
}

TEST_CASE("Полиморфизм через базовый класс Container", "[oop]") {
    MyStack s;
    s.push("x");
    Container* c = &s;
    REQUIRE(c->typeName() == "MyStack");
    REQUIRE(c->toString() == "top> [x]");
    c->clear();
    REQUIRE(c->isEmpty());
}

TEST_CASE("Сериализация: бинарный и текстовый формат", "[serialize]") {
    MyArray a;
    for (auto s : {"hello world", "", "x"}) a.push_back(s);
    a.saveBinary("t_arr.bin");
    a.saveText("t_arr.json");
    MyArray a1, a2;
    a1.loadBinary("t_arr.bin");
    a2.loadText("t_arr.json");
    REQUIRE(a1.getData() == a.getData());
    REQUIRE(a2.getData() == a.getData());

    ForwardList fl;
    fl.push_back("1");
    fl.push_back("2");
    fl.saveBinary("t_fl.bin");
    fl.saveText("t_fl.json");
    ForwardList fl1, fl2;
    fl1.loadBinary("t_fl.bin");
    fl2.loadText("t_fl.json");
    REQUIRE(fl1.toString() == fl.toString());
    REQUIRE(fl2.toString() == fl.toString());

    DoublyList dl;
    dl.push_back("a");
    dl.saveBinary("t_dl.bin");
    dl.saveText("t_dl.json");
    DoublyList dl1, dl2;
    dl1.loadBinary("t_dl.bin");
    dl2.loadText("t_dl.json");
    REQUIRE(dl1.toString() == "[a]");
    REQUIRE(dl2.toString() == "[a]");

    MyStack s;
    s.push("bottom");
    s.push("top");
    s.saveBinary("t_st.bin");
    MyStack s2;
    s2.loadBinary("t_st.bin");
    REQUIRE(s2.pop() == "top");

    MyHashTable h;
    h.put("k", "v");
    h.put("a", "b");
    h.saveBinary("t_h.bin");
    h.saveText("t_h.json");
    MyHashTable h1, h2;
    h1.loadBinary("t_h.bin");
    h2.loadText("t_h.json");
    REQUIRE(h1.get("k") == "v");
    REQUIRE(h2.get("a") == "b");

    AVLTree t;
    for (int v : {7, 3, 2, 1, 9, 5, 4, 6, 8}) t.insert(v);
    t.saveBinary("t_tree.bin");
    t.saveText("t_tree.json");
    AVLTree t1, t2;
    t1.loadBinary("t_tree.bin");
    t2.loadText("t_tree.json");
    REQUIRE(t1.traverse(Traversal::BFS) == t.traverse(Traversal::BFS));  // форма та же
    REQUIRE(t2.traverse(Traversal::PreOrder) == t.traverse(Traversal::PreOrder));
    REQUIRE(t1.getSize() == 9);

    // ошибки: чужой тип, нет файла, испорченный файл
    REQUIRE_THROWS(t1.loadBinary("t_arr.bin"));
    REQUIRE_THROWS(t1.loadText("t_arr.json"));
    REQUIRE_THROWS(a1.loadBinary("no_such_file.bin"));
    REQUIRE_THROWS(a1.loadText("no_such_file.json"));
    REQUIRE_THROWS(a1.saveBinary("/no_such_dir/x.bin"));
    std::ofstream("t_bad.bin") << "XXXX";
    REQUIRE_THROWS(a1.loadBinary("t_bad.bin"));
    std::ofstream("t_bad.json") << "{not json";
    REQUIRE_THROWS(a1.loadText("t_bad.json"));
    std::ofstream("t_short.bin", std::ios::binary) << "LAB3";
    REQUIRE_THROWS(a1.loadBinary("t_short.bin"));

    for (auto f : {"t_arr.bin", "t_arr.json", "t_fl.bin", "t_fl.json", "t_dl.bin", "t_dl.json", "t_st.bin",
                   "t_h.bin", "t_h.json", "t_tree.bin", "t_tree.json", "t_bad.bin", "t_bad.json", "t_short.bin"})
        std::remove(f);
}
