#ifndef _C0_COMPILE_SYMBOL_H_
#define _C0_COMPILE_SYMBOL_H_
#include <string.h>
#include <iostream>
#include <map>
#include <vector>
#include <string>
// #include <boost/variant.hpp>

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
        FUNC(PARAMETER) \

#define FOREACH_FUNC_SYMBOL_TYPE(FUNC) \
        FUNC(INT) \
        FUNC(CHAR) \
        FUNC(VOID) \

#define GENERATE_ENUM(ENUM) ENUM,
#define GENERATE_STRING(STRING) #STRING,

using std::string;
using std::pair;
using std::vector;
using std::map;

typedef int compile_errcode;

typedef enum _SymbolName {
    FOREACH_FUNC_SYMBOL(GENERATE_ENUM)
}SymbolName;

extern const char* symbol_name_string[];

extern map<string, SymbolName> keyword; 
namespace c0_compile{
class SymbolValue {
public:
    SymbolValue() {}
    explicit SymbolValue(int _value) {
        //value = _value;
        memcpy(&value, &_value, sizeof(int));
    }
    explicit SymbolValue(char _value) {
        //value = _value;
        memcpy(&value, &_value, sizeof(char));
    }
    explicit SymbolValue(const string& _value) {
        //value = _value;
        string_value = _value;
    }
    template<typename T>
    T GetValue() {
        // TODO check type T
        //return boost::get<T>(value);
        T ret;
        memcpy(&ret, &value, sizeof(T));
        return ret;
    }
    /*template<class T>
    T GetValue<T>() {
    }*/
private:
    typedef union {
        int int_value;
        char char_value;
    }Value;
    // boost::variant<int, char, string> value;
    Value value;
    string string_value;
};
    template<>
    string SymbolValue::GetValue<string>();
}  // namespace c0_compile

class Symbol {
public:
    Symbol() {}
    void SetName(SymbolName name) {
        m_name = name;
    }
    template<typename T>
    void SetValue(T value) {
        m_value = c0_compile::SymbolValue(value);
    }
    SymbolName GetName() {
        return m_name;
    }
    template<typename T>
    T GetValue() {
        return m_value.GetValue<T>();
    }
    int GetLine() {
        return m_line_number;
    }
    int GetCharacter() {
        return m_character_number;
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
    c0_compile::SymbolValue m_value;
    int m_line_number;
    int m_character_number;
};

typedef enum _SymbolKind {
    FOREACH_FUNC_SYMBOL_KIND(GENERATE_ENUM)
}SymbolKind;

typedef enum _SymbolType {
    FOREACH_FUNC_SYMBOL_TYPE(GENERATE_ENUM)
}SymbolType;

extern const char* symbol_kind_string[];
extern const char* symbol_type_string[];

template<class T>
struct DisableCompare : public std::binary_function<T, T, bool> {
    bool operator()(T left, T right) const {
        return false;
    }
};

class SymbolTableTerm {
public:
    SymbolTableTerm(string name, SymbolKind kind, SymbolName type_name) {
        m_name = name;
        m_kind = kind;
        if (type_name == INT_SYM)
            m_type = INT;
        else if (type_name == CHAR_SYM)
            m_type = CHAR;
        else if (type_name == VOID_SYM && kind == FUNCTION)
            m_type = VOID;
    }
    ~SymbolTableTerm();
    string GetName() {
        return m_name;
    }
    template<typename T>
    compile_errcode SetConstInformation(T value) {
        memcpy(&m_other_information, &value, sizeof(T));
    }
    void SetArrayInformation(int value) {
        m_other_information.array_length = value;
    }
    void SetFuncInformation(int value) {
        m_other_information.func_argument_number = value;
    }
    void PrintTerm();
private:
    string m_name;
    SymbolKind m_kind;
    SymbolType m_type;
    int m_relative_address;
    typedef union {
        int int_value;
        char char_value;
        int array_length;
        int func_argument_number;
    }Info;
    Info m_other_information;
};

class SymbolTable {
public:
    //SymbolTable(string name, string previous_level) : m_table_name(name), m_previous_level_name(previous_level) {}
    SymbolTable() {}
    SymbolTable(string name, string previous_level) {
        m_table_name = name;
        m_previous_level_name = previous_level;
    }
    bool Find(string name);
    compile_errcode Insert(SymbolTableTerm& term);
    string GetPreviousTableName() {
        return m_previous_level_name;
    }
    void PrintTable();
private:
    vector<pair<string, SymbolTableTerm>> m_symbol_table;
    string m_table_name;
    string m_previous_level_name;
};

class SymbolTableTree {
public:
    ~SymbolTableTree();
    compile_errcode CreateTable(string table_name, string previous_level_name);
    bool Find(string name, bool only_this_level);
    compile_errcode Insert(SymbolTableTerm& term);
    string GetCurrentPreviousTableName();
    string GetCurrentTableName() {
        return current_table_name;
    }
    void SetCurrentTableName(string name) {
        current_table_name = name;
    }
    void PrintTree();
private:
    vector<pair<string, SymbolTable>> m_table_tree;
    string current_table_name;
};
#endif // _C0_COMPILE_SYMBOL_H_
