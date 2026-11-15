#ifndef MYSTACK_HPP
#define MYSTACK_HPP
#include "MyArray.hpp"

// Стек (LIFO) - наследник MyArray, вершина = последний элемент массива.
class MyStack : public MyArray {
public:
    void push(const std::string& val);  // O(1) амортизированно
    std::string pop();                  // O(1)
    std::string peek() const;           // O(1)
    std::string toString() const override;
    std::string typeName() const override;
};
#endif
