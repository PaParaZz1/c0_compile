#ifndef _C0_COMPILE_SYMBOL_H_
#define _C0_COMPILE_SYMBOL_H_
#include <map>
#include <string>
#include <boost/variant.hpp>

#define FOREACH_FUNC(FUNC) \
        FUNC(WHILE_SYM) \
        FUNC(SWITCH_SYM) \
        FUNC(IF_SYM) \
        FUNC(CASE_SYM) \
        FUNC(DEFAULT_SYM) \
        FUNC(RETURN_SYM) \
        FUNC(PRINTF_SYM) \
        FUNC(SCANF_SYM) \
        FUNC(INT_SYM) \
        FUNC(CHAR_SYM) \
        FUNC(VOID_SYM) \
        FUNC(ADD_SYM) \
        FUNC(SUB_SYM) \
        FUNC(MUL_SYM) \
        FUNC(DIV_SYM) \
        FUNC(ASSIGN_SYM) \
        FUNC(EQUAL_SYM) \
        FUNC(NOT_EQUAL_SYM) \
        FUNC(SMALL_SYM) \
        FUNC(SMALL_EQUAL_SYM) \
        FUNC(LARGE_SYM) \
        FUNC(LARGE_EQUAL_SYM) \
        FUNC(CONST_SYM) \
        FUNC(COMMA_SYM) \
        FUNC(SEMICOLON_SYM) \
        FUNC(COLON_SYM) \
        FUNC(L_CIRCLE_BRACKET_SYM) \
        FUNC(L_SQUARE_BRACKET_SYM) \
        FUNC(L_CURLY_BRACKET_SYM) \
        FUNC(R_CIRCLE_BRACKET_SYM) \
        FUNC(R_SQUARE_BRACKET_SYM) \
        FUNC(R_CURLY_BRACKET_SYM) \
        FUNC(CHARACTER_SYM) \
        FUNC(STRING_SYM) \
        FUNC(IDENTITY_SYM) \
        FUNC(SINGLE_QUOTE_SYM) \
        FUNC(DOUBLE_QUOTE_SYM) \
        FUNC(INTERGER_SYM) \
        FUNC(EOF_SYM) \
        FUNC(MAIN_SYM) \

#define GENERATE_ENUM(ENUM) ENUM,
#define GENERATE_STRING(STRING) #STRING,

typedef enum _SymbolName {
    FOREACH_FUNC(GENERATE_ENUM)
}SymbolName;

extern const char* symbol_name_string[];

extern std::map<std::string, SymbolName> keyword; 

class SymbolValue {
public:
    SymbolValue() {}
    explicit SymbolValue(int _value) {
        value = _value;
    }
    explicit SymbolValue(char _value) {
        value = _value;
    }
    explicit SymbolValue(const std::string& _value) {
        value = _value;
    }
    template<typename T>
    T GetValue() {
        // TODO check type T
        return boost::get<T>(value);
    }
private:
    boost::variant<int, char, std::string> value;
};

class Symbol {
public:
    Symbol() {}
    void SetName(SymbolName _name) {
        this->name = _name;
    }
    template<typename T>
    void SetValue(T _value) {
        value = SymbolValue(_value);
    }
    SymbolName GetName() {
        return this->name;
    }
    template<typename T>
    T GetValue() {
        return value.GetValue<T>();
    }
private:
    SymbolName name;
    SymbolValue value;
};

#endif // _C0_COMPILE_SYMBOL_H_
