#include <iostream>

#include "set.h"
#include "gtest/gtest.h"

TEST(ConstructorTest, Default) {
    Set<int> s;
    EXPECT_EQ(s.empty(), true);
}


TEST(ConstructorTest, Iterators) {
    Set<int> s{1, 2, 3, 4, 5};

    Set<int> s1(s.begin(), s.end());
    EXPECT_EQ(s1, (Set<int>{1, 2, 3, 4, 5}));
}

TEST(ConstructorTest, SortedInitList) {
    Set<int> s{1, 2, 3, 4, 5};
    EXPECT_EQ(s, (Set<int>{1, 2, 3, 4, 5}));
}

TEST(ConstructorTest, ReversedInitList) {
    Set<int> s{5, 4, 3, 2, 1};
    EXPECT_EQ(s, (Set<int>{1, 2, 3, 4, 5}));
}

TEST(ConstructorTest, RandomInitList) {
    Set<int> s{5, 2, 8, 1, 4, 9};
    EXPECT_EQ(s, (Set<int>{1, 2, 4, 5, 8, 9}));
}

TEST(ConstructorTest, RepeatedInitList) {
    Set<int> s{1, 2, 2, 3, 3, 3, 4, 5, 2, 4, 1, 5, 2, 1};
    EXPECT_EQ(s, (Set<int>{1, 2, 3, 4, 5}));
}

TEST(ConstructorTest, Copy) {
    Set<int> s{5, 2, 8, 1, 4, 9};
    Set<int> s1(s);
    EXPECT_EQ(s1, (Set<int>{1, 2, 4, 5, 8, 9}));

    Set<int> s2 = s;
    EXPECT_EQ(s2, (Set<int>{1, 2, 4, 5, 8, 9}));

}

TEST(InsertTest, Simple) {
    Set<int> s{5, 2, 8, 1, 4, 9};
    s.insert(6);
    EXPECT_EQ(s, (Set<int>{1, 2, 4, 5, 6, 8, 9}));
}

TEST(InsertTest, RepeatingElement) {
    Set<int> s{5, 2, 8, 1, 4, 9};
    s.insert(5);
    EXPECT_EQ(s, (Set<int>{1, 2, 4, 5, 8, 9}));
}

TEST(EraseTest, Simple) {
    Set<int> s{5, 2, 8, 1, 4, 9};
    s.erase(5);
    EXPECT_EQ(s, (Set<int>{1, 2, 4, 8, 9}));
}

TEST(EraseTest, NoElement) {
    Set<int> s{5, 2, 8, 1, 4, 9};
    s.erase(6);
    EXPECT_EQ(s, (Set<int>{1, 2, 4, 5, 8, 9}));
}

TEST(SizeTest, Size) {
    Set<int> s{5, 2, 8, 1, 4, 9};
    EXPECT_EQ(s.size(), 6);
}

TEST(SizeTest, EmptyTrue) {
    Set<int> s;
    EXPECT_EQ(s.empty(), true);
}

TEST(SizeTest, EmptyFalse) {
    Set<int> s{5, 2, 8, 1, 4, 9};
    EXPECT_EQ(s.empty(), false);
}

TEST(FindTest, Find) {
    Set<int> s{5, 2, 8, 1, 4, 9};
    EXPECT_EQ(s.find(1), s.begin());
}

TEST(FindTest, NotFind) {
    Set<int> s{5, 2, 8, 1, 4, 9};
    EXPECT_EQ(s.find(6), s.end());
}

TEST(LowerBoundTest, Find) {
    Set<int> s{5, 2, 8, 1, 4, 9};
    EXPECT_EQ(s.lower_bound(1), s.begin());
}

TEST(LowerBoundTest, NotFind) {
    Set<int> s{5, 2, 8, 1, 4, 9};
    EXPECT_EQ(s.lower_bound(11), s.end());
}

int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
    return 0;
}
