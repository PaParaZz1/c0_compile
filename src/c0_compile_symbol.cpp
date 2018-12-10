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
// FILE* fp_symbol = stdout;

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
    if (m_kind != FUNCTION)
        fprintf(fp_symbol, " relative addr: 0x%04x\n", m_relative_address);
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
        SymbolKind kind = term.GetKind();
        term.SetAddress(m_table_address_length, m_table_base_address);
        pair<string, SymbolTableTerm> pair_term(name, term);
        switch (kind) {
            case FUNCTION:break;
            case ARRAY: {
                int number = term.GetArrayInformation();
                m_table_address_length += 4*number;
                break;
            }
            default: m_table_address_length += 4;
        }
        m_symbol_table.push_back(pair_term);
        return COMPILE_OK;
    }
}

void SymbolTable::PrintTable() {
    fprintf(fp_symbol, "-------------------------------------------------\n");
    fprintf(fp_symbol, "function %s's symbol table\n", m_table_name.c_str());
    fprintf(fp_symbol, "function type: %s\n", symbol_type_string[m_table_type]);
    auto iter = m_symbol_table.begin();
    for (; iter != m_symbol_table.end(); ++iter) {
        iter->second.PrintTerm();
    }
    fprintf(fp_symbol, "-------------------------------------------------\n");
}

compile_errcode SymbolTable::GetTerm(string name, vector<pair<string, SymbolTableTerm>>::iterator& iter) {
    iter = m_symbol_table.begin();
    for (; iter != m_symbol_table.end(); ++iter) {
        if (iter->first == name) {
            return COMPILE_OK;
        }
    }
    return UNDEFINED_SYMBOL_TERM;
}

compile_errcode SymbolTable::GetTermType(string name, SymbolType& type) {
    int ret = COMPILE_OK;
    vector<pair<string, SymbolTableTerm>>::iterator iter;
    if ((ret = this->GetTerm(name, iter)) != COMPILE_OK) {
        return ret;
    } else {
        type = iter->second.GetType();
        return COMPILE_OK;
    }
}

compile_errcode SymbolTable::GetTermKind(string name, SymbolKind& kind) {
    int ret = COMPILE_OK;
    vector<pair<string, SymbolTableTerm>>::iterator iter;
    if ((ret = this->GetTerm(name, iter)) != COMPILE_OK) {
        return ret;
    } else {
        kind = iter->second.GetKind();
        return COMPILE_OK;
    }
}

compile_errcode SymbolTable::GetTermIntValue(string name, int& value) {
    int ret = COMPILE_OK;
    vector<pair<string, SymbolTableTerm>>::iterator iter;
    if ((ret = this->GetTerm(name, iter)) != COMPILE_OK) {
        return ret;
    } else {
        value = iter->second.GetValueInformation();
        return COMPILE_OK;
    }
}

compile_errcode SymbolTable::GetAddress(string name, int& addr) {
    int ret = COMPILE_OK;
    vector<pair<string, SymbolTableTerm>>::iterator iter;
    if ((ret = this->GetTerm(name, iter)) != COMPILE_OK) {
        return ret;
    } else {
        addr = iter->second.GetRelativeAddr();
        return COMPILE_OK;
    }
}

SymbolTableTree::~SymbolTableTree() {
}

compile_errcode SymbolTableTree::CreateTable(string table_name, SymbolType type, string previous_level) {
    auto table = SymbolTable(table_name, type, previous_level);
    table.SetAddress(m_tree_address_length);
    pair<string, SymbolTable> pair_term(table_name, table);
    m_table_tree.push_back(pair_term);
    return COMPILE_OK;
}

compile_errcode SymbolTableTree::Insert(SymbolTableTerm& term) {
    string table_name = this->GetCurrentTableName();
    auto iter = m_table_tree.begin();
    for (; iter != m_table_tree.end(); ++iter) {
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

compile_errcode SymbolTableTree::GetTermKind(string name, SymbolKind& kind) {
    int ret = COMPILE_OK;
    string current_table_name = this->GetCurrentTableName();
    do {
        auto iter = m_table_tree.begin();
        for (; iter != m_table_tree.end(); ++iter) {
            if (iter->first == current_table_name) {
                break;
            }
        }
        if ((ret = iter->second.GetTermKind(name, kind)) != COMPILE_OK) {
            current_table_name = iter->second.GetPreviousTableName();
        } else {
            return COMPILE_OK;
        }
    } while (strcmp(current_table_name.c_str(), BOTTOM_LEVEL) != 0);
    return ret;
}

compile_errcode SymbolTableTree::GetTermIntValue(string name, int& value) {
    int ret = COMPILE_OK;
    string current_table_name = this->GetCurrentTableName();
    do {
        auto iter = m_table_tree.begin();
        for (; iter != m_table_tree.end(); ++iter) {
            if (iter->first == current_table_name) {
                break;
            }
        }
        if ((ret = iter->second.GetTermIntValue(name, value)) != COMPILE_OK) {
            current_table_name = iter->second.GetPreviousTableName();
        } else {
            return COMPILE_OK;
        }
    } while (strcmp(current_table_name.c_str(), BOTTOM_LEVEL) != 0);
    return ret;
}

compile_errcode SymbolTableTree::GetCurrentTableType(SymbolType& type) {
    string current_table_name = this->GetCurrentTableName();
    auto iter = m_table_tree.begin();
    for (; iter != m_table_tree.end(); ++iter) {
        if (iter->first == current_table_name) {
            break;
        }
    }
    if (iter == m_table_tree.end()) {
        return -2;
    }
    iter->second.GetTableType(type);
    return COMPILE_OK;
}

void SymbolTableTree::UpgradeAddress() {
    string current_table_name = this->GetCurrentTableName();
    auto iter = m_table_tree.begin();
    for (; iter != m_table_tree.end(); ++iter) {
        if (iter->first == current_table_name)
            break;
    }
    if (iter != m_table_tree.end()) {  // there is at least a table in tree
        m_tree_address_length += iter->second.GetTableSpace();
    }
}

compile_errcode SymbolTableTree::GetAddressString(string name, string& address_string) {
    string current_table_name = this->GetCurrentTableName();
    auto iter = m_table_tree.begin();
    int addr;
    int ret = COMPILE_OK;
    do {
        auto iter = m_table_tree.begin();
        for (; iter != m_table_tree.end(); ++iter) {
            if (iter->first == current_table_name) {
                break;
            }
        }
        if ((ret = iter->second.GetAddress(name, addr)) != COMPILE_OK) {
            current_table_name = iter->second.GetPreviousTableName();
        } else {
            if (current_table_name != string("global")) {
                address_string = string("sp") + std::to_string(addr);
            } else {
                int base_addr = 0;
                address_string = std::to_string(addr + base_addr);
            }
            return COMPILE_OK;
        }
    } while (strcmp(current_table_name.c_str(), BOTTOM_LEVEL) != 0);
    return COMPILE_OK;
}

void FunctionTableTerm::PrintTerm() {
    fprintf(fp_symbol, "--------------------------------------");
    fprintf(fp_symbol, "function\nname: %s\ntop label: %s\nbottom label: %s\nargument space: %d\nreturn value space: %d\n",
    m_func_name.c_str(), m_top_label.c_str(), m_bottom_label.c_str(), m_argument_space_length, m_return_value_space_length);
}
void FunctionTable::InsertTerm(string func_name,
                               string top_label,
                               string bottom_label,
                               int argument_number,
                               int return_value_number) {
    FunctionTableTerm term(func_name, top_label, bottom_label, argument_number, return_value_number);
    m_func_table.push_back(term);
    m_current_term_ptr++;
}

bool FunctionTable::Find(string func_name) {
    for (FunctionTableTerm term: m_func_table) {
        string tmp;
        term.GetName(tmp);
        if (tmp == func_name) {
            return true;
        }
    }
    return false;
}

void FunctionTable::GetCurrentTermTopLabel(string& top_label) {
    m_func_table[m_current_term_ptr].GetTopLabel(top_label);
}

void FunctionTable::GetCurrentTermBottomLabel(string& bottom_label) {
    m_func_table[m_current_term_ptr].GetBottomLabel(bottom_label);
}

void FunctionTable::GetTermTopLabel(string term_name, string& top_label) {
    auto iter = m_func_table.begin();
    for (; iter != m_func_table.end(); ++iter) {
        string tmp;
        iter->GetName(tmp);
        if (tmp == term_name) {
            iter->GetTopLabel(top_label);
        }
    }
}

void FunctionTable::PrintAllTerm() {
    for (FunctionTableTerm term: m_func_table) {
        term.PrintTerm();
    }
}

SymbolTableTree* symbol_table_tree;
FunctionTable* handle_func_table;
