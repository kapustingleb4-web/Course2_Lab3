#include "Serializer.hpp"
#include "json.hpp"
#include <cstdint>
#include <fstream>
#include <stdexcept>

using json = nlohmann::json;

namespace {
const char MAGIC[4] = {'L', 'A', 'B', '3'};

void writeU64(std::ofstream& f, uint64_t v) { f.write(reinterpret_cast<const char*>(&v), sizeof(v)); }

uint64_t readU64(std::ifstream& f) {
    uint64_t v = 0;
    if (!f.read(reinterpret_cast<char*>(&v), sizeof(v))) throw std::runtime_error("binary: unexpected end of file");
    return v;
}

void writeStr(std::ofstream& f, const std::string& s) {
    writeU64(f, s.size());
    f.write(s.data(), s.size());
}

std::string readStr(std::ifstream& f) {
    uint64_t n = readU64(f);
    std::string s(n, '\0');
    if (n > 0 && !f.read(&s[0], n)) throw std::runtime_error("binary: unexpected end of file");
    return s;
}

std::ofstream openOut(const std::string& filename, bool binary) {
    std::ofstream f(filename, binary ? std::ios::binary : std::ios::out);
    if (!f.is_open()) throw std::runtime_error("cannot open file for writing: " + filename);
    return f;
}

// Открывает бинарный файл и проверяет заголовок; возвращает количество элементов
uint64_t openIn(std::ifstream& f, const std::string& filename, const std::string& type) {
    f.open(filename, std::ios::binary);
    if (!f.is_open()) throw std::runtime_error("cannot open file for reading: " + filename);
    char magic[4];
    if (!f.read(magic, 4) || std::string(magic, 4) != std::string(MAGIC, 4)) throw std::runtime_error("binary: bad magic");
    std::string t = readStr(f);
    if (t != type) throw std::runtime_error("binary: type mismatch, expected " + type + ", got " + t);
    return readU64(f);
}

json readJson(const std::string& filename, const std::string& type) {
    std::ifstream f(filename);
    if (!f.is_open()) throw std::runtime_error("cannot open file for reading: " + filename);
    json j;
    try { f >> j; } catch (json::exception& e) { throw std::runtime_error(std::string("text: bad json: ") + e.what()); }
    if (!j.contains("type") || j["type"] != type) throw std::runtime_error("text: type mismatch, expected " + type);
    return j;
}
}  // namespace

namespace Serializer {

void saveStringsBinary(const std::string& filename, const std::string& type, const std::vector<std::string>& items) {
    std::ofstream f = openOut(filename, true);
    f.write(MAGIC, 4);
    writeStr(f, type);
    writeU64(f, items.size());
    for (auto& s : items) writeStr(f, s);
}

std::vector<std::string> loadStringsBinary(const std::string& filename, const std::string& type) {
    std::ifstream f;
    uint64_t n = openIn(f, filename, type);
    std::vector<std::string> res;
    for (uint64_t i = 0; i < n; ++i) res.push_back(readStr(f));
    return res;
}

void saveIntsBinary(const std::string& filename, const std::string& type, const std::vector<int>& items) {
    std::ofstream f = openOut(filename, true);
    f.write(MAGIC, 4);
    writeStr(f, type);
    writeU64(f, items.size());
    for (int v : items) f.write(reinterpret_cast<const char*>(&v), sizeof(v));
}

std::vector<int> loadIntsBinary(const std::string& filename, const std::string& type) {
    std::ifstream f;
    uint64_t n = openIn(f, filename, type);
    std::vector<int> res;
    for (uint64_t i = 0; i < n; ++i) {
        int v;
        if (!f.read(reinterpret_cast<char*>(&v), sizeof(v))) throw std::runtime_error("binary: unexpected end of file");
        res.push_back(v);
    }
    return res;
}

void saveStringsText(const std::string& filename, const std::string& type, const std::vector<std::string>& items) {
    std::ofstream f = openOut(filename, false);
    json j;
    j["type"] = type;
    j["items"] = items;
    f << j.dump(4);
}

std::vector<std::string> loadStringsText(const std::string& filename, const std::string& type) {
    return readJson(filename, type)["items"].get<std::vector<std::string>>();
}

void saveIntsText(const std::string& filename, const std::string& type, const std::vector<int>& items) {
    std::ofstream f = openOut(filename, false);
    json j;
    j["type"] = type;
    j["items"] = items;
    f << j.dump(4);
}

std::vector<int> loadIntsText(const std::string& filename, const std::string& type) {
    return readJson(filename, type)["items"].get<std::vector<int>>();
}

}  // namespace Serializer
