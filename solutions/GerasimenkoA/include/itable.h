// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// itable.h
//
// Copyright (c) Пинежанин Е.С.

#ifndef __ITable_H__
#define __ITable_H__

#include <string>

using namespace std;

template <typename T> 
class ITable {
protected:
    int data_count;

public:
    ITable() { data_count = 0; }

    virtual ~ITable() {}

    virtual void insert(const string& key, const T& value) = 0;

    virtual void remove(const string& key) = 0;

    virtual T& find(const string& key) = 0;

    virtual bool contains(const string& key) = 0;

    virtual void clear() = 0;

    int size() const { return data_count; }

    bool empty() const { return data_count == 0; }

};

#endif
