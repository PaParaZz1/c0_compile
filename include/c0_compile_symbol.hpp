#ifndef _C0_COMPILE_SYMBOL_H_
#define _C0_COMPILE_SYMBOL_H_
#include <string.h>
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <utility>
#include "c0_compile_utils.hpp"
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
namespace c0_compile {
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
        else
            fprintf(stderr, "invalid type name\n");
    }
    ~SymbolTableTerm();
    string GetName() {
        return m_name;
    }
    SymbolType GetType() {
        return m_type;
    }
    SymbolKind GetKind() {
        return m_kind;
    }
    int GetRelativeAddr() {
        return m_relative_address;
    }
    int GetAbsoluteAddr() {
        return m_absolute_address;
    }
    template<typename T>
    compile_errcode SetConstInformation(T value) {
        memcpy(&m_other_information, &value, sizeof(T));
        return COMPILE_OK;
    }
    void SetArrayInformation(int value) {
        m_other_information.array_length = value;
    }
    void SetFuncInformation(int value) {
        m_other_information.func_argument_number = value;
    }
    void SetAddress(int relative_address, int base_address) {
        m_relative_address = relative_address;
        m_absolute_address = base_address + relative_address;
    }
    int GetArrayInformation() {
        return m_other_information.array_length;
    }
    int GetValueInformation() {
        if (m_type == CHAR) {
            return static_cast<int>(m_other_information.char_value);
        } else {
            return m_other_information.int_value;
        }
    }
    void PrintTerm();
private:
    string m_name;
    SymbolKind m_kind;
    SymbolType m_type;
    int m_relative_address;
    int m_absolute_address;
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
    SymbolTable(string name, SymbolType type, string previous_level) {
        m_table_name = name;
        m_table_type = type;
        m_previous_level_name = previous_level;
    }
    bool Find(string name);
    compile_errcode Insert(SymbolTableTerm& term);
    string GetPreviousTableName() {
        return m_previous_level_name;
    }
    compile_errcode GetTermType(string name, SymbolType& type);
    compile_errcode GetTermKind(string name, SymbolKind& kind);
    compile_errcode GetTermIntValue(string name, int& value);
    compile_errcode GetAddress(string name, int& addr);
    void GetTableType(SymbolType& type) {
        type = m_table_type;
    }
    int GetTableBaseAddr() {
        return m_table_base_address;
    }
    int GetTableSpace() {
        return m_table_address_length;
    }
    void SetAddress(int base_address) {
        m_table_base_address = base_address;
        m_table_address_length = 0;
    }
    void PrintTable();
private:
    vector<pair<string, SymbolTableTerm> > m_symbol_table;
    string m_table_name;
    string m_previous_level_name;
    SymbolType m_table_type;
    int m_table_base_address;
    int m_table_address_length;
    compile_errcode GetTerm(string name, vector<pair<string, SymbolTableTerm> >::iterator& iter);
};

class SymbolTableTree {
public:
    SymbolTableTree() {
        m_tree_address_length = 0;
    }
    ~SymbolTableTree();
    compile_errcode CreateTable(string table_name, SymbolType type, string previous_level_name);
    bool Find(string name, bool only_this_level);
    compile_errcode Insert(SymbolTableTerm& term);
    string GetCurrentPreviousTableName();
    string GetCurrentTableName() {
        return current_table_name;
    }
    compile_errcode GetCurrentTableType(SymbolType& type);
    compile_errcode GetTermType(string name, SymbolType& type);
    compile_errcode GetTermType(string current_table_name, string name, SymbolType& type);
    compile_errcode GetTermKind(string name, SymbolKind& kind);
    compile_errcode GetTermKind(string current_table_name, string name, SymbolKind& kind);
    compile_errcode GetTermIntValue(string current_table_name, string name, int& value);
    compile_errcode GetAddressStringInterface(string name, string& address_string);
    compile_errcode GetAddressStringInterface(string current_table_name, string name, string& address_string);
    void SetCurrentTableName(string name) {
        current_table_name = name;
    }
    void GetTableSpaceLength(string name, int& length);
    void UpgradeAddress();
    void PrintTree();
private:
    vector<pair<string, SymbolTable> > m_table_tree;
    string current_table_name;
    int m_tree_address_length;
    compile_errcode GetAddressString(string current_table_name, string name, string& address_string);
};

class FunctionTableTerm {
public:
    FunctionTableTerm(string func_name,
                      int space_length,
                      int argument_number,
                      int return_value_number) :
    m_func_name(func_name), m_space_length(space_length) {
        m_argument_space_length = 4 * argument_number;
        m_return_value_space_length = 4 * return_value_number;
    }
    void GetTopLabel(string& top_label) const {
        top_label = m_top_label;
    }
    void GetBottomLabel(string& bottom_label) const {
        bottom_label = m_bottom_label;
    }
    void GetName(string& name) const {
        name = m_func_name;
    }
    void GetSpaceLength(int& space_length) const {
        space_length = m_space_length;
    }
    void SetTopLabel(const string& top_label) {
        m_top_label = top_label;
    }
    void SetBottomLabel(const string& bottom_label) {
        m_bottom_label = bottom_label;
    }
    void PrintTerm();
private:
    string m_func_name;
    string m_top_label;
    string m_bottom_label;
    int m_argument_space_length;
    int m_return_value_space_length;
    int m_space_length;
};

class FunctionTable {
public:
    FunctionTable() {
        m_current_term_ptr = -1;
    }
    void InsertTerm(string func_name, int space_length, int argument_number, int return_value_number);
    bool Find(string func_name);
    void GetTermTopLabel(const string& term_name, string& top_label);
    void GetCurrentTermTopLabel(string& top_label);
    void GetTermBottomLabel(const string& term_name, string& bottom_label);
    void GetCurrentTermBottomLabel(string& bottom_label);
    void GetTermSpaceLength(string func_name, int& space_length);
    void PrintAllTerm();
    void SetTermTopLabel(const string& func_name, const string& top_label);
    void SetTermBottomLabel(const string& func_name, const string& bottom_label);
private:
    vector<FunctionTableTerm> m_func_table;
    int m_current_term_ptr;
};

#endif // _C0_COMPILE_SYMBOL_H_
