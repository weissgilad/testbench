#include "gtest/gtest.h"

#include "TestUtils/string_utils.h"

class Test_get_something_not_in_list_String : public ::testing::Test {
protected:
    static constexpr std::array<std::string_view, 3> m_test_array = { "\x20", "\x7e\x7e\x20", "3" };
};

TEST_F(Test_get_something_not_in_list_String, NovelElement) {
    std::string novel_string = get_something_not_in_list(m_test_array);
    for (const auto& elem : m_test_array) {
        ASSERT_NE(elem, novel_string);
    }
}

TEST_F(Test_get_something_not_in_list_String, ListFull) {
    std::array<std::string, MAX_PRINTABLE_CHAR - MIN_PRINTABLE_CHAR + 2> full_list;
    std::iota(std::begin(full_list), std::end(full_list),
              MIN_PRINTABLE_CHAR);

    full_list.back() = "\x7e\x20"; // if the util ever changes, this may be a bad choice

    std::string novel_string = get_something_not_in_list(full_list);
    for (const auto& elem : m_test_array) {
        ASSERT_NE(elem, novel_string);
    }
}
