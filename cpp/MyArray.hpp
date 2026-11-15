#ifndef MYARRAY_HPP
#define MYARRAY_HPP
#include "Container.hpp"
#include <string>
#include <vector>

// Динамический массив строк. При заполнении ёмкость удваивается.
class MyArray : public Container {
protected:
    std::string* data;
    int size;
    int capacity;
    void resize(int newCapacity);

public:
    MyArray();
    MyArray(const MyArray& other);             // конструктор копирования (глубокая копия)
    MyArray& operator=(const MyArray& other);  // оператор присваивания
    ~MyArray() override;

    void push_back(const std::string& val);              // O(1) амортизированно
    void insert_at(int index, const std::string& val);   // O(n)
    void remove_at(int index);                           // O(n)
    void update_at(int index, const std::string& val);   // O(1)
    std::string get(int index) const;                    // O(1)
    int find(const std::string& val) const;              // O(n), -1 если нет
    int length() const;
    std::vector<std::string> getData() const;

    int getSize() const override;
    void clear() override;
    std::string toString() const override;
    std::string typeName() const override;
    void saveBinary(const std::string& filename) const override;
    void loadBinary(const std::string& filename) override;
    void saveText(const std::string& filename) const override;
    void loadText(const std::string& filename) override;
};
#endif
