#include "hash_open.h"

THashOpen::THashOpen(size_t initialSize) : table(initialSize), count(0) {}

size_t THashOpen::hash(int key, size_t i) const {
    return (std::hash<int>{}(key) % table.size() + i) % table.size();
}

void THashOpen::resize() {
    std::vector<Entry> old = std::move(table);
    table.clear();
    table.resize(old.size() * 2);
    count = 0;
    for (const auto& e : old) {
        if (e.occupied && !e.deleted) insert(e.key, e.value);
    }
}

void THashOpen::insert(int key, const std::string& value) {
    if (static_cast<double>(count) / table.size() > LOAD_FACTOR) resize();
    for (size_t i = 0; i < table.size(); ++i) {
        size_t idx = hash(key, i);
        if (!table[idx].occupied || table[idx].deleted) {
            table[idx] = Entry(key, value);
            count++;
            return;
        }
        if (table[idx].key == key) { table[idx].value = value; return; }
    }
}

bool THashOpen::remove(int key) {
    for (size_t i = 0; i < table.size(); ++i) {
        size_t idx = hash(key, i);
        if (!table[idx].occupied) return false;
        if (table[idx].key == key && !table[idx].deleted) {
            table[idx].deleted = true;
            count--;
            return true;
        }
    }
    return false;
}

std::string* THashOpen::search(int key) {
    for (size_t i = 0; i < table.size(); ++i) {
        size_t idx = hash(key, i);
        if (!table[idx].occupied) return nullptr;
        if (table[idx].key == key && !table[idx].deleted) return &(table[idx].value);
    }
    return nullptr;
}

const std::string* THashOpen::search(int key) const {
    for (size_t i = 0; i < table.size(); ++i) {
        size_t idx = hash(key, i);
        if (!table[idx].occupied) return nullptr;
        if (table[idx].key == key && !table[idx].deleted) return &(table[idx].value);
    }
    return nullptr;
}

bool THashOpen::contains(int key) const { return search(key) != nullptr; }
size_t THashOpen::size() const { return count; }
void THashOpen::clear() { table.clear(); table.resize(101); count = 0; }
std::string THashOpen::getType() const { return "Hash Table (Open Addressing, Linear Probing)"; }