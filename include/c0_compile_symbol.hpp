#ifndef _C0_COMPILE_SYMBOL_H_
#define _C0_COMPILE_SYMBOL_H_
#include <string.h>
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <utility>
#include "c0_compile_utils.hpp"

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

typedef enum _SymbolKind {
    FOREACH_FUNC_SYMBOL_KIND(GENERATE_ENUM)
}SymbolKind;

typedef enum _SymbolType {
    FOREACH_FUNC_SYMBOL_TYPE(GENERATE_ENUM)
}SymbolType;

extern const char* symbol_name_string[];
extern const char* symbol_kind_string[];
extern const char* symbol_type_string[];

extern map<string, SymbolName> keyword;

namespace c0_compile {
class SymbolValue {
public:
    SymbolValue() {}
    explicit SymbolValue(int _value) {
        memcpy(&value, &_value, sizeof(int));
    }
    explicit SymbolValue(char _value) {
        memcpy(&value, &_value, sizeof(char));
    }
    explicit SymbolValue(const string& _value) {
        string_value = _value;
    }
    template<typename T>
    T GetValue() const {
        // TODO check type T
        T ret;
        memcpy(&ret, &value, sizeof(T));
        return ret;
    }
private:
    typedef union {
        int int_value;
        char char_value;
    }Value;
    Value value;
    string string_value;
};
    template<>
    string SymbolValue::GetValue<string>() const;
}  // namespace c0_compile

class Symbol {
public:
    Symbol() {}
    void SetName(const SymbolName& name) {
        m_name = name;
    }
    template<typename T>
    void SetValue(T value) {
        m_value = c0_compile::SymbolValue(value);
    }
    SymbolName GetName() const {
        return m_name;
    }
    template<typename T>
    T GetValue() const {
        return m_value.GetValue<T>();
    }
    int GetLine() const {
        return m_line_number;
    }
    int GetCharacter() const {
        return m_character_number;
    }
    void SetLocate(int line_number, int character_number) {
        this->SetLineNumber(line_number);
        this->SetCharacterNumber(character_number);
    }
private:
    SymbolName m_name;
    c0_compile::SymbolValue m_value;
    int m_line_number;
    int m_character_number;
    void SetLineNumber(int line_number) {
        m_line_number = line_number;
    }
    void SetCharacterNumber(int character_number) {
        m_character_number = character_number;
    }
};


template<class T>
struct DisableCompare : public std::binary_function<T, T, bool> {
    bool operator()(T left, T right) const {
        return false;
    }
};

class SymbolTableTerm {
public:
    SymbolTableTerm() {}
    SymbolTableTerm(const string& name, const SymbolKind& kind, const SymbolName& type_name) : m_name(name), m_kind(kind) {
        switch (type_name) {
            case INT_SYM: m_type = INT; break;
            case CHAR_SYM: m_type = CHAR; break;
            case VOID_SYM: {
                               if (kind == FUNCTION) {
                                   m_type = VOID;
                                   break;
                               } else {
                                   fprintf(stderr, "invalid type name: %s\n", symbol_name_string[type_name]);
                                   break;
                               }
                           }
            default:
                    fprintf(stderr, "invalid type name: %s\n", symbol_name_string[type_name]);
        }
    }
    ~SymbolTableTerm();
    string GetName() const {
        return m_name;
    }
    SymbolType GetType() const {
        return m_type;
    }
    SymbolKind GetKind() const {
        return m_kind;
    }
    int GetRelativeAddr() const {
        return m_relative_address;
    }
    int GetAbsoluteAddr() const {
        return m_absolute_address;
    }
    template<typename T>
    compile_errcode SetConstInformation(T value) {
        // (TODO) check T type
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
    int GetArrayInformation() const {
        return m_other_information.array_length;
    }
    int GetValueInformation() const {
        if (m_type == CHAR) {
            return static_cast<int>(m_other_information.char_value);
        } else if (m_type == INT) {
            return m_other_information.int_value;
        } else {
            fprintf(stderr, "invalid m_type: %s\n", symbol_type_string[m_type]);
            return NOT_DEFINED_ERROR;
        }
    }
    void PrintTerm() const;
private:
    string m_name;
    SymbolKind m_kind;
    SymbolType m_type;
    int m_relative_address;
    int m_absolute_address;
    typedef union _Info{
        int int_value;
        char char_value;
        int array_length;
        int func_argument_number;
    }Info;
    Info m_other_information;
};

class SymbolTable {
public:
    SymbolTable() {}
    SymbolTable(const string& name, const SymbolType& type, const string& previous_level_name, int base_address) 
        : m_table_name(name), m_table_type(type), m_previous_level_name(previous_level_name), m_table_base_address(base_address) {
            m_table_address_length = 0;
        }
    string GetPreviousTableName() const {
        return m_previous_level_name;
    }
    SymbolType GetTableType() const {
        return m_table_type;
    }
    int GetTableBaseAddr() const {
        return m_table_base_address;
    }
    int GetTableSpace() const {
        return m_table_address_length;
    }
    compile_errcode GetTermType(const string& name, SymbolType& type) const;
    compile_errcode GetTermKind(const string& name, SymbolKind& kind) const;
    compile_errcode GetTermIntValue(const string& name, int& value) const;
    compile_errcode GetAddress(const string& name, int& addr) const;
    compile_errcode GetArraySpace(const string& name, int& array_length) const;
    bool Find(const string& name) const;
    compile_errcode Insert(SymbolTableTerm& term);
    void PrintTable() const;
private:
    vector<pair<string, SymbolTableTerm> > m_symbol_table;
    string m_table_name;
    string m_previous_level_name;
    SymbolType m_table_type;
    int m_table_base_address;
    int m_table_address_length;
    compile_errcode GetTerm(const string& name, SymbolTableTerm& term) const;
    compile_errcode GetTermIter(const string& name, vector<pair<string, SymbolTableTerm> >::iterator& iter);
};

class SymbolTableTree {
public:
    SymbolTableTree() {
        m_tree_address_length = 0;
    }
    ~SymbolTableTree();
    void InsertTable(const string& table_name, const SymbolType& type, const string& previous_level_name);
    bool FindTerm(const string& name, bool only_this_level) const;
    bool MatchKeyword(const string& name);
    compile_errcode Insert(SymbolTableTerm& term);
    string GetCurrentTableName() const {
        return current_table_name;
    }
    void SetCurrentTableName(const string& name) {
        current_table_name = name;
    }
    string GetCurrentPreviousTableName() const;
    SymbolType GetCurrentTableType() const;
    compile_errcode GetTableSpaceLength(const string& table_name, int& length);

    compile_errcode GetTermKindInterface(const string& name, SymbolKind& kind);
    compile_errcode GetTermKindInterface(const string& cur_table_name, const string& name, SymbolKind& kind);
    compile_errcode GetTermTypeInterface(const string& name, SymbolType& kind);
    compile_errcode GetTermTypeInterface(const string& cur_table_name, const string& name, SymbolType& Type);
    compile_errcode GetArraySpaceInterface(const string& name, int& array_space);
    compile_errcode GetArraySpaceInterface(const string& cur_table_name, const string& name, int& array_space);
    compile_errcode GetTermIntValueInterface(const string& name, int& value);
    compile_errcode GetTermIntValueInterface(const string& cur_table_name, const string& name, int& value);
    compile_errcode GetAddressStringInterface(const string& name, string& address_string);
    compile_errcode GetAddressStringInterface(const string& cur_table_name, const string& name, string& address_string);
    void UpgradeAddress();
    void PrintTree() const;
private:
    const string m_BOTTOM_LEVEL = string("end");
    vector<pair<string, SymbolTable> > m_table_tree;
    string current_table_name;
    int m_tree_address_length;
    compile_errcode GetAddressString(const string& begin_table_name, const string& name, string& address_string);
    compile_errcode GetTermKind(const string& begin_table_name, const string& name, SymbolKind& kind);
    compile_errcode GetTermType(const string& begin_table_name, const string& name, SymbolType& type);
    compile_errcode GetArraySpace(const string& begin_table_name, const string& name, int& array_space);
    compile_errcode GetTermIntValue(const string& begin_table_name, const string& name, int& value);
};

class FunctionTableTerm {
public:
    FunctionTableTerm(string func_name,
                      int space_length,
                      int argument_number,
                      int return_value_number,
                      const vector<SymbolType>& argument_type) :
    m_func_name(func_name), m_space_length(space_length), m_argument_type(argument_type) {
        m_argument_space_length = 4 * argument_number;
        m_return_value_space_length = 4 * return_value_number;
    }
    string GetTopLabel() const {
        return m_top_label;
    }
    string GetBottomLabel() const {
        return m_bottom_label;
    }
    string GetName() const {
        return m_func_name;
    }
    int GetSpaceLength() const {
        return m_space_length;
    }
    vector<SymbolType> GetArgumentType() const {
        return m_argument_type;
    }
    void SetTopLabel(const string& top_label) {
        m_top_label = top_label;
    }
    void SetBottomLabel(const string& bottom_label) {
        m_bottom_label = bottom_label;
    }
    void PrintTerm() const;
private:
    string m_func_name;
    string m_top_label;
    string m_bottom_label;
    int m_argument_space_length;
    int m_return_value_space_length;
    int m_space_length;
    vector<SymbolType> m_argument_type;
};

class FunctionTable {
public:
    FunctionTable() {
        m_current_term_ptr = -1;
    }
    ~FunctionTable() {}
    void InsertTerm(const string& func_name, int space_length, int return_value_number, const vector<SymbolType>& argument_type);
    bool Find(const string& func_name);
    void GetCurrentTermTopLabel(string& top_label) const;
    void GetCurrentTermBottomLabel(string& bottom_label) const ;
    compile_errcode GetTermTopLabel(const string& term_name, string& top_label) const;
    compile_errcode GetTermBottomLabel(const string& term_name, string& bottom_label) const;
    compile_errcode GetTermSpaceLength(const string& term_name, int& space_length) const ;
    compile_errcode GetTermArgumentType(const string& term_name, vector<SymbolType>& argument_type) const;
    void SetTermTopLabel(const string& func_name, const string& top_label);
    void SetTermBottomLabel(const string& func_name, const string& bottom_label);
    void PrintAllTerm() const;
private:
    vector<FunctionTableTerm> m_func_table;
    int m_current_term_ptr;
};

#endif // _C0_COMPILE_SYMBOL_H_
