#pragma once

#include <iostream>
#include <cmath>

uint32_t constexpr constexpr_hash(const char *pInput, unsigned int uPrev = 5381) {
    return *pInput
           ? constexpr_hash(pInput + 1, uPrev * 33 + *pInput)
           : uPrev;
}


#define LIST_OF_WORDS(X) \
    X(ONE, "one")        \
    X(TWO, "two")        \
    X(THREE, "three")


enum class WORD : uint32_t {
    ERROR = 0,
#define X(name, str) name = constexpr_hash(str),
    LIST_OF_WORDS(X)
#undef X
};

constexpr const char *word_to_str(WORD word) {
    switch (word) {
        case WORD::ERROR:
            return nullptr;
#define X(name, str) case WORD::name: return str;
        LIST_OF_WORDS(X)
#undef X
    }

    return nullptr;
}

constexpr WORD str_to_word(const char *word_str) {
    switch (constexpr_hash(word_str)) {
#define X(name, str) case static_cast<std::underlying_type_t<WORD>>(WORD::name): return WORD::name;
        LIST_OF_WORDS(X)
#undef X
    }

    return WORD::ERROR;
}

template <typename...Args>
auto constexpr __do_nothing_return_last(Args&&...args) {
    // comma operator discards the result of the left
    //  must be in () because of it's low precedence
    //  calling a function with it gets rid of the 'no effect' warning so std::forward it is
    return (std::forward<Args>(args), ...);
}

#define MATH_OP_LIST(X)                     \
    X(+, int64_t, __builtin_add_overflow_p) \
    X(-, int64_t, __builtin_sub_overflow_p) \
    X(*, int64_t, __builtin_mul_overflow_p) \
    X(/, double , __do_nothing_return_last) \
    X(%, int64_t, __do_nothing_return_last) \

long double do_math_op(int64_t lhs = 2, int64_t rhs = 4, char oper = '%') {
   (void)__do_nothing_return_last(1,2,3);
    switch (oper) // doing the appropriate action according to the inputed operator
    {
#define X(op, type, overflow) \
    case #op[0]:              \
        return overflow(lhs, rhs, 0) ? 0 : (type)lhs op rhs; \
        std::cout << lhs << oper << rhs << "=" << (type)lhs op rhs << std::endl; \
        break;
        MATH_OP_LIST(X)
#undef X
        default:
            std::cout << "ERROR" << std::endl;
            break;    // unnecessary break for good measure :)
    }

    return 0;
}
