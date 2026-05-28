#include "search_tree.h"

TSearchTree::TSearchTree() : root(nullptr), count(0) {}

std::shared_ptr<TSearchTree::Node> TSearchTree::insertNode(std::shared_ptr<Node> node, int key, const std::string& value) {
    if (!node) return std::make_shared<Node>(key, value);
    if (key < node->key) node->left = insertNode(node->left, key, value);
    else if (key > node->key) node->right = insertNode(node->right, key, value);
    else node->value = value;
    return node;
}

std::shared_ptr<TSearchTree::Node> TSearchTree::removeNode(std::shared_ptr<Node> node, int key) {
    if (!node) return nullptr;
    if (key < node->key) node->left = removeNode(node->left, key);
    else if (key > node->key) node->right = removeNode(node->right, key);
    else {
        if (!node->left) return node->right;
        if (!node->right) return node->left;
        auto minNode = findMin(node->right);
        node->key = minNode->key;
        node->value = minNode->value;
        node->right = removeNode(node->right, minNode->key);
    }
    return node;
}

std::shared_ptr<TSearchTree::Node> TSearchTree::findMin(std::shared_ptr<Node> node) const {
    while (node->left) node = node->left;
    return node;
}

std::shared_ptr<TSearchTree::Node> TSearchTree::searchNode(std::shared_ptr<Node> node, int key) const {
    if (!node || node->key == key) return node;
    return (key < node->key) ? searchNode(node->left, key) : searchNode(node->right, key);
}

void TSearchTree::insert(int key, const std::string& value) {
    if (!contains(key)) count++;
    root = insertNode(root, key, value);
}

bool TSearchTree::remove(int key) {
    if (contains(key)) { root = removeNode(root, key); count--; return true; }
    return false;
}

std::string* TSearchTree::search(int key) {
    auto node = searchNode(root, key);
    return node ? &(node->value) : nullptr;
}

const std::string* TSearchTree::search(int key) const {
    auto node = searchNode(root, key);
    return node ? &(node->value) : nullptr;
}

bool TSearchTree::contains(int key) const { return searchNode(root, key) != nullptr; }
size_t TSearchTree::size() const { return count; }
void TSearchTree::clear() { root = nullptr; count = 0; }
std::string TSearchTree::getType() const { return "Random Search Tree"; }