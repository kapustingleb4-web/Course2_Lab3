#ifndef MYARRAY_HPP
#define MYARRAY_HPP
#include "Container.hpp"
#include <string>
#include <vector>

using namespace std;

// Динамический массив строк. При заполнении ёмкость удваивается.
class MyArray : public Container {
protected:
    string* data;
    int size;
    int capacity;
    void resize(int newCapacity);

public:
    MyArray();
    MyArray(const MyArray& other);             // конструктор копирования (глубокая копия)
    MyArray& operator=(const MyArray& other);  // оператор присваивания
    ~MyArray() override;

    void push_back(const string& val);              // O(1) амортизированно
    void insert_at(int index, const string& val);   // O(n)
    void remove_at(int index);                           // O(n)
    void update_at(int index, const string& val);   // O(1)
    string get(int index) const;                    // O(1)
    int find(const string& val) const;              // O(n), -1 если нет
    int length() const;
    vector<string> getData() const;

    int getSize() const override;
    void clear() override;
    string toString() const override;
    string typeName() const override;
    void saveBinary(const string& filename) const override;
    void loadBinary(const string& filename) override;
    void saveText(const string& filename) const override;
    void loadText(const string& filename) override;
};
#endif
