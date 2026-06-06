// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Random_Search_Tree.h
//
// Copyright (c) Пинежанин Е.С.

#ifndef __Random_Search_Tree_H__
#define __Random_Search_Tree_H__

#include <itable.h>
#include <stdexcept>
#include <cstdlib>
#include <ctime>  

using namespace std;

template <typename T>
class Random_Search_Tree : public ITable<T> {
private:
    struct Node {
        string key;
        T value;
        int priority;

        Node* left;
        Node* right;

        Node(const string& k, const T& v) {
            key = k;
            value = v;
            priority = rand(); // случайное значение при создании узла
            left = nullptr;
            right = nullptr;
        }
    };

    Node* root;

    // Правый поворот
    Node* rotate_right(Node* p) {
        Node* q = p->left;
        p->left = q->right;
        q->right = p;
        return q;
    }

    // Левый поворот
    Node* rotate_left(Node* p) {
        Node* q = p->right;
        p->right = q->left;
        q->left = p;
        return q;
    }

    Node* insert_node(Node* node, const string& key, const T& value) {
        if (node == nullptr) {
            this->data_count++;
            return new Node(key, value);
        }

        if (key < node->key) {
            node->left = insert_node(node->left, key, value);
            if (node->left->priority > node->priority)
                node = rotate_right(node);
        }
        else if (key > node->key) {
            node->right = insert_node(node->right, key, value);
            if (node->right->priority > node->priority)
                node = rotate_left(node);
        }
        else {
            node->value = value;
        }
        return node;
    }

    Node* find_node(Node* node, const string& key) const {
        if (node == nullptr) return nullptr;
        if (key == node->key) return node;
        if (key < node->key)
            return find_node(node->left, key);
        else
            return find_node(node->right, key);
    }
  
    Node* remove_node(Node* node, const string& key) {
        if (node == nullptr)
            throw out_of_range("Key not found");

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
            if (node->left->priority > node->right->priority) {
                node = rotate_right(node);
                node->right = remove_node(node->right, key);
            }
            else {
                node = rotate_left(node);
                node->left = remove_node(node->left, key);
            }
        }
        return node;
    }

    void clear_node(Node* node) {
        if (node == nullptr) return;
        clear_node(node->left);
        clear_node(node->right);
        delete node;
    }

public:
    Random_Search_Tree() {
        srand(static_cast<unsigned int>(time(0)));
        root = nullptr;
    }

    ~Random_Search_Tree() {
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
        if (node == nullptr)
            throw out_of_range("Key not found");
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