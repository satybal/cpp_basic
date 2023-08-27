#include <gtest/gtest.h>

#include "../src/vector_container.hpp"

class vector : public ::testing::Test {
protected:
    void SetUp() override {
        for (auto i = 0; i < 5; ++i) { vec_0_1_2_3_4.push_back(i); }
    }

    Vector::Container<int> empty_vec;
    Vector::Container<int> vec_0_1_2_3_4;
};

TEST_F(vector, creates_well) {
    ASSERT_EQ(empty_vec.size(), 0);
}

TEST_F(vector, insert_to_empty) {
    empty_vec.insert(0, 10);
    ASSERT_EQ(empty_vec.size(), 1);
    ASSERT_EQ(empty_vec[0], 10);
}

TEST_F(vector, insert_to_the_end) {
    vec_0_1_2_3_4.insert(5, 20);
    ASSERT_EQ(vec_0_1_2_3_4.size(), 6);
    ASSERT_EQ(vec_0_1_2_3_4[5], 20);
}

TEST_F(vector, insert_to_the_center) {
    vec_0_1_2_3_4.insert(2, 30);
    ASSERT_EQ(vec_0_1_2_3_4.size(), 6);
    ASSERT_EQ(vec_0_1_2_3_4[2], 30);
}

TEST_F(vector, can_not_insert_out_of_range) {
    ASSERT_ANY_THROW(vec_0_1_2_3_4.insert(6, 50));
    ASSERT_ANY_THROW(vec_0_1_2_3_4.insert(-2, 50));
}

TEST_F(vector, push_back) {
    vec_0_1_2_3_4.push_back(20);
    ASSERT_EQ(vec_0_1_2_3_4.size(), 6);
    ASSERT_EQ(vec_0_1_2_3_4[5], 20);
}

TEST_F(vector, erase_from_the_beginning) { // size 4
    vec_0_1_2_3_4.erase(0);
    ASSERT_EQ(vec_0_1_2_3_4.size(), 4);
    ASSERT_EQ(vec_0_1_2_3_4[0], 1);
}

TEST_F(vector, erase_from_the_center) { // size 3
    vec_0_1_2_3_4.erase(2);
    ASSERT_EQ(vec_0_1_2_3_4.size(), 4);
    ASSERT_EQ(vec_0_1_2_3_4[2], 3);
}

TEST_F(vector, erase_from_the_end) { // size 2
    vec_0_1_2_3_4.erase(4);
    ASSERT_EQ(vec_0_1_2_3_4.size(), 4);
    ASSERT_EQ(vec_0_1_2_3_4[3], 3);
}

TEST_F(vector, can_not_erase_out_of_range) { // size 1
    ASSERT_ANY_THROW(vec_0_1_2_3_4.erase(5););
    ASSERT_ANY_THROW(vec_0_1_2_3_4.erase(-1););
}

TEST_F(vector, can_not_erase_from_empty) { // size 1
    ASSERT_ANY_THROW(empty_vec.erase(0););
}

TEST_F(vector, shows_correct_size) { // size 1
    ASSERT_EQ(vec_0_1_2_3_4.size(), 5);
    vec_0_1_2_3_4.push_back(5);
    ASSERT_EQ(vec_0_1_2_3_4.size(), 6);

    ASSERT_EQ(empty_vec.size(), 0);
    empty_vec.push_back(0);
    ASSERT_EQ(empty_vec.size(), 1);
}
