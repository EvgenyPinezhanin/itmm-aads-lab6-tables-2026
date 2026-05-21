// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// thashopen.h
//
// Copyright (c) Пинежанин Е.С.

#ifndef __THashOpen_H__
#define __THashOpen_H__

#include <itable.h>
#include <stdexcept>

using namespace std;

template <typename T> 
class THashOpen : public ITable<T> {
private:
    struct Node {
        string key;
        T value;

        bool is_used;
        bool is_deleted;
    };

    Node* table;
    int table_size;

    int hash_function(const string& key) {
        int hash = 0;

        for (char c : key) {
            hash += c;
        }

        return hash % table_size;
    }

public:
    THashOpen(int size = 10) {
        table_size = size;

        table = new Node[table_size];

        for (int i = 0; i < table_size; i++) {
            table[i].is_used = false;
            table[i].is_deleted = false;
        }
    }

    ~THashOpen() {
        delete[] table;
    }

    void insert(const string& key, const T& value) override {
        int index = hash_function(key);

        for (int i = 0; i < table_size; i++) {

            int current = (index + i) % table_size;

            if (!table[current].is_used || table[current].is_deleted) {

                table[current].key = key;
                table[current].value = value;

                table[current].is_used = true;
                table[current].is_deleted = false;

                this->data_count++;
                return;
            }

            if (table[current].key == key) {
                table[current].value = value;
                return;
            }
        }

        throw out_of_range("Hash table is full");
    }

    void remove(const string& key) override {
        int index = hash_function(key);

        for (int i = 0; i < table_size; i++) {

            int current = (index + i) % table_size;

            if (!table[current].is_used) {
                break;
            }

            if (table[current].key == key &&
                !table[current].is_deleted) {

                table[current].is_deleted = true;

                this->data_count--;

                return;
            }
        }

        throw out_of_range("Key not found");
    }

    T& find(const string& key) override {
        int index = hash_function(key);

        for (int i = 0; i < table_size; i++) {

            int current = (index + i) % table_size;

            if (!table[current].is_used) {
                break;
            }

            if (table[current].key == key &&
                !table[current].is_deleted) {

                return table[current].value;
            }
        }

        throw out_of_range("Key not found");
    }

    bool contains(const string& key) override {
        int index = hash_function(key);

        for (int i = 0; i < table_size; i++) {

            int current = (index + i) % table_size;

            if (!table[current].is_used) {
                return false;
            }

            if (table[current].key == key &&
                !table[current].is_deleted) {

                return true;
            }
        }

        return false;
    }

    void clear() override {
        for (int i = 0; i < table_size; i++) {
            table[i].is_used = false;
            table[i].is_deleted = false;
        }

        this->data_count = 0;
    }
};

#endif
