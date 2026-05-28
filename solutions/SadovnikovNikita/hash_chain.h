#pragma once
#include "table_interface.h"
#include <vector>
#include <list>
#include <cmath>

class THashChain : public ITable {
private:
    struct Entry { int key; std::string value; };
    std::vector<std::list<Entry>> table;
    size_t count;
    static constexpr double A = 0.618033988749895; // Метод умножения
    size_t hash(int key) const;
public:
    THashChain(size_t initialSize = 101);
    void insert(int key, const std::string& value) override;
    bool remove(int key) override;
    std::string* search(int key) override;
    const std::string* search(int key) const override;
    bool contains(int key) const override;
    size_t size() const override;
    void clear() override;
    std::string getType() const override;
};