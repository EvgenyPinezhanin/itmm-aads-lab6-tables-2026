#pragma once
#include <string>
#include <cstddef>

class ITable {
public:
    virtual ~ITable() = default;
    
    virtual void insert(int key, const std::string& value) = 0;
    virtual bool remove(int key) = 0;
    virtual std::string* search(int key) = 0;
    virtual const std::string* search(int key) const = 0;
    virtual bool contains(int key) const = 0;
    virtual size_t size() const = 0;
    virtual void clear() = 0;
    virtual std::string getType() const = 0;
};