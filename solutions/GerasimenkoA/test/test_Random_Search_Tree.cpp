#include "Random_Search_Tree.h"
#include <gtest.h>

using namespace std;

TEST(Random_Search_Tree, can_insert_and_find) {
    Random_Search_Tree<int> tree;
    ASSERT_NO_THROW(tree.insert("key", 10));
    EXPECT_EQ(tree.find("key"), 10);
}

TEST(Random_Search_Tree, can_overwrite_value) {
    Random_Search_Tree<int> tree;
    tree.insert("key", 10);
    tree.insert("key", 30);
    EXPECT_EQ(tree.find("key"), 30);
}

TEST(Random_Search_Tree, cant_find_in_empty_tree) {
    Random_Search_Tree<int> tree;
    ASSERT_ANY_THROW(tree.find("key"));
}

TEST(Random_Search_Tree, cant_remove_in_empty_tree) {
    Random_Search_Tree<int> tree;
    ASSERT_ANY_THROW(tree.remove("key"));
}

TEST(Random_Search_Tree, can_remove_leaf_node) {
    Random_Search_Tree<int> tree;
    tree.insert("b", 2);
    tree.insert("a", 1);
    tree.insert("c", 3);

    ASSERT_NO_THROW(tree.remove("a"));
    ASSERT_ANY_THROW(tree.find("a"));
    EXPECT_EQ(tree.find("b"), 2);
    EXPECT_EQ(tree.find("c"), 3);
}

TEST(Random_Search_Tree, cant_remove_nonexistent_key) {
    Random_Search_Tree<int> tree;
    tree.insert("a", 1);
    ASSERT_ANY_THROW(tree.remove("b"));
}