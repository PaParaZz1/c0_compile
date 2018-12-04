#include <string.h>
#include <stdio.h>
#include <algorithm>
#include "c0_compile_symbol.hpp"
#include "c0_compile_utils.hpp"
using std::string;
using std::map;
using std::vector;
using std::pair;
#define BOTTOM_LEVEL "end"


const char* symbol_name_string[] = {
    FOREACH_FUNC_SYMBOL(GENERATE_STRING)
};
const char* symbol_kind_string[] = {
    FOREACH_FUNC_SYMBOL_KIND(GENERATE_STRING)
};
const char* symbol_type_string[] = {
    FOREACH_FUNC_SYMBOL_TYPE(GENERATE_STRING)
};

FILE* fp_symbol = fopen("symbol_log.txt", "w");
//FILE* fp_symbol = stdout;

map<string, SymbolName> keyword = {
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

SymbolTableTerm::~SymbolTableTerm() {
    /*if (m_other_information != NULL) {
        delete m_other_information;
    }*/
}
namespace c0_compile {
    template<>
    string SymbolValue::GetValue<string>() {
        return string_value;
    }
} // namespace c0_compile

void SymbolTableTerm::PrintTerm() {
    fprintf(fp_symbol, "{\n name: %s\n", m_name.c_str());
    fprintf(fp_symbol, " kind: %s\n", symbol_kind_string[m_kind]);
    fprintf(fp_symbol, " type: %s\n", symbol_type_string[m_type]);
    switch (m_kind) {
        case CONST: {
            if (m_type == INT)
                fprintf(fp_symbol, " const int value: %d\n", m_other_information.int_value);
            else if (m_type == CHAR)
                fprintf(fp_symbol, " const char value: %c\n", m_other_information.char_value);
            break;
        }
        case ARRAY: {
            fprintf(fp_symbol, " array length: %d\n", m_other_information.array_length);
            break;
        }
        case FUNCTION: {
            fprintf(fp_symbol, " function parameter number: %d\n", m_other_information.func_argument_number);
            break;
        }
        default: {}
    }
    fprintf(fp_symbol, "}\n");
}

bool SymbolTable::Find(string name) {
    auto iter = m_symbol_table.begin();
    for (; iter != m_symbol_table.end(); ++iter) {
        if (iter->first == name)
            return true;
    }
    return false;
}

compile_errcode SymbolTable::Insert(SymbolTableTerm& term) {
    auto name = term.GetName();
    if (this->Find(name)) {
        return REPEAT_DEFINITION_IDENTIFIER;
    } else {
        // m_symbol_table.insert(map<string, SymbolTableTerm>::value_type(name, term));
        pair<string, SymbolTableTerm> pair_term(name, term);
        m_symbol_table.push_back(pair_term);
        return COMPILE_OK;
    }
}

void SymbolTable::PrintTable() {
    fprintf(fp_symbol, "-------------------------------------------------\n");
    fprintf(fp_symbol, "function %s's symbol table\n", m_table_name.c_str());
    auto iter = m_symbol_table.begin();
    for (; iter != m_symbol_table.end(); ++iter) {
        iter->second.PrintTerm();
    }
    fprintf(fp_symbol, "-------------------------------------------------\n");
}

compile_errcode SymbolTable::GetTerm(string name, SymbolTableTerm* term_ptr) {
    auto iter = m_symbol_table.begin();
    for (; iter != m_symbol_table.end(); ++iter) {
        if (iter->first == name) {
            term_ptr = &(iter->second);
            return COMPILE_OK;
        }
    }
    return UNDEFINED_SYMBOL_TERM;
}

compile_errcode SymbolTable::GetTermType(string name, SymbolType& type) {
    SymbolTableTerm* term_ptr = NULL;
    int ret = COMPILE_OK;
    if ((ret = this->GetTerm(name, term_ptr)) != COMPILE_OK) {
        return ret;
    } else {
        type = term_ptr->GetType();
        return COMPILE_OK;
    }
}

SymbolTableTree::~SymbolTableTree() {
}

compile_errcode SymbolTableTree::CreateTable(string table_name, string previous_level) {
    auto table = SymbolTable(table_name, previous_level);
    pair<string, SymbolTable> pair_term(table_name, table);
    m_table_tree.push_back(pair_term);
    // m_table_tree.insert(map<string, SymbolTable>::value_type(table_name, table));
}

compile_errcode SymbolTableTree::Insert(SymbolTableTerm& term) {
    string table_name = this->GetCurrentTableName();
    auto iter = m_table_tree.begin();
    for(; iter != m_table_tree.end(); ++iter) {
        if (iter->first == table_name)
            break;
    }
    return iter->second.Insert(term);
}

bool SymbolTableTree::Find(string name, bool only_this_level) {
    string current_table_name = this->GetCurrentTableName();
    do {
        auto iter = m_table_tree.begin();
        for (; iter != m_table_tree.end(); ++iter) {
            if (iter->first == current_table_name)
                break;
        }
        if (iter == m_table_tree.end()) {
            fprintf(stderr, "invalid table name: %s\n", current_table_name.c_str());
            return false;
        }
        SymbolTable current_table = iter->second;
        if (current_table.Find(name)) {
            return true;
        } else {
            current_table_name = current_table.GetPreviousTableName();
        }
    } while (!only_this_level && strcmp(current_table_name.c_str(), BOTTOM_LEVEL) != 0);
    return false;
}

string SymbolTableTree::GetCurrentPreviousTableName() {
    for (auto iter=m_table_tree.begin(); iter != m_table_tree.end(); ++iter) {
        if (iter->first == current_table_name)
            return iter->second.GetPreviousTableName();
    }
    return string("Bug++");
}

void SymbolTableTree::PrintTree() {
    auto iter = m_table_tree.begin();
    for (; iter != m_table_tree.end(); ++iter) {
        (iter->second).PrintTable();
    }
}

compile_errcode SymbolTableTree::GetTermType(string name, SymbolType& type) {
    int ret = COMPILE_OK;
    string current_table_name = this->GetCurrentTableName();
    do {
        auto iter = m_table_tree.begin();
        for (; iter != m_table_tree.end(); ++iter) {
            if (iter->first == current_table_name) {
                break;
            }
        }
        if ((ret = iter->second.GetTermType(name, type)) != COMPILE_OK) {
            current_table_name = iter->second.GetPreviousTableName();
        } else {
            return COMPILE_OK;
        }
    } while (strcmp(current_table_name.c_str(), BOTTOM_LEVEL) != 0);
    return ret;
}

SymbolTableTree* symbol_table_tree;
