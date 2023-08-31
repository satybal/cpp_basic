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

    Vector::Container<int> temp_vec{1, 2, 3};
    ASSERT_EQ(temp_vec[1], 2);
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

TEST_F(vector, erase_from_the_beginning) {
    vec_0_1_2_3_4.erase(0);
    ASSERT_EQ(vec_0_1_2_3_4.size(), 4);
    ASSERT_EQ(vec_0_1_2_3_4[0], 1);
}

TEST_F(vector, erase_from_the_center) {
    vec_0_1_2_3_4.erase(2);
    ASSERT_EQ(vec_0_1_2_3_4.size(), 4);
    ASSERT_EQ(vec_0_1_2_3_4[2], 3);
}

TEST_F(vector, erase_from_the_end) {
    vec_0_1_2_3_4.erase(4);
    ASSERT_EQ(vec_0_1_2_3_4.size(), 4);
    ASSERT_EQ(vec_0_1_2_3_4[3], 3);
}

TEST_F(vector, can_not_erase_out_of_range) {
    ASSERT_ANY_THROW(vec_0_1_2_3_4.erase(5););
    ASSERT_ANY_THROW(vec_0_1_2_3_4.erase(-1););
}

TEST_F(vector, can_not_erase_from_empty) {
    ASSERT_ANY_THROW(empty_vec.erase(0););
}

TEST_F(vector, shows_correct_size) {
    ASSERT_EQ(vec_0_1_2_3_4.size(), 5);
    vec_0_1_2_3_4.push_back(5);
    ASSERT_EQ(vec_0_1_2_3_4.size(), 6);

    ASSERT_EQ(empty_vec.size(), 0);
    empty_vec.push_back(0);
    ASSERT_EQ(empty_vec.size(), 1);
}

TEST_F(vector, copies_well) {
    Vector::Container<int> temp_vec = vec_0_1_2_3_4;
    bool eq = true;
    for (size_t i = 0; i < vec_0_1_2_3_4.size(); ++i)
        if (vec_0_1_2_3_4[i] != temp_vec[i])
            eq = false;
    
    ASSERT_TRUE(eq);
    ASSERT_EQ(vec_0_1_2_3_4.size(), temp_vec.size());

    vec_0_1_2_3_4.push_back(3);
    temp_vec = vec_0_1_2_3_4;
    eq = true;
    for (size_t i = 0; i < vec_0_1_2_3_4.size(); ++i)
        if (vec_0_1_2_3_4[i] != temp_vec[i])
            eq = false;
    
    ASSERT_TRUE(eq);
    ASSERT_EQ(vec_0_1_2_3_4.size(), temp_vec.size());
}

TEST(vector_dtor, destructs_well) {
    static size_t dtor_counter;
    dtor_counter = 0;
    
    int *p1 = nullptr;

    class vec : public Vector::Container<int> {
    public:
        ~vec() {
            dtor_counter++;
        }
    };

    {
        vec v1, v2, v3;
        v1.push_back(10);
        p1 = v1.get_data();
        ASSERT_EQ(*p1, 10);
    }

    ASSERT_EQ(dtor_counter, 3);
    ASSERT_NE(*p1, 10);
}

TEST(vector_move, moves_well) {
    Vector::Container<int> vec0 {1,2,3};
    Vector::Container<int> vec1;
    vec1 = std::move(vec0);

    ASSERT_EQ(vec0.size(), 0);
    ASSERT_EQ(vec1.size(), 3);

    ASSERT_EQ(vec0.get_data(), nullptr);
    ASSERT_NE(vec1.get_data(), nullptr);
}
