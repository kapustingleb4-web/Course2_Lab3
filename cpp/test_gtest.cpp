// Модульные тесты на Google Test.
// Нужна библиотека: sudo apt install libgtest-dev   (сборка: make -f Makefile.txt test_gtest)
#include <gtest/gtest.h>

#include "AVLTree.hpp"
#include "DoublyList.hpp"
#include "ForwardList.hpp"
#include "MyArray.hpp"
#include "MyHashTable.hpp"
#include "MyQueue.hpp"
#include "MyStack.hpp"

using namespace std;

TEST(MyArrayTest, PushInsertGet) {
    MyArray a;
    a.push_back("a");
    a.push_back("c");
    a.insert_at(1, "b");
    EXPECT_EQ(a.toString(), "[a, b, c]");
    EXPECT_EQ(a.get(1), "b");
    EXPECT_THROW(a.get(5), out_of_range);
}

TEST(ListTest, ForwardAndDoubly) {
    ForwardList f;
    f.push_back("1");
    f.push_front("0");
    EXPECT_TRUE(f.insert_after("1", "2"));
    EXPECT_EQ(f.toString(), "[0 -> 1 -> 2]");
    DoublyList d;
    d.push_back("x");
    d.push_back("y");
    d.pop_back();
    EXPECT_EQ(d.toReverseString(), "[x]");
}

TEST(StackQueueTest, LifoFifo) {
    MyStack s;
    s.push("1");
    s.push("2");
    EXPECT_EQ(s.pop(), "2");
    MyQueue q;
    q.push("1");
    q.push("2");
    EXPECT_EQ(q.pop(), "1");
    EXPECT_THROW(MyStack().pop(), runtime_error);
}

TEST(HashTableTest, PutGetRemove) {
    MyHashTable t;
    t.put("a", "1");
    EXPECT_EQ(t.get("a"), "1");
    EXPECT_TRUE(t.remove("a"));
    EXPECT_FALSE(t.contains("a"));
}

TEST(AVLTreeTest, BalancedAfterInsertRemove) {
    AVLTree t;
    for (int i = 1; i <= 100; ++i) t.insert(i);
    EXPECT_TRUE(t.isBalanced());
    EXPECT_LE(t.getHeight(), 8);
    for (int i = 1; i <= 50; ++i) t.remove(i);
    EXPECT_TRUE(t.isBalanced());
    EXPECT_EQ(t.getSize(), 50);
}
