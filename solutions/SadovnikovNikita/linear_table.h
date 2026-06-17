#pragma once
#include "table_interface.h"
#include <vector>
#include <utility>
#include <algorithm>

class TLinearTable : public ITable {
private:
    std::vector<std::pair<int, std::string>> data;
public:
    void insert(int key, const std::string& value) override;
    bool remove(int key) override;
    std::string* search(int key) override;
    const std::string* search(int key) const override;
    bool contains(int key) const override;
    size_t size() const override;
    void clear() override;
    std::string getType() const override;
};