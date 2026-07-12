#include "list.hpp"

#include <gtest/gtest.h>

TEST(ListTest, DefaultConstructor) {
  tgl::list<int> list;
  EXPECT_EQ(list.begin(), nullptr);
}

TEST(ListTest, ConstructWithSize) {
  tgl::list<int> list(10);
  EXPECT_EQ(list.size(), 10);
  for (auto elem : list)     
    EXPECT_EQ(elem, int());
}

TEST(ListTest, ConstructInitializedElements) {
  tgl::list<int> list(10,10);
  EXPECT_EQ(list.size(), 10);
  for (auto elem : list)
    EXPECT_EQ(elem, 10);
}

TEST(ListTest, InitializerList) {
  tgl::list list{0,1,2,3};
  int i{0};
  for (auto elem : list) {
    EXPECT_EQ(elem, i);
    i++;
  }
}

TEST(ListTest, Insert) {
  tgl::list list{0};
  list.insert(list.begin(), -1);
  list.insert(std::next(std::next(list.begin())), 1);
  list.insert(list.end(), 2);
  
  int i{-1};
  ASSERT_EQ(list.size(), 4);
  for (auto elem : list) {
    EXPECT_EQ(elem, i);
    i++;
  }
}

TEST(ListTest, Erase) {
  tgl::list list{0,1,2,3};
  list.erase(list.end());
  list.erase(std::next(list.begin()));
  list.erase(list.begin());
  EXPECT_EQ(list.size(), 1);
  EXPECT_EQ(*list.begin(), 2);
}

TEST(ListTest, PushBack) {
  tgl::list<int> list;
  for (auto i{0}; i<10; i++) 
    list.push_back(i);
  auto i{0};
  for (auto elem : list) {
    EXPECT_EQ(elem, i);
    i++;
  }
  EXPECT_EQ(list.size(),10);
}

TEST(ListTest, PushFront) {
  tgl::list<int> list;
  for (auto i{9}; i>=0; i--) 
    list.push_front(i);
  auto i{0};
  for (auto elem : list) {
    EXPECT_EQ(elem, i);
    i++;
  }
  EXPECT_EQ(list.size(),10);
}

TEST(ListTest, PopBack) {
  tgl::list<int> list{0,1,2,3,4,5};
  for (auto i{0}; i<3; i++) 
    list.pop_back();
  auto i{0};
  for (auto elem : list) {
    EXPECT_EQ(elem, i);
    i++;
  }
  EXPECT_EQ(list.size(),3);
}

TEST(ListTest, PopFront) {
  tgl::list<int> list{0,1,2,3,4,5};
  for (auto i{0}; i<3; i++) 
    list.pop_front();
  auto i{3};
  for (auto elem : list) {
    EXPECT_EQ(elem, i);
    i++;
  }
  EXPECT_EQ(list.size(),3);
}

