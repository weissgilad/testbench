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

#define MATH_OP_LIST(X) \
    X(+, int64_t  )     \
    X(-, int64_t  )     \
    X(*, int64_t  )     \
    X(/, double   )     \
    X(%, int64_t  )     \

long double do_math_op() {

    int num1 = 2, num2 = 4;    // hardcoded input numbers
    char oper = '%';

    switch (oper) // doing the appropriate action according to the inputed operator
    {
#define X(op, type) \
    case #op[0]:    \
        return (type)num1 op num2; \
        std::cout << num1 << oper << num2 << "=" << (type)num1 op num2 << std::endl; \
        break;
        MATH_OP_LIST(X)
#undef X
        default:
            std::cout << "ERROR" << std::endl;
            break;    // unnecessary break for good measure :)
    }

    return 0;
}
