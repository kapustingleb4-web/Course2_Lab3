#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP
#include <string>
#include <vector>

// Сохранение списка значений в файл.
// Бинарный формат: "LAB3" + имя типа + количество + элементы (строка = длина + байты).
// Текстовый формат: JSON {"type": ..., "items": [...]} (json.hpp из ЛР1).
namespace Serializer {
void saveStringsBinary(const std::string& filename, const std::string& type, const std::vector<std::string>& items);
std::vector<std::string> loadStringsBinary(const std::string& filename, const std::string& type);
void saveIntsBinary(const std::string& filename, const std::string& type, const std::vector<int>& items);
std::vector<int> loadIntsBinary(const std::string& filename, const std::string& type);

void saveStringsText(const std::string& filename, const std::string& type, const std::vector<std::string>& items);
std::vector<std::string> loadStringsText(const std::string& filename, const std::string& type);
void saveIntsText(const std::string& filename, const std::string& type, const std::vector<int>& items);
std::vector<int> loadIntsText(const std::string& filename, const std::string& type);
}
#endif
