#pragma once
#include "table_interface.h"
#include <vector>
#include <functional>

class THashOpen : public ITable {
private:
    struct Entry {
        int key; std::string value;
        bool occupied; bool deleted;
        Entry() : key(0), value(""), occupied(false), deleted(false) {}
        Entry(int k, const std::string& v) : key(k), value(v), occupied(true), deleted(false) {}
    };
    std::vector<Entry> table;
    size_t count;
    static constexpr double LOAD_FACTOR = 0.7;
    size_t hash(int key, size_t i) const;
    void resize();
public:
    THashOpen(size_t initialSize = 101);
    void insert(int key, const std::string& value) override;
    bool remove(int key) override;
    std::string* search(int key) override;
    const std::string* search(int key) const override;
    bool contains(int key) const override;
    size_t size() const override;
    void clear() override;
    std::string getType() const override;
};