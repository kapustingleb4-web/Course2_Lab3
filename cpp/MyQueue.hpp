#ifndef MYQUEUE_HPP
#define MYQUEUE_HPP
#include "MyArray.hpp"

using namespace std;

// Очередь (FIFO) - наследник MyArray: добавление в конец, извлечение из начала.
class MyQueue : public MyArray {
public:
    void push(const string& val);  // O(1) амортизированно
    string pop();                  // O(n) - сдвиг массива
    string front() const;          // O(1)
    string toString() const override;
    string typeName() const override;
};
#endif
