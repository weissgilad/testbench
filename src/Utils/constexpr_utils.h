#pragma once
uint32_t constexpr constexpr_hash(const char *pInput, unsigned int uPrev = 5381) {
    return *pInput
           ? constexpr_hash(pInput + 1, uPrev * 33 + *pInput)
           : uPrev;
}

template <typename...Args>
auto constexpr do_nothing_return_last(Args&&...args) {
    // comma operator discards the result of the left
    //  must be in () because of its low precedence
    //  calling a function with it gets rid of the 'no effect' warning so std::forward it is
    return (std::forward<Args>(args), ...);
}
