#ifndef TABLE_H
#define TABLE_H

#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <chrono>

template<typename K, typename V>
class Table {
public:
    ~Table() = default;

    // Основные операции
    insert(const K& key, const V& value) = 0;
    bool remove(const K& key) = 0;
    bool search(const K& key, V& value) = 0;
    bool contains(const K& key) = 0;
    size_t size() const = 0;
    bool empty() const = 0;
    void clear() = 0;
    std::string getName() const = 0;

   

protected:  
    int getOperationCount() const { return operationCount; }
    void incOperationCount() { operationCount++; }
    void resetOperationCount() { operationCount = 0; }

private:
    int operationCount = 0;
};

#endif