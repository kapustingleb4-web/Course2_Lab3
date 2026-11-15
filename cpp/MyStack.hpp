#ifndef MYSTACK_HPP
#define MYSTACK_HPP
#include "MyArray.hpp"

using namespace std;

// Стек (LIFO) - наследник MyArray, вершина = последний элемент массива.
class MyStack : public MyArray {
public:
    void push(const string& val);  // O(1) амортизированно
    string pop();                  // O(1)
    string peek() const;           // O(1)
    string toString() const override;
    string typeName() const override;
};
#endif
