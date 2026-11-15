#include "Serializer.hpp"
#include "json.hpp"
#include <cstdint>
#include <fstream>
#include <stdexcept>

using namespace std;

using json = nlohmann::json;

namespace {
const char MAGIC[4] = {'L', 'A', 'B', '3'};

void writeU64(ofstream& f, uint64_t v) { f.write(reinterpret_cast<const char*>(&v), sizeof(v)); }

uint64_t readU64(ifstream& f) {
    uint64_t v = 0;
    if (!f.read(reinterpret_cast<char*>(&v), sizeof(v))) throw runtime_error("binary: unexpected end of file");
    return v;
}

void writeStr(ofstream& f, const string& s) {
    writeU64(f, s.size());
    f.write(s.data(), s.size());
}

string readStr(ifstream& f) {
    uint64_t n = readU64(f);
    string s(n, '\0');
    if (n > 0 && !f.read(&s[0], n)) throw runtime_error("binary: unexpected end of file");
    return s;
}

ofstream openOut(const string& filename, bool binary) {
    ofstream f(filename, binary ? ios::binary : ios::out);
    if (!f.is_open()) throw runtime_error("cannot open file for writing: " + filename);
    return f;
}

// Открывает бинарный файл и проверяет заголовок; возвращает количество элементов
uint64_t openIn(ifstream& f, const string& filename, const string& type) {
    f.open(filename, ios::binary);
    if (!f.is_open()) throw runtime_error("cannot open file for reading: " + filename);
    char magic[4];
    if (!f.read(magic, 4) || string(magic, 4) != string(MAGIC, 4)) throw runtime_error("binary: bad magic");
    string t = readStr(f);
    if (t != type) throw runtime_error("binary: type mismatch, expected " + type + ", got " + t);
    return readU64(f);
}

json readJson(const string& filename, const string& type) {
    ifstream f(filename);
    if (!f.is_open()) throw runtime_error("cannot open file for reading: " + filename);
    json j;
    try { f >> j; } catch (json::exception& e) { throw runtime_error(string("text: bad json: ") + e.what()); }
    if (!j.contains("type") || j["type"] != type) throw runtime_error("text: type mismatch, expected " + type);
    return j;
}
}  // namespace

namespace Serializer {

void saveStringsBinary(const string& filename, const string& type, const vector<string>& items) {
    ofstream f = openOut(filename, true);
    f.write(MAGIC, 4);
    writeStr(f, type);
    writeU64(f, items.size());
    for (auto& s : items) writeStr(f, s);
}

vector<string> loadStringsBinary(const string& filename, const string& type) {
    ifstream f;
    uint64_t n = openIn(f, filename, type);
    vector<string> res;
    for (uint64_t i = 0; i < n; ++i) res.push_back(readStr(f));
    return res;
}

void saveIntsBinary(const string& filename, const string& type, const vector<int>& items) {
    ofstream f = openOut(filename, true);
    f.write(MAGIC, 4);
    writeStr(f, type);
    writeU64(f, items.size());
    for (int v : items) f.write(reinterpret_cast<const char*>(&v), sizeof(v));
}

vector<int> loadIntsBinary(const string& filename, const string& type) {
    ifstream f;
    uint64_t n = openIn(f, filename, type);
    vector<int> res;
    for (uint64_t i = 0; i < n; ++i) {
        int v;
        if (!f.read(reinterpret_cast<char*>(&v), sizeof(v))) throw runtime_error("binary: unexpected end of file");
        res.push_back(v);
    }
    return res;
}

void saveStringsText(const string& filename, const string& type, const vector<string>& items) {
    ofstream f = openOut(filename, false);
    json j;
    j["type"] = type;
    j["items"] = items;
    f << j.dump(4);
}

vector<string> loadStringsText(const string& filename, const string& type) {
    return readJson(filename, type)["items"].get<vector<string>>();
}

void saveIntsText(const string& filename, const string& type, const vector<int>& items) {
    ofstream f = openOut(filename, false);
    json j;
    j["type"] = type;
    j["items"] = items;
    f << j.dump(4);
}

vector<int> loadIntsText(const string& filename, const string& type) {
    return readJson(filename, type)["items"].get<vector<int>>();
}

}  // namespace Serializer
