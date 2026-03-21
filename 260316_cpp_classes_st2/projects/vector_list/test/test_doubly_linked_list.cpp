#include <gtest/gtest.h>

#include "doubly_linked_list.hpp"

using ssY::DoublyLinkedList;

TEST(DoublyLinkedListTest, PushBack) {
    DoublyLinkedList<int> l;

    l.push_back(1);
    EXPECT_EQ(l.get_size(), 1);

    l.push_back(2);
    EXPECT_EQ(l.get_size(), 2);
}

TEST(DoublyLinkedListTest, HasItem) {
    DoublyLinkedList<int> l;

    l.push_back(1);
    l.push_back(2);
    l.push_back(3);

    EXPECT_TRUE(l.has_item(1));
    EXPECT_TRUE(l.has_item(2));
    EXPECT_TRUE(l.has_item(3));
    EXPECT_FALSE(l.has_item(4));
}

TEST(DoublyLinkedListTest, RemoveFirst) {
    DoublyLinkedList<int> l;

    l.push_back(1);
    l.push_back(2);
    l.push_back(2);
    l.push_back(3);
    l.push_back(4);

    EXPECT_TRUE(l.remove_first(2));
    EXPECT_EQ(l.get_size(), 4);
    EXPECT_TRUE(l.has_item(2));

    EXPECT_TRUE(l.remove_first(1));
    EXPECT_EQ(l.get_size(), 3);
    EXPECT_FALSE(l.has_item(1));

    EXPECT_TRUE(l.has_item(3));
    EXPECT_TRUE(l.has_item(4));
}

TEST(DoublyLinkedListTest, RemoveFirst_1el) {
    DoublyLinkedList<int> l;

    l.push_back(1);

    EXPECT_TRUE(l.remove_first(1));
	
    EXPECT_EQ(l.get_size(), 0);
    EXPECT_FALSE(l.has_item(1));
}
TEST(DoublyLinkedListTest, RemoveFirst_2el_first_out) {
    DoublyLinkedList<int> l;

    l.push_back(1);
    l.push_back(2);

    EXPECT_TRUE(l.remove_first(1));
	
    EXPECT_EQ(l.get_size(), 1);
    EXPECT_FALSE(l.has_item(1));
    EXPECT_TRUE(l.has_item(2));
}
TEST(DoublyLinkedListTest, RemoveFirst_2el_second_out) {
    DoublyLinkedList<int> l;

    l.push_back(1);
    l.push_back(2);

    EXPECT_TRUE(l.remove_first(2));
	
    EXPECT_EQ(l.get_size(), 1);
    EXPECT_TRUE(l.has_item(1));
    EXPECT_FALSE(l.has_item(2));
}
TEST(DoublyLinkedListTest, RemoveFirst_3el_first_out) {
    DoublyLinkedList<int> l;

    l.push_back(1);
    l.push_back(2);
    l.push_back(3);

    EXPECT_TRUE(l.remove_first(1));
	
    EXPECT_EQ(l.get_size(), 2);
    EXPECT_FALSE(l.has_item(1));
    EXPECT_TRUE(l.has_item(2));
    EXPECT_TRUE(l.has_item(3));
}
TEST(DoublyLinkedListTest, RemoveFirst_3el_second_out) {
    DoublyLinkedList<int> l;

    l.push_back(1);
    l.push_back(2);
    l.push_back(3);

    EXPECT_TRUE(l.remove_first(2));
	
    EXPECT_EQ(l.get_size(), 2);
    EXPECT_TRUE(l.has_item(1));
    EXPECT_FALSE(l.has_item(2));
    EXPECT_TRUE(l.has_item(3));
}
TEST(DoublyLinkedListTest, RemoveFirst_3el_third_out) {
    DoublyLinkedList<int> l;

    l.push_back(1);
    l.push_back(2);
    l.push_back(3);

    EXPECT_TRUE(l.remove_first(3));
	
    EXPECT_EQ(l.get_size(), 2);
    EXPECT_TRUE(l.has_item(1));
    EXPECT_TRUE(l.has_item(2));
    EXPECT_FALSE(l.has_item(3));
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}