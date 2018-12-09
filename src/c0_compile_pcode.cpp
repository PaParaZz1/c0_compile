#include <c0_compile_pcode.hpp>

const char* pcode_string[] = {
    FOREACH_FUNC_PCODE(GENERATE_STRING)
};
