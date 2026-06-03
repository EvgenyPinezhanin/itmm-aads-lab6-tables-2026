#include "Linear_OpenHash_Table.h"
#include <gtest.h>

using namespace std;

TEST(Linear_OpenHash_Table, can_insert_and_find) {
    Linear_OpenHash_Table<int> table(5);
    ASSERT_NO_THROW(table.insert("key", 10));
    EXPECT_EQ(table.find("key"), 10);
}

TEST(Linear_OpenHash_Table, can_overwrite_value) {
    Linear_OpenHash_Table<int> table(5);
    table.insert("key", 10);
    table.insert("key", 42);
    EXPECT_EQ(table.find("key"), 42);
}

TEST(Linear_OpenHash_Table, cant_find_in_empty_table) {
    Linear_OpenHash_Table<int> table(5);
    ASSERT_ANY_THROW(table.find("key"));
}

TEST(Linear_OpenHash_Table, cant_remove_in_empty_table) {
    Linear_OpenHash_Table<int> table(5);
    ASSERT_ANY_THROW(table.remove("key"));
}

TEST(Linear_OpenHash_Table, can_handle_collision) {
    Linear_OpenHash_Table<int> table(2);
    ASSERT_NO_THROW(table.insert("ab", 10));
    ASSERT_NO_THROW(table.insert("ba", 20));
    EXPECT_EQ(table.find("ab"), 10);
    EXPECT_EQ(table.find("ba"), 20);
}

TEST(Linear_OpenHash_Table, can_remove_and_insert_after_delete) {
    Linear_OpenHash_Table<int> table(2);
    table.insert("ab", 10);
    table.insert("ba", 20);

    ASSERT_NO_THROW(table.remove("ab"));
    ASSERT_ANY_THROW(table.find("ab"));

    ASSERT_NO_THROW(table.insert("ca", 30));
    EXPECT_EQ(table.find("ca"), 30);
}

TEST(Linear_OpenHash_Table, cant_insert_into_full_table) {
    Linear_OpenHash_Table<int> table(2);
    table.insert("ab", 10);
    table.insert("ba", 20);
    ASSERT_ANY_THROW(table.insert("zz", 30));
}

TEST(Linear_OpenHash_Table, cant_remove_nonexistent_key) {
    Linear_OpenHash_Table<int> table(3);
    table.insert("a", 1);
    ASSERT_ANY_THROW(table.remove("b"));
}