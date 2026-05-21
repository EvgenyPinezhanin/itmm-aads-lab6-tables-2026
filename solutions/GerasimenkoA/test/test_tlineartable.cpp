#include "tlineartable.h"
#include <gtest.h>

using namespace std;

TEST(TLinearTable, can_insert_and_find) {
    TLinearTable<int> table;
    ASSERT_NO_THROW(table.insert("key", 10));
    EXPECT_EQ(table.find("key"), 10);
}

TEST(TLinearTable, can_overwrite_value) {
    TLinearTable<int> table;
    table.insert("key", 10);
    table.insert("key", 25);
    EXPECT_EQ(table.find("key"), 25);
}

TEST(TLinearTable, cant_find_in_empty_table) {
    TLinearTable<int> table;
    ASSERT_ANY_THROW(table.find("key"));
}

TEST(TLinearTable, cant_remove_in_empty_table) {
    TLinearTable<int> table;
    ASSERT_ANY_THROW(table.remove("key"));
}

TEST(TLinearTable, can_remove_element) {
    TLinearTable<int> table;
    table.insert("key", 10);
    ASSERT_NO_THROW(table.remove("key"));
    ASSERT_ANY_THROW(table.find("key"));
}

TEST(TLinearTable, cant_remove_nonexistent_key) {
    TLinearTable<int> table;
    table.insert("a", 1);
    ASSERT_ANY_THROW(table.remove("b"));
}
