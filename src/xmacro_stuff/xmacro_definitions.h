#pragma once

#include <iostream>
#include <cmath>
#include "Utils/constexpr_utils.h"

/** if i were to include this way instead of the above way, the mock wouldn't work
 *      and it would just go to the original code */
// #include "src/Utils/constexpr_utils.h"

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

#define MATH_OP_LIST(X)                     \
    X(+, int64_t, __builtin_add_overflow_p) \
    X(-, int64_t, __builtin_sub_overflow_p) \
    X(*, int64_t, __builtin_mul_overflow_p) \
    X(/, double , do_nothing_return_last  ) \
    X(%, int64_t, do_nothing_return_last  ) \

long double do_math_op(int64_t lhs = 2, int64_t rhs = 4, char oper = '%') {
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
