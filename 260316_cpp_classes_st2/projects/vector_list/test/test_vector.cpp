#include <gtest/gtest.h>

#include "vector.hpp"

using ssY::Vector;

TEST(VectorTest, PushBack) {
    Vector<int> v;

    v.push_back(1);
    EXPECT_EQ(v.get_size(), 1);

    v.push_back(2);
    EXPECT_EQ(v.get_size(), 2);
}

TEST(VectorTest, HasItem) {
    Vector<int> v;

    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    EXPECT_TRUE(v.has_item(1));
    EXPECT_TRUE(v.has_item(2));
    EXPECT_TRUE(v.has_item(3));
    EXPECT_FALSE(v.has_item(4));
}

TEST(VectorTest, Insert) {
    Vector<int> v;
    v.push_back(2);
    v.push_back(3);

    EXPECT_TRUE(v.insert(0, 1));
    EXPECT_EQ(v.get_size(), 3);
    EXPECT_TRUE(v.has_item(1));
    EXPECT_TRUE(v.has_item(2));
    EXPECT_TRUE(v.has_item(3));

    EXPECT_TRUE(v.insert(1, 4));
    EXPECT_EQ(v.get_size(), 4);
    EXPECT_TRUE(v.has_item(4));

    EXPECT_TRUE(v.insert(4, 5));
    EXPECT_EQ(v.get_size(), 5);
    EXPECT_TRUE(v.has_item(5));
}

TEST(VectorTest, RemoveFirst) {
    Vector<int> v;

    v.push_back(1);
    v.push_back(2);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);

    EXPECT_TRUE(v.remove_first(2));
    EXPECT_EQ(v.get_size(), 4);
    EXPECT_TRUE(v.has_item(2));

    EXPECT_TRUE(v.remove_first(1));
    EXPECT_EQ(v.get_size(), 3);
    EXPECT_FALSE(v.has_item(1));

    EXPECT_TRUE(v.has_item(3));
    EXPECT_TRUE(v.has_item(4));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}