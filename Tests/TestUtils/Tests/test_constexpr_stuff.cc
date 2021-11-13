#include "gtest/gtest.h"

#include <numeric>
#include "TestUtils/constexpr_stuff.h"

class Test_exists_in_list : public ::testing::Test {
protected:
    static constexpr auto m_test_array = std::array {1,2,3};
};

TEST_F(Test_exists_in_list, ConstepxrnessInList) {
    // this test will simply not compile if the function is not constexpr
    constexpr bool placeholder = exists_in_list(1 , m_test_array);
    ASSERT_TRUE(placeholder);
}

TEST_F(Test_exists_in_list, NotInList) {
    bool in_list = exists_in_list(4 , m_test_array);
    ASSERT_FALSE(in_list);
}

TEST_F(Test_exists_in_list, EmptyList) {
    bool in_list = exists_in_list(1 , std::array<decltype(1), 0> {});
    ASSERT_FALSE(in_list);
}


class Test_get_something_not_in_list_Integral : public ::testing::Test {
protected:
    static constexpr auto m_test_array = std::array {1,2,3};
};

TEST_F(Test_get_something_not_in_list_Integral, ConstepxrnessNovelElement) {
    // this test will simply not compile if the function is not constexpr
    constexpr auto placeholder = get_something_not_in_list(m_test_array);
    ASSERT_TRUE(placeholder.has_value());
    decltype(placeholder)::value_type novel_element = *placeholder;
    for (const auto& elem : m_test_array) {
        ASSERT_NE(elem, novel_element);
    }
}

TEST_F(Test_get_something_not_in_list_Integral, ListFullUnsigned) {
    using value_type_t = uint8_t;
    std::array<value_type_t, 1 << (sizeof(value_type_t) * 8)> m_test_full_array_signed {};
    std::iota(std::begin(m_test_full_array_signed), std::end(m_test_full_array_signed),
              std::numeric_limits<value_type_t>::min());

    auto missing_elem = get_something_not_in_list(m_test_full_array_signed);
    ASSERT_FALSE(missing_elem.has_value());
}

TEST_F(Test_get_something_not_in_list_Integral, ListFullsigned) {
    using value_type_t = int8_t;
    std::array<value_type_t, 1 << (sizeof(value_type_t) * 8)> m_test_full_array_signed {};
    std::iota(std::begin(m_test_full_array_signed), std::end(m_test_full_array_signed),
              std::numeric_limits<value_type_t>::min());

    auto missing_elem = get_something_not_in_list(m_test_full_array_signed);
    ASSERT_FALSE(missing_elem.has_value());
}
