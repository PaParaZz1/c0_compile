#include "c0_compile_symbol.hpp"
const char* symbol_name_string[] = {
    FOREACH_FUNC(GENERATE_STRING)
};

std::map<std::string, SymbolName> keyword = {
    {"while", WHILE_SYM},
    {"if", IF_SYM},
    {"switch", SWITCH_SYM},
    {"case", CASE_SYM},
    {"void", VOID_SYM},
    {"default", DEFAULT_SYM},
    {"int", INT_SYM},
    {"char", CHAR_SYM},
    {"return", RETURN_SYM},
    {"const", CONST_SYM},
    {"scanf", SCANF_SYM},
    {"printf", PRINTF_SYM},
    {"main", MAIN_SYM}
};
