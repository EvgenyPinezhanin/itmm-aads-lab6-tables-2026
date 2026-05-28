#include "linear_table.h"

void TLinearTable::insert(int key, const std::string& value) {
    auto it = std::lower_bound(data.begin(), data.end(),
                               std::make_pair(key, std::string()),
                               [](const auto& a, const auto& b) { return a.first < b.first; });
    
    if (it != data.end() && it->first == key) {
        it->second = value;
    } else {
        data.insert(it, {key, value});
    }
}

bool TLinearTable::remove(int key) {
    auto it = std::lower_bound(data.begin(), data.end(),
                               std::make_pair(key, std::string()),
                               [](const auto& a, const auto& b) { return a.first < b.first; });
    
    if (it != data.end() && it->first == key) {
        data.erase(it);
        return true;
    }
    return false;
}

std::string* TLinearTable::search(int key) {
    auto it = std::lower_bound(data.begin(), data.end(),
                               std::make_pair(key, std::string()),
                               [](const auto& a, const auto& b) { return a.first < b.first; });
    return (it != data.end() && it->first == key) ? &(it->second) : nullptr;
}

const std::string* TLinearTable::search(int key) const {
    auto it = std::lower_bound(data.begin(), data.end(),
                               std::make_pair(key, std::string()),
                               [](const auto& a, const auto& b) { return a.first < b.first; });
    return (it != data.end() && it->first == key) ? &(it->second) : nullptr;
}

bool TLinearTable::contains(int key) const { return search(key) != nullptr; }
size_t TLinearTable::size() const { return data.size(); }
void TLinearTable::clear() { data.clear(); }
std::string TLinearTable::getType() const { return "Sorted Linear Table"; }