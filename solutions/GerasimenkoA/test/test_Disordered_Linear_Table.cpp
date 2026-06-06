#include "Disordered_Linear_Table.h"
#include <gtest.h>

using namespace std;

TEST(Disordered_Linear_Table, can_insert_and_find) {
    Disordered_Linear_Table<int> table;
    ASSERT_NO_THROW(table.insert("key", 10));
    EXPECT_EQ(table.find("key"), 10);
}

TEST(Disordered_Linear_Table, can_overwrite_value) {
    Disordered_Linear_Table<int> table;
    table.insert("key", 10);
    table.insert("key", 25);
    EXPECT_EQ(table.find("key"), 25);
}

TEST(Disordered_Linear_Table, cant_find_in_empty_table) {
    Disordered_Linear_Table<int> table;
    ASSERT_ANY_THROW(table.find("key"));
}

TEST(Disordered_Linear_Table, cant_remove_in_empty_table) {
    Disordered_Linear_Table<int> table;
    ASSERT_ANY_THROW(table.remove("key"));
}

TEST(Disordered_Linear_Table, can_remove_element) {
    Disordered_Linear_Table<int> table;
    table.insert("key", 10);
    ASSERT_NO_THROW(table.remove("key"));
    ASSERT_ANY_THROW(table.find("key"));
}

TEST(Disordered_Linear_Table, cant_remove_nonexistent_key) {
    Disordered_Linear_Table<int> table;
    table.insert("a", 1);
    ASSERT_ANY_THROW(table.remove("b"));
}
