#include <array>
#include "gtest/gtest.h"
#include "src/xmacro_stuff/xmacro_definitions.h"
#include "TestUtils/constexpr_stuff.h"
#include "TestUtils/string_utils.h"

TEST(XmacroTests, WORD_EnumToString) {
#define X(wrd, str) ASSERT_STREQ(word_to_str(WORD::wrd), str);
    LIST_OF_WORDS(X)
#undef X
}

TEST(XmacroTests, WORD_EnumToStringFail) {
    constexpr auto array_of_words = std::array {
#define X(wrd, str) static_cast<std::underlying_type_t<WORD>>(WORD::wrd),
        LIST_OF_WORDS(X)
#undef X
    };

    const auto novel_element = get_something_not_in_list(array_of_words);
    /* Assuming get_something_not_in_list works properly */
    ASSERT_TRUE(novel_element.has_value());
    const char* word_string = word_to_str(static_cast<WORD>(*novel_element));

    ASSERT_EQ(nullptr, word_string);
}

TEST(XmacroTests, WORD_StringToEnumFail) {
    constexpr auto array_of_words = std::array {
#define X(wrd, str) std::string_view { str },
        LIST_OF_WORDS(X)
#undef X
    };

    const std::string novel_element = get_something_not_in_list(array_of_words);
    ASSERT_FALSE(novel_element.empty());

    ASSERT_EQ(WORD::ERROR, str_to_word(novel_element.c_str()));
}

TEST(XmacroTests, WORD_StringToEnum) {
#define X(wrd, str) ASSERT_EQ(str_to_word(str), WORD::wrd);
    LIST_OF_WORDS(X)
#undef X
}

