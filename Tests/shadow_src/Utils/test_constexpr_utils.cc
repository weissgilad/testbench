#include "gtest/gtest.h"
#include "Utils/constexpr_utils.h"

TEST(DoNothingReturnLast, constexprnessAndFunctionality) {
    constexpr auto placeholder = do_nothing_return_last(1, 'a', 1.0, false);
    ASSERT_FALSE(placeholder);
}