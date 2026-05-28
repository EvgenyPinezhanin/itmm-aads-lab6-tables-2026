#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
#include <random>
#include <iomanip>
#include <numeric>

#include "table_interface.h"
#include "linear_table.h"
#include "search_tree.h"
#include "hash_chain.h"
#include "hash_open.h"

template<typename TableType>
double measureTime(void (TableType::*method)(int, const std::string&), 
                   TableType& table, const std::vector<int>& keys) {
    auto start = std::chrono::high_resolution_clock::now();
    for (int k : keys) table.insert(k, "val_" + std::to_string(k));
    return std::chrono::duration<double, std::milli>(std::chrono::high_resolution_clock::now() - start).count();
}

template<typename TableType>
double measureSearchTime(TableType& table, const std::vector<int>& keys) {
    auto start = std::chrono::high_resolution_clock::now();
    for (int k : keys) table.search(k);
    return std::chrono::duration<double, std::milli>(std::chrono::high_resolution_clock::now() - start).count();
}

template<typename TableType>
double measureRemoveTime(TableType& table, const std::vector<int>& keys) {
    auto start = std::chrono::high_resolution_clock::now();
    for (int k : keys) table.remove(k);
    return std::chrono::duration<double, std::milli>(std::chrono::high_resolution_clock::now() - start).count();
}

template<typename TableType>
void testTable(const std::string& name, size_t size) {
    std::cout << "\n=== " << name << " (N=" << size << ") ===\n";
    
    std::vector<int> keys(size);
    std::iota(keys.begin(), keys.end(), 1);
    std::shuffle(keys.begin(), keys.end(), std::mt19937(std::random_device{}()));
    
    std::vector<int> searchKeys(keys.begin(), keys.begin() + std::min(size, static_cast<size_t>(10000)));
    
    TableType table;
    double t_ins = measureTime(&TableType::insert, table, keys);
    double t_sch = measureSearchTime(table, searchKeys);
    double t_rem = measureRemoveTime(table, keys);
    
    std::cout << std::fixed << std::setprecision(3);
    std::cout << "Insert:  " << t_ins << " ms (" << (t_ins/size*1e6) << " ns/op)\n";
    std::cout << "Search:  " << t_sch << " ms (" << (t_sch/searchKeys.size()*1e6) << " ns/op)\n";
    std::cout << "Remove:  " << t_rem << " ms (" << (t_rem/size*1e6) << " ns/op)\n";
}

int main() {
    std::cout << "===== Lab #2: Table Research (Sadovnikov Nikita) =====\n";
    std::vector<size_t> sizes = {1000, 5000, 10000};
    
    for (size_t n : sizes) {
        std::cout << "\n---------- SIZE: " << n << " ----------\n";
        testTable<TLinearTable>("Sorted Linear Table", n);
        testTable<TSearchTree>("Random Search Tree", n);
        testTable<THashChain>("Hash Chain (Multiplication)", n);
        testTable<THashOpen>("Hash Open (Linear Probing)", n);
    }
    std::cout << "\n===== Done =====\n";
    return 0;
}