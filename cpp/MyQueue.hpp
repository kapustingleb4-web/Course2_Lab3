#ifndef MYQUEUE_HPP
#define MYQUEUE_HPP
#include "MyArray.hpp"

// Очередь (FIFO) - наследник MyArray: добавление в конец, извлечение из начала.
class MyQueue : public MyArray {
public:
    void push(const std::string& val);  // O(1) амортизированно
    std::string pop();                  // O(n) - сдвиг массива
    std::string front() const;          // O(1)
    std::string toString() const override;
    std::string typeName() const override;
};
#endif
