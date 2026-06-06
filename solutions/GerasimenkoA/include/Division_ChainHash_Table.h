// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Division_ChainHash_Table.h
//
// Copyright (c) Пинежанин Е.С.

#ifndef __Division_ChainHash_Table_H__
#define __Division_ChainHash_Table_H__

#include <itable.h>
#include <stdexcept>

using namespace std;

template <typename T> 
class Division_ChainHash_Table : public ITable<T> {
private:
    struct Node{
        string key;
        T value;

        Node* next;
    };

    Node** table;
    int table_size;

    int hash_function(const string& key) {
        int hash = 0;

        for (char c : key) {
            hash += c;
        }

        return hash % table_size;
    }

public:
    Division_ChainHash_Table(int size = 10) {
        table_size = size;

        table = new Node * [table_size];

        for (int i = 0; i < table_size; i++) {
            table[i] = nullptr;
        }
    }

    ~Division_ChainHash_Table() {
        clear();
        delete[] table;
    }

    void insert(const string& key, const T& value) override {
        int index = hash_function(key);

        Node* current = table[index];

        while (current != nullptr) {
            if (current->key == key) {
                current->value = value;
                return;
            }

            current = current->next;
        }

        Node* new_node = new Node;
        new_node->key = key;
        new_node->value = value;

        new_node->next = table[index];
        table[index] = new_node;

        this->data_count++;
    }

    void remove(const string& key) override {
        int index = hash_function(key);

        Node* current = table[index];
        Node* prev = nullptr;

        while (current != nullptr) {
            if (current->key == key) {

                if (prev == nullptr) {
                    table[index] = current->next;
                }
                else {
                    prev->next = current->next;
                }

                delete current;

                this->data_count--;
                return;
            }

            prev = current;
            current = current->next;
        }

        throw out_of_range("Key not found");
    }

    T& find(const string& key) override {
        int index = hash_function(key);

        Node* current = table[index];

        while (current != nullptr) {
            if (current->key == key) {
                return current->value;
            }

            current = current->next;
        }

        throw out_of_range("Key not found");
    }

    bool contains(const string& key) override {
        int index = hash_function(key);

        Node* current = table[index];

        while (current != nullptr) {
            if (current->key == key) {
                return true;
            }

            current = current->next;
        }

        return false;
    }

    void clear() override {
        for (int i = 0; i < table_size; i++) {

            Node* current = table[i];

            while (current != nullptr) {
                Node* temp = current;

                current = current->next;

                delete temp;
            }

            table[i] = nullptr;
        }

        this->data_count = 0;
    }
};

#endif
