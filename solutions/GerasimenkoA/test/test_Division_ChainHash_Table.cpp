#include "Division_ChainHash_Table.h"
#include <gtest.h>

using namespace std;

TEST(Division_ChainHash_Table, can_insert_and_find) {
    Division_ChainHash_Table<int> table(5);
    ASSERT_NO_THROW(table.insert("key", 10));
    EXPECT_EQ(table.find("key"), 10);
}

TEST(Division_ChainHash_Table, can_overwrite_value) {
    Division_ChainHash_Table<int> table(5);
    table.insert("key", 10);
    table.insert("key", 55);
    EXPECT_EQ(table.find("key"), 55);
}

TEST(Division_ChainHash_Table, cant_find_in_empty_table) {
    Division_ChainHash_Table<int> table(5);
    ASSERT_ANY_THROW(table.find("key"));
}

TEST(Division_ChainHash_Table, cant_remove_in_empty_table) {
    Division_ChainHash_Table<int> table(5);
    ASSERT_ANY_THROW(table.remove("key"));
}

TEST(Division_ChainHash_Table, can_handle_collision) {
    Division_ChainHash_Table<int> table(1);
    ASSERT_NO_THROW(table.insert("ab", 10));
    ASSERT_NO_THROW(table.insert("ba", 20));
    EXPECT_EQ(table.find("ab"), 10);
    EXPECT_EQ(table.find("ba"), 20);
}

TEST(Division_ChainHash_Table, can_remove_element_after_collision) {
    Division_ChainHash_Table<int> table(1);
    table.insert("ab", 10);
    table.insert("ba", 20);

    ASSERT_NO_THROW(table.remove("ab"));
    ASSERT_ANY_THROW(table.find("ab"));
    EXPECT_EQ(table.find("ba"), 20);
}

TEST(Division_ChainHash_Table, cant_remove_nonexistent_key) {
    Division_ChainHash_Table<int> table(3);
    table.insert("a", 1);
    ASSERT_ANY_THROW(table.remove("b"));
}