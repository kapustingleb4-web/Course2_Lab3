#ifndef CONTAINER_HPP
#define CONTAINER_HPP
#include <string>

using namespace std;

// Абстрактный базовый класс для всех структур данных.
// Чисто виртуальные методы (= 0) нужно переопределить в наследниках.
class Container {
public:
    virtual ~Container() = default;  // виртуальный деструктор: удаление через указатель на базовый класс

    virtual int getSize() const = 0;
    virtual bool isEmpty() const { return getSize() == 0; }
    virtual void clear() = 0;
    virtual string toString() const = 0;
    virtual string typeName() const = 0;

    // Сериализация: бинарный формат и текстовый (JSON)
    virtual void saveBinary(const string& filename) const = 0;
    virtual void loadBinary(const string& filename) = 0;
    virtual void saveText(const string& filename) const = 0;
    virtual void loadText(const string& filename) = 0;
};
#endif
