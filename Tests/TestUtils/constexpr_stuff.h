#pragma once
#include <array>
#include <numeric>
#include <optional>

template <typename T, size_t N>
constexpr bool exists_in_list(const T& element, const std::array<T,N>& list) {
    if constexpr (0 == N) {
        return false;
    }

    for (const T& elem : list) {
        if (elem == element) {
            return true;
        }
    }
    return false;
}

/* currently, only for numbers (and chars) */
template <typename T, size_t N, std::enable_if_t<std::is_integral_v<T>, bool> = true>
constexpr std::optional<T> get_something_not_in_list(const std::array<T,N>& list) {
    if constexpr (0 == N) {
        return 0;
    }

    for (T num = std::numeric_limits<T>::min(); num < std::numeric_limits<T>::max(); ++num) {
        if (! exists_in_list(num, list)) {
            return num;
        }
    }

    return std::nullopt;
}
