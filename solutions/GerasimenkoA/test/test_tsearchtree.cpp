#include "tsearchtree.h"
#include <gtest.h>

using namespace std;

TEST(TSearchTree, can_insert_and_find) {
    TSearchTree<int> tree;
    ASSERT_NO_THROW(tree.insert("key", 10));
    EXPECT_EQ(tree.find("key"), 10);
}

TEST(TSearchTree, can_overwrite_value) {
    TSearchTree<int> tree;
    tree.insert("key", 10);
    tree.insert("key", 30);
    EXPECT_EQ(tree.find("key"), 30);
}

TEST(TSearchTree, cant_find_in_empty_tree) {
    TSearchTree<int> tree;
    ASSERT_ANY_THROW(tree.find("key"));
}

TEST(TSearchTree, cant_remove_in_empty_tree) {
    TSearchTree<int> tree;
    ASSERT_ANY_THROW(tree.remove("key"));
}

TEST(TSearchTree, can_remove_leaf_node) {
    TSearchTree<int> tree;
    tree.insert("b", 2);
    tree.insert("a", 1);
    tree.insert("c", 3);

    ASSERT_NO_THROW(tree.remove("a"));
    ASSERT_ANY_THROW(tree.find("a"));
    EXPECT_EQ(tree.find("b"), 2);
    EXPECT_EQ(tree.find("c"), 3);
}

TEST(TSearchTree, cant_remove_nonexistent_key) {
    TSearchTree<int> tree;
    tree.insert("a", 1);
    ASSERT_ANY_THROW(tree.remove("b"));
}