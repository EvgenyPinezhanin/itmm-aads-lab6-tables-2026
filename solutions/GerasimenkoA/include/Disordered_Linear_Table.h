// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Disordered_Linear_Table.h
//
// Copyright (c) Пинежанин Е.С.

#ifndef __Disordered_Linear_Table_H__
#define __Disordered_Linear_Table_H__

#include <itable.h>
#include <stdexcept>

using namespace std;

template <typename T> 
class Disordered_Linear_Table : public ITable<T> {
private:
    struct Node {
        string key;
        T value;
    };

    Node* data;
    int capacity;

    int find_index(const string& key) {
        for (int i = 0; i < this->data_count; i++) {
            if (data[i].key == key) {
                return i;
            }
        }

        return -1;
    }

    void resize() {
        capacity *= 2;

        Node* new_data = new Node[capacity];

        for (int i = 0; i < this->data_count; i++) {
            new_data[i] = data[i];
        }

        delete[] data;
        data = new_data;
    }

public:
    Disordered_Linear_Table(int size = 10) {
        capacity = size;
        data = new Node[capacity];
    }

    ~Disordered_Linear_Table() {
        delete[] data;
    }

    void insert(const string& key, const T& value) override {
        int index = find_index(key);

        if (index != -1) {
            data[index].value = value;
            return;
        }

        if (this->data_count >= capacity) {
            resize();
        }

        data[this->data_count].key = key;
        data[this->data_count].value = value;

        this->data_count++;
    }

    void remove(const string& key) override {
        int index = find_index(key);

        if (index == -1) {
            throw out_of_range("Key not found");
        }

        for (int i = index; i < this->data_count - 1; i++) {
            data[i] = data[i + 1];
        }

        this->data_count--;
    }

    T& find(const string& key) override {
        int index = find_index(key);

        if (index == -1) {
            throw out_of_range("Key not found");
        }

        return data[index].value;
    }

    bool contains(const string& key) override {
        return find_index(key) != -1;
    }

    void clear() override {
        this->data_count = 0;
    }
};

#endif
