#pragma once

template <typename...Args>
auto constexpr do_nothing_return_last(Args&&...args) {
    // comma operator discards the result of the left
    //  must be in () because of it's low precedence
    //  calling a function with it gets rid of the 'no effect' warning so std::forward it is
    return (std::forward<Args>(args), ...);
}
