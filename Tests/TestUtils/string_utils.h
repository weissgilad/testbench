#pragma once

#include <string>

constexpr char MIN_PRINTABLE_CHAR = 0x20;
constexpr char MAX_PRINTABLE_CHAR = 0x7e;

template <typename T, size_t N,
          std::enable_if_t<std::is_base_of_v<std::string, T> || std::is_base_of_v<std::string_view, T>, bool> = true>
std::string get_something_not_in_list(const std::array<T,N>& list);

#include "string_utils.tpp"
