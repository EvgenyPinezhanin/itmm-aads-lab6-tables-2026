#include "hash_chain.h"

THashChain::THashChain(size_t initialSize) : table(initialSize), count(0) {}

size_t THashChain::hash(int key) const {
    double product = key * A;
    double fraction = product - std::floor(product);
    return static_cast<size_t>(fraction * table.size());
}

void THashChain::insert(int key, const std::string& value) {
    size_t idx = hash(key);
    for (auto& e : table[idx]) {
        if (e.key == key) { e.value = value; return; }
    }
    table[idx].push_front({key, value});
    count++;
}

bool THashChain::remove(int key) {
    size_t idx = hash(key);
    auto& chain = table[idx];
    for (auto it = chain.begin(); it != chain.end(); ++it) {
        if (it->key == key) { chain.erase(it); count--; return true; }
    }
    return false;
}

std::string* THashChain::search(int key) {
    size_t idx = hash(key);
    for (auto& e : table[idx]) if (e.key == key) return &(e.value);
    return nullptr;
}

const std::string* THashChain::search(int key) const {
    size_t idx = hash(key);
    for (const auto& e : table[idx]) if (e.key == key) return &(e.value);
    return nullptr;
}

bool THashChain::contains(int key) const { return search(key) != nullptr; }
size_t THashChain::size() const { return count; }
void THashChain::clear() { for (auto& c : table) c.clear(); count = 0; }
std::string THashChain::getType() const { return "Hash Table (Chaining, Multiplication)"; }