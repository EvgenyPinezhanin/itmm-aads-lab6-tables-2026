// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// tsearchtree.h
//
// Copyright (c) Пинежанин Е.С.

#ifndef __TSearchTree_H__
#define __TSearchTree_H__

#include <itable.h>
#include <stdexcept>

using namespace std;

template <typename T> 
class TSearchTree : public ITable<T> {
private:
    struct Node {
        string key;
        T value;

        Node* left;
        Node* right;

        Node(const string& k, const T& v) {
            key = k;
            value = v;

            left = nullptr;
            right = nullptr;
        }
    };

    Node* root;

    Node* insert_node(Node* node, const string& key, const T& value) {
        if (node == nullptr) {
            this->data_count++;
            return new Node(key, value);
        }

        if (key < node->key) {
            node->left = insert_node(node->left, key, value);
        }
        else if (key > node->key) {
            node->right = insert_node(node->right, key, value);
        }
        else {
            node->value = value;
        }

        return node;
    }

    Node* find_node(Node* node, const string& key) {
        if (node == nullptr) {
            return nullptr;
        }

        if (key == node->key) {
            return node;
        }

        if (key < node->key) {
            return find_node(node->left, key);
        }

        return find_node(node->right, key);
    }

    Node* remove_node(Node* node, const string& key) {
        if (node == nullptr) {
            throw out_of_range("Key not found");
        }

        if (key < node->key) {
            node->left = remove_node(node->left, key);
        }
        else if (key > node->key) {
            node->right = remove_node(node->right, key);
        }
        else {
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                this->data_count--;
                return nullptr;
            }

            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                this->data_count--;
                return temp;
            }

            if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                this->data_count--;
                return temp;
            }

            Node* min_node = node->right;
            while (min_node->left != nullptr) {
                min_node = min_node->left;
            }

            node->key = min_node->key;
            node->value = min_node->value;
            node->right = remove_node(node->right, min_node->key);
        }

        return node;
    }

    void clear_node(Node* node) {
        if (node == nullptr) {
            return;
        }

        clear_node(node->left);
        clear_node(node->right);

        delete node;
    }

public:
    TSearchTree() {
        root = nullptr;
    }

    ~TSearchTree() {
        clear();
    }

    void insert(const string& key, const T& value) override {
        root = insert_node(root, key, value);
    }

    void remove(const string& key) override {
        root = remove_node(root, key);
    }


    T& find(const string& key) override {
        Node* node = find_node(root, key);

        if (node == nullptr) {
            throw out_of_range("Key not found");
        }

        return node->value;
    }

    bool contains(const string& key) override {
        return find_node(root, key) != nullptr;
    }

    void clear() override {
        clear_node(root);
        root = nullptr;
        this->data_count = 0;
    }
};

#endif
