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

TEST_F(list, erase_from_the_beginning) {
    list_0_1_2_3_4.erase(0);
    ASSERT_EQ(list_0_1_2_3_4.size(), 4);
    ASSERT_EQ(list_0_1_2_3_4[0], 1);
}

TEST_F(list, erase_from_the_center) {
    list_0_1_2_3_4.erase(2);
    ASSERT_EQ(list_0_1_2_3_4.size(), 4);
    ASSERT_EQ(list_0_1_2_3_4[2], 3);
}

TEST_F(list, erase_from_the_end) {
    list_0_1_2_3_4.erase(4);
    ASSERT_EQ(list_0_1_2_3_4.size(), 4);
    ASSERT_EQ(list_0_1_2_3_4[3], 3);
}

TEST_F(list, can_not_erase_out_of_range) {
    ASSERT_ANY_THROW(list_0_1_2_3_4.erase(5););
    ASSERT_ANY_THROW(list_0_1_2_3_4.erase(-1););
}

TEST_F(list, can_not_erase_from_empty) {
    ASSERT_ANY_THROW(empty_list.erase(0););
}

TEST_F(list, shows_correct_size) {
    ASSERT_EQ(list_0_1_2_3_4.size(), 5);
    list_0_1_2_3_4.push_back(5);
    ASSERT_EQ(list_0_1_2_3_4.size(), 6);

    ASSERT_EQ(empty_list.size(), 0);
    empty_list.push_back(0);
    ASSERT_EQ(empty_list.size(), 1);
}

TEST_F(list, copies_well) {
    List::Container<int> temp_list = list_0_1_2_3_4; // copy ctor
    bool eq = true;
    for (size_t i = 0; i < list_0_1_2_3_4.size(); ++i)
        if (temp_list[i] != list_0_1_2_3_4[i])
            eq = false;
    
    ASSERT_TRUE(eq);
    ASSERT_EQ(temp_list.size(), list_0_1_2_3_4.size());

    list_0_1_2_3_4.push_back(3);
    temp_list = list_0_1_2_3_4; // copy assignment
    eq = true;
    for (size_t i = 0; i < list_0_1_2_3_4.size(); ++i)
        if (temp_list[i] != temp_list[i])
            eq = false;
    
    ASSERT_TRUE(eq);
    ASSERT_EQ(list_0_1_2_3_4.size(), temp_list.size());
}

TEST(list_dtor, destructs_well) {
    static size_t nodes_counter;
    nodes_counter = 0;

    class list : public List::Container<int> {
    public:
        ~list() {
             this->clear();
        }

        void push_back(int value) override {
            List::Container<int>::push_back(value);
            nodes_counter++;
        }

        void erase(size_t idx) override {
            List::Container<int>::erase(idx);
            nodes_counter--;
        }
    };

    {
        list l1;
        l1.push_back(3);
        l1.push_back(5);
        l1.push_back(7);
        ASSERT_EQ(nodes_counter, 3);
    }

    ASSERT_EQ(nodes_counter, 0);
}

TEST(list_move, moves_well) {
    List::Container<int> list0 {1,2,3};
    List::Container<int> list1;
    list1 = std::move(list0); // move assignment

    ASSERT_EQ(list0.size(), 0);
    ASSERT_EQ(list1.size(), 3);

    list1.push_back(30);
    List::Container<int> list4 = std::move(list1); // move ctor

    ASSERT_EQ(list4.size(), 4);
    ASSERT_EQ(list1.size(), 0);
}
