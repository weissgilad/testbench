#include "string_utils.h"
#include "TestUtils/constexpr_stuff.h"

/* This function is extremely naive and produces a bunch of MAX_PRINTABLE_CHAR until finally some other printable char */
template <typename T, size_t N,
          std::enable_if_t<std::is_base_of_v<std::string, T> || std::is_base_of_v<std::string_view, T>, bool> = true>
std::string get_something_not_in_list(const std::array<T,N>& list) {
    if constexpr (0 == N) {
        return "0";
    }

    std::string novel_element { MIN_PRINTABLE_CHAR };
    // inefficient conversion to std::string probably
    while (exists_in_list(T { novel_element }, list)) {
        char& last_char = novel_element[novel_element.length() - 1];
        if (last_char < MAX_PRINTABLE_CHAR) {
            ++last_char;
        } else {
            novel_element += MIN_PRINTABLE_CHAR;
        }
    }

    return novel_element;
}
