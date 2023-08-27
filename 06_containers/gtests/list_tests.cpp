#include <gtest/gtest.h>

#include "../src/list_container.hpp"

class list : public ::testing::Test {
protected:
    void SetUp() override {
        for (auto i = 0; i < 5; ++i) { list_0_1_2_3_4.push_back(i); }
    }

    List::Container<int> empty_list;
    List::Container<int> list_0_1_2_3_4;
};

TEST_F(list, creates_well) {
    ASSERT_EQ(empty_list.size(), 0);
}

TEST_F(list, insert_to_empty) {
    empty_list.insert(0, 10);
    ASSERT_EQ(empty_list.size(), 1);
    ASSERT_EQ(empty_list[0], 10);
}

TEST_F(list, insert_to_the_end) {
    list_0_1_2_3_4.insert(5, 20);
    ASSERT_EQ(list_0_1_2_3_4.size(), 6);
    ASSERT_EQ(list_0_1_2_3_4[5], 20);
}

TEST_F(list, insert_to_the_center) {
    list_0_1_2_3_4.insert(2, 30);
    ASSERT_EQ(list_0_1_2_3_4.size(), 6);
    ASSERT_EQ(list_0_1_2_3_4[2], 30);
}

TEST_F(list, can_not_insert_out_of_range) {
    ASSERT_ANY_THROW(list_0_1_2_3_4.insert(6, 50));
    ASSERT_ANY_THROW(list_0_1_2_3_4.insert(-2, 50));
}

TEST_F(list, push_back) {
    list_0_1_2_3_4.push_back(20);
    ASSERT_EQ(list_0_1_2_3_4.size(), 6);
    ASSERT_EQ(list_0_1_2_3_4[5], 20);
}

TEST_F(list, erase_from_the_beginning) { // size 4
    list_0_1_2_3_4.erase(0);
    ASSERT_EQ(list_0_1_2_3_4.size(), 4);
    ASSERT_EQ(list_0_1_2_3_4[0], 1);
}

TEST_F(list, erase_from_the_center) { // size 3
    list_0_1_2_3_4.erase(2);
    ASSERT_EQ(list_0_1_2_3_4.size(), 4);
    ASSERT_EQ(list_0_1_2_3_4[2], 3);
}

TEST_F(list, erase_from_the_end) { // size 2
    list_0_1_2_3_4.erase(4);
    ASSERT_EQ(list_0_1_2_3_4.size(), 4);
    ASSERT_EQ(list_0_1_2_3_4[3], 3);
}

TEST_F(list, can_not_erase_out_of_range) { // size 1
    ASSERT_ANY_THROW(list_0_1_2_3_4.erase(5););
    ASSERT_ANY_THROW(list_0_1_2_3_4.erase(-1););
}

TEST_F(list, can_not_erase_from_empty) { // size 1
    ASSERT_ANY_THROW(empty_list.erase(0););
}

TEST_F(list, shows_correct_size) { // size 1
    ASSERT_EQ(list_0_1_2_3_4.size(), 5);
    list_0_1_2_3_4.push_back(5);
    ASSERT_EQ(list_0_1_2_3_4.size(), 6);

    ASSERT_EQ(empty_list.size(), 0);
    empty_list.push_back(0);
    ASSERT_EQ(empty_list.size(), 1);
}
