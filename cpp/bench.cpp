// Бенчмарки: среднее время операции для разных n (std::chrono).
// Показывают, как растёт время: O(1), O(n), O(log n).
#include "AVLTree.hpp"
#include "DoublyList.hpp"
#include "ForwardList.hpp"
#include "MyArray.hpp"
#include "MyHashTable.hpp"
#include "MyStack.hpp"
#include <chrono>
#include <functional>
#include <iomanip>
#include <iostream>
#include <string>

using Clock = std::chrono::steady_clock;

// Запускает op n раз и возвращает время одной операции в наносекундах
double measure(int n, const std::function<void(int)>& op) {
    auto a = Clock::now();
    for (int i = 0; i < n; ++i) op(i);
    auto b = Clock::now();
    return (double)std::chrono::duration_cast<std::chrono::nanoseconds>(b - a).count() / n;
}

void row(const std::string& name, const std::function<double(int)>& f) {
    std::cout << std::left << std::setw(34) << name << std::right << std::fixed << std::setprecision(1);
    for (int n : {1000, 10000, 100000}) std::cout << std::setw(12) << f(n);
    std::cout << std::endl;
}

int main() {
    std::cout << std::left << std::setw(34) << "операция (нс на операцию)" << std::right
              << std::setw(12) << "n=1000" << std::setw(12) << "n=10000" << std::setw(12) << "n=100000" << std::endl;
    row("MyArray::push_back      O(1)*", [](int n) { MyArray a; return measure(n, [&](int i) { a.push_back(std::to_string(i)); }); });
    row("MyArray::get            O(1)", [](int n) {
        MyArray a; for (int i = 0; i < n; ++i) a.push_back("x");
        return measure(n, [&](int i) { volatile auto s = a.get(i).size(); (void)s; });
    });
    row("MyArray::insert_at(0)   O(n)", [](int n) { MyArray a; return measure(n / 10, [&](int i) { a.insert_at(0, std::to_string(i)); }); });
    row("ForwardList::push_front O(1)", [](int n) { ForwardList l; return measure(n, [&](int i) { l.push_front(std::to_string(i)); }); });
    row("DoublyList::find        O(n)", [](int n) {
        DoublyList l; for (int i = 0; i < n; ++i) l.push_back(std::to_string(i));
        return measure(100, [&](int i) { volatile int r = l.find(std::to_string(n - 1 - i)); (void)r; });
    });
    row("MyStack push+pop        O(1)", [](int n) { MyStack s; return measure(n, [&](int i) { s.push(std::to_string(i)); s.pop(); }); });
    row("MyHashTable::put        O(1)", [](int n) { MyHashTable h; return measure(n, [&](int i) { h.put(std::to_string(i), "v"); }); });
    row("MyHashTable::get        O(1)", [](int n) {
        MyHashTable h; for (int i = 0; i < n; ++i) h.put(std::to_string(i), "v");
        return measure(n, [&](int i) { volatile auto s = h.get(std::to_string(i)).size(); (void)s; });
    });
    row("AVLTree::insert         O(log n)", [](int n) { AVLTree t; return measure(n, [&](int i) { t.insert(i * 7919 % 1000003); }); });
    row("AVLTree::find           O(log n)", [](int n) {
        AVLTree t; for (int i = 0; i < n; ++i) t.insert(i);
        return measure(n, [&](int i) { volatile bool r = t.find(i); (void)r; });
    });
    return 0;
}
