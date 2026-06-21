#include "vector.hpp"

#include <gtest/gtest.h>

TEST(VectorTest, CreateEmpty) {
  tgl::vector<int> vec;
  int size = vec.size();
  int capacity = vec.capacity();

  EXPECT_EQ(size, 0);
  EXPECT_EQ(capacity, 0); 
}

TEST(VectorTest, CreateWithCapacity) {
  int initial_capacity( 10 );
  tgl::vector<int> vec( initial_capacity ); 
  int size = vec.size();
  int capacity = vec.capacity();

  EXPECT_EQ(size, 0);
  EXPECT_EQ(capacity, initial_capacity);
}

TEST(VectorTest, CreateInitializerList) {
  tgl::vector<int> vec{0,1,2};

  EXPECT_EQ(vec[0], 0);
  EXPECT_EQ(vec[1], 1);
  EXPECT_EQ(vec[2], 2);
}

TEST(VectorTest, CopyConstructor) {
  tgl::vector<int> vec{0,1,2};
  tgl::vector<int> vec_copy = vec;

  EXPECT_EQ(vec.size(), vec_copy.size());
  EXPECT_EQ(vec.capacity(), vec_copy.capacity());
  EXPECT_EQ(vec_copy[0], 0);
  EXPECT_EQ(vec_copy[1], 1);
  EXPECT_EQ(vec_copy[2], 2);
}

TEST(VectorTest, CopyAssignment) {
  tgl::vector<int> vec{0,1,2};
  tgl::vector<int> vec_copy;
  vec_copy = vec;

  EXPECT_EQ(vec.size(), vec_copy.size());
  EXPECT_EQ(vec.capacity(), vec_copy.capacity());
  EXPECT_EQ(vec_copy[0], 0);
  EXPECT_EQ(vec_copy[1], 1);
  EXPECT_EQ(vec_copy[2], 2);
}

TEST(VectorTest, MoveConstructor) {
  tgl::vector<int> vec{ 0 };
  tgl::vector<int> vec_moved( std::move(vec));

  EXPECT_EQ(vec_moved.size(), 1);
  EXPECT_EQ(vec_moved.capacity(), 1);
  EXPECT_NE(vec_moved.begin().get_ptr(), nullptr);

  EXPECT_EQ(vec.begin().get_ptr(), nullptr);
}

TEST(VectorTest, MoveAssignment) {
  tgl::vector<int> vec{ 0 };
  tgl::vector<int> vec_moved = std::move(vec);

  EXPECT_EQ(vec_moved.size(), 1);
  EXPECT_EQ(vec_moved.capacity(), 1);
  EXPECT_NE(vec_moved.begin().get_ptr(), nullptr);

  EXPECT_EQ(vec.begin().get_ptr(), nullptr);
}

TEST(VectorTest, AccessWithBoundsChecking) {
  tgl::vector<int> vec{0,1,2};
  EXPECT_THROW(vec.at(3), std::out_of_range);
}

TEST(VectorTest, Reserve) {
  tgl::vector<int> vec;
  int new_capacity{ 10 };
  vec.reserve( new_capacity );

  EXPECT_EQ(vec.capacity(), new_capacity);
}

TEST(VectorTest, PushBack) {
  tgl::vector<int> vec{0,1,2};
  vec.push_back(10);

  EXPECT_EQ(vec.size(), 4);
  EXPECT_EQ(*vec.end(), 10);
}

TEST(VectorTest, PopBack) {
  tgl::vector<int> vec{ 0 };
  vec.pop_back();

  EXPECT_EQ(vec.size(), 0);
  EXPECT_THROW(vec.pop_back(), std::out_of_range);
}
