#ifndef _C0_COMPILE_SYMBOL_H_
#define _C0_COMPILE_SYMBOL_H_
#include <map>
#include <string>
#include <vector>
#include <boost/variant.hpp>

#define FOREACH_FUNC_SYMBOL(FUNC) \
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
        FUNC(IDENTIFIER_SYM) \
        FUNC(SINGLE_QUOTE_SYM) \
        FUNC(DOUBLE_QUOTE_SYM) \
        FUNC(INTERGER_SYM) \
        FUNC(EOF_SYM) \
        FUNC(MAIN_SYM) \

#define FOREACH_FUNC_SYMBOL_KIND(FUNC) \
        FUNC(CONST) \
        FUNC(VARIABLE) \
        FUNC(ARRAY) \
        FUNC(FUNCTION) \

#define FOREACH_FUNC_SYMBOL_TYPE(FUNC) \
        FUNC(INT) \
        FUNC(CHAR) \

#define GENERATE_ENUM(ENUM) ENUM,
#define GENERATE_STRING(STRING) #STRING,

typedef int compile_errcode;

typedef enum _SymbolName {
    FOREACH_FUNC_SYMBOL(GENERATE_ENUM)
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
    void SetName(SymbolName name) {
        m_name = name;
    }
    template<typename T>
    void SetValue(T value) {
        m_value = SymbolValue(value);
    }
    SymbolName GetName() {
        return m_name;
    }
    template<typename T>
    T GetValue() {
        return m_value.GetValue<T>();
    }
    void SetLocate(int line_number, int character_number) {
        this->SetLineNumber(line_number);
        this->SetCharacterNumber(character_number);
    }
    void SetLineNumber(int line_number) {
        m_line_number = line_number;
    }
    void SetCharacterNumber(int character_number) {
        m_character_number = character_number;
    }
private:
    SymbolName m_name;
    SymbolValue m_value;
    int m_line_number;
    int m_character_number;
};

typedef enum _SymbolKind {
    FOREACH_FUNC_SYMBOL_KIND(GENERATE_ENUM)
}SymbolKind;

typedef enum _SymbolType {
    FOREACH_FUNC_SYMBOL_TYPE(GENERATE_ENUM)
}SymbolType;

typedef struct _SymbolTableKey {
    std::string name;
    int level;
}SymbolTableKey;

class SymbolTableTerm {
public:
    SymbolTableTerm() {}
private:
    std::string name;
    int level;
    SymbolKind kind;
    std::string type;
};

class SymbolTable {
public:
    SymbolTable() {}
    bool Find(std::string name) {return true;}
    compile_errcode Insert(SymbolTableTerm term);
private:
    std::vector<SymbolTableTerm> m_symbol_table;
    SymbolTable* m_previous_level_ptr;
    std::string m_table_name;
};

extern SymbolTable* handle_symbol_table;
#endif // _C0_COMPILE_SYMBOL_H_
