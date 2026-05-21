#include "thashchain.h"
#include <gtest.h>

using namespace std;

TEST(THashChain, can_insert_and_find) {
    THashChain<int> table(5);
    ASSERT_NO_THROW(table.insert("key", 10));
    EXPECT_EQ(table.find("key"), 10);
}

TEST(THashChain, can_overwrite_value) {
    THashChain<int> table(5);
    table.insert("key", 10);
    table.insert("key", 55);
    EXPECT_EQ(table.find("key"), 55);
}

TEST(THashChain, cant_find_in_empty_table) {
    THashChain<int> table(5);
    ASSERT_ANY_THROW(table.find("key"));
}

TEST(THashChain, cant_remove_in_empty_table) {
    THashChain<int> table(5);
    ASSERT_ANY_THROW(table.remove("key"));
}

TEST(THashChain, can_handle_collision) {
    THashChain<int> table(1);
    ASSERT_NO_THROW(table.insert("ab", 10));
    ASSERT_NO_THROW(table.insert("ba", 20));
    EXPECT_EQ(table.find("ab"), 10);
    EXPECT_EQ(table.find("ba"), 20);
}

TEST(THashChain, can_remove_element_after_collision) {
    THashChain<int> table(1);
    table.insert("ab", 10);
    table.insert("ba", 20);

    ASSERT_NO_THROW(table.remove("ab"));
    ASSERT_ANY_THROW(table.find("ab"));
    EXPECT_EQ(table.find("ba"), 20);
}

TEST(THashChain, cant_remove_nonexistent_key) {
    THashChain<int> table(3);
    table.insert("a", 1);
    ASSERT_ANY_THROW(table.remove("b"));
}