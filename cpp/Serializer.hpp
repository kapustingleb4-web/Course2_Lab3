#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP
#include <string>
#include <vector>

using namespace std;

// Сохранение списка значений в файл.
// Бинарный формат: "LAB3" + имя типа + количество + элементы (строка = длина + байты).
// Текстовый формат: JSON {"type": ..., "items": [...]} (json.hpp из ЛР1).
namespace Serializer {
void saveStringsBinary(const string& filename, const string& type, const vector<string>& items);
vector<string> loadStringsBinary(const string& filename, const string& type);
void saveIntsBinary(const string& filename, const string& type, const vector<int>& items);
vector<int> loadIntsBinary(const string& filename, const string& type);

void saveStringsText(const string& filename, const string& type, const vector<string>& items);
vector<string> loadStringsText(const string& filename, const string& type);
void saveIntsText(const string& filename, const string& type, const vector<int>& items);
vector<int> loadIntsText(const string& filename, const string& type);
}
#endif
