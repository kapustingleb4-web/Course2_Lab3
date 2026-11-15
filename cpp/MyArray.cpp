#include "MyArray.hpp"
#include "Serializer.hpp"
#include <stdexcept>

MyArray::MyArray() : data(nullptr), size(0), capacity(0) {}

MyArray::MyArray(const MyArray& other) : data(nullptr), size(0), capacity(0) {
    for (int i = 0; i < other.size; ++i) push_back(other.data[i]);
}

MyArray& MyArray::operator=(const MyArray& other) {
    if (this == &other) return *this;
    clear();
    for (int i = 0; i < other.size; ++i) push_back(other.data[i]);
    return *this;
}

MyArray::~MyArray() { delete[] data; }

void MyArray::resize(int newCapacity) {
    std::string* newData = new std::string[newCapacity];
    for (int i = 0; i < size; ++i) newData[i] = data[i];
    delete[] data;
    data = newData;
    capacity = newCapacity;
}

void MyArray::push_back(const std::string& val) {
    if (size == capacity) resize(capacity == 0 ? 2 : capacity * 2);
    data[size++] = val;
}

void MyArray::insert_at(int index, const std::string& val) {
    if (index < 0 || index > size) throw std::out_of_range("Index out of range");
    if (size == capacity) resize(capacity == 0 ? 2 : capacity * 2);
    for (int i = size; i > index; --i) data[i] = data[i - 1];
    data[index] = val;
    size++;
}

void MyArray::remove_at(int index) {
    if (index < 0 || index >= size) throw std::out_of_range("Index out of range");
    for (int i = index; i < size - 1; ++i) data[i] = data[i + 1];
    size--;
}

void MyArray::update_at(int index, const std::string& val) {
    if (index < 0 || index >= size) throw std::out_of_range("Index out of range");
    data[index] = val;
}

std::string MyArray::get(int index) const {
    if (index < 0 || index >= size) throw std::out_of_range("Index out of range");
    return data[index];
}

int MyArray::find(const std::string& val) const {
    for (int i = 0; i < size; ++i)
        if (data[i] == val) return i;
    return -1;
}

int MyArray::length() const { return size; }

std::vector<std::string> MyArray::getData() const { return std::vector<std::string>(data, data + size); }

int MyArray::getSize() const { return size; }

void MyArray::clear() {
    delete[] data;
    data = nullptr;
    size = capacity = 0;
}

std::string MyArray::toString() const {
    std::string s = "[";
    for (int i = 0; i < size; ++i) s += (i ? ", " : "") + data[i];
    return s + "]";
}

std::string MyArray::typeName() const { return "MyArray"; }

void MyArray::saveBinary(const std::string& filename) const { Serializer::saveStringsBinary(filename, typeName(), getData()); }

void MyArray::loadBinary(const std::string& filename) {
    auto items = Serializer::loadStringsBinary(filename, typeName());
    clear();
    for (auto& s : items) push_back(s);
}

void MyArray::saveText(const std::string& filename) const { Serializer::saveStringsText(filename, typeName(), getData()); }

void MyArray::loadText(const std::string& filename) {
    auto items = Serializer::loadStringsText(filename, typeName());
    clear();
    for (auto& s : items) push_back(s);
}
