#pragma once
#include "table_interface.h"
#include <memory>

class TSearchTree : public ITable {
private:
    struct Node {
        int key;
        std::string value;
        std::shared_ptr<Node> left;
        std::shared_ptr<Node> right;
        Node(int k, const std::string& v) : key(k), value(v), left(nullptr), right(nullptr) {}
    };
    std::shared_ptr<Node> root;
    size_t count;
    
    std::shared_ptr<Node> insertNode(std::shared_ptr<Node> node, int key, const std::string& value);
    std::shared_ptr<Node> removeNode(std::shared_ptr<Node> node, int key);
    std::shared_ptr<Node> findMin(std::shared_ptr<Node> node) const;
    std::shared_ptr<Node> searchNode(std::shared_ptr<Node> node, int key) const;
public:
    TSearchTree();
    void insert(int key, const std::string& value) override;
    bool remove(int key) override;
    std::string* search(int key) override;
    const std::string* search(int key) const override;
    bool contains(int key) const override;
    size_t size() const override;
    void clear() override;
    std::string getType() const override;
};