// Модульные тесты на Boost.Test (header-only вариант).
// Нужна библиотека: sudo apt install libboost-test-dev   (сборка: make -f Makefile.txt test_boost)
#define BOOST_TEST_MODULE Lab3Tests
#include <boost/test/included/unit_test.hpp>

#include "AVLTree.hpp"
#include "ForwardList.hpp"
#include "MyArray.hpp"
#include "MyHashTable.hpp"
#include "MyStack.hpp"

using namespace std;

BOOST_AUTO_TEST_CASE(array_basic) {
    MyArray a;
    for (int i = 0; i < 5; ++i) a.push_back(to_string(i));
    a.remove_at(0);
    BOOST_CHECK_EQUAL(a.length(), 4);
    BOOST_CHECK_EQUAL(a.get(0), "1");
    BOOST_CHECK_THROW(a.get(10), out_of_range);
}

BOOST_AUTO_TEST_CASE(list_and_stack) {
    ForwardList l;
    l.push_back("a");
    l.push_back("b");
    BOOST_CHECK(l.remove_before("b"));
    BOOST_CHECK_EQUAL(l.toString(), "[b]");
    MyStack s;
    s.push("x");
    BOOST_CHECK_EQUAL(s.peek(), "x");
}

BOOST_AUTO_TEST_CASE(hash_and_tree) {
    MyHashTable h;
    h.put("key", "value");
    BOOST_CHECK(h.contains("key"));
    AVLTree t;
    for (int v : {3, 1, 2}) t.insert(v);
    BOOST_CHECK(t.isBalanced());
    BOOST_CHECK(t.find(2));
}
