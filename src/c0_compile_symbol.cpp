#include <string.h>
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include "c0_compile_symbol.hpp"
#include "c0_compile_utils.hpp"

using std::string;
using std::map;
using std::vector;
using std::pair;
using std::cout;
using std::endl;


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
    string SymbolValue::GetValue<string>() const {
        return string_value;
    }
} // namespace c0_compile

void SymbolTableTerm::PrintTerm() const {
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

bool SymbolTable::Find(const string& name) const {
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
            case CONST:
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

void SymbolTable::PrintTable() const {
    fprintf(fp_symbol, "-------------------------------------------------\n");
    fprintf(fp_symbol, "function %s's symbol table\n", m_table_name.c_str());
    fprintf(fp_symbol, "function type: %s\n", symbol_type_string[m_table_type]);
    auto iter = m_symbol_table.begin();
    for (; iter != m_symbol_table.end(); ++iter) {
        iter->second.PrintTerm();
    }
    fprintf(fp_symbol, "-------------------------------------------------\n");
}

compile_errcode SymbolTable::GetTermIter(const string& name, vector<pair<string, SymbolTableTerm> >::iterator& iter) {
    iter = m_symbol_table.begin();
    for (; iter != m_symbol_table.end(); ++iter) {
        if (iter->first == name) {
            return COMPILE_OK;
        }
    }
    return NOT_FIND_TERM;
}

compile_errcode SymbolTable::GetTerm(const string& name, SymbolTableTerm& term) const {
    auto iter = m_symbol_table.begin();
    for (; iter != m_symbol_table.end(); ++iter) {
        if (iter->first == name) {
            term = iter->second;
            return COMPILE_OK;
        }
    }
    return NOT_FIND_TERM;
}

compile_errcode SymbolTable::GetTermType(const string& name, SymbolType& type) const {
    int ret = COMPILE_OK;
    SymbolTableTerm term;
    if ((ret = this->GetTerm(name, term)) != COMPILE_OK) {
        return ret;
    } else {
        type = term.GetType();
        return COMPILE_OK;
    }
}

compile_errcode SymbolTable::GetTermKind(const string& name, SymbolKind& kind) const {
    int ret = COMPILE_OK;
    SymbolTableTerm term;
    if ((ret = this->GetTerm(name, term)) != COMPILE_OK) {
        return ret;
    } else {
        kind = term.GetKind();
        return COMPILE_OK;
    }
}

compile_errcode SymbolTable::GetArraySpace(const string& name, int& array_space) const {
    int ret = COMPILE_OK;
    SymbolTableTerm term;
    if ((ret = this->GetTerm(name, term)) != COMPILE_OK) {
        return ret;
    } else {
        array_space = term.GetArrayInformation();
        return COMPILE_OK;
    }
}


compile_errcode SymbolTable::GetTermIntValue(const string& name, int& value) const {
    int ret = COMPILE_OK;
    SymbolTableTerm term;
    if ((ret = this->GetTerm(name, term)) != COMPILE_OK) {
        return ret;
    } else {
        value = term.GetValueInformation();
        return COMPILE_OK;
    }
}

compile_errcode SymbolTable::GetAddress(const string& name, int& addr) const {
    int ret = COMPILE_OK;
    SymbolTableTerm term;
    if ((ret = this->GetTerm(name, term)) != COMPILE_OK) {
        return ret;
    } else {
        addr = term.GetRelativeAddr();
        return COMPILE_OK;
    }
}

SymbolTableTree::~SymbolTableTree() {
}

void SymbolTableTree::InsertTable(const string& table_name, const SymbolType& type, const string& previous_level) {
    SymbolTable table = SymbolTable(table_name, type, previous_level, m_tree_address_length);
    pair<string, SymbolTable> pair_term(table_name, table);
    m_table_tree.push_back(pair_term);
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

bool SymbolTableTree::FindTerm(const string& name, bool only_this_level) const {
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
    //} while (!only_this_level && strcmp(current_table_name.c_str(), m_BOTTOM_LEVEL)!=0);
    } while (!only_this_level && current_table_name != m_BOTTOM_LEVEL);
    return false;
}

string SymbolTableTree::GetCurrentPreviousTableName() const {
    auto iter = m_table_tree.begin();
    for (; iter != m_table_tree.end(); ++iter) {
        if (iter->first == current_table_name)
            break;
    }
    return iter->second.GetPreviousTableName();
}

void SymbolTableTree::PrintTree() const {
    auto iter = m_table_tree.begin();
    for (; iter != m_table_tree.end(); ++iter) {
        (iter->second).PrintTable();
    }
}

SymbolType SymbolTableTree::GetCurrentTableType() const {
    string current_table_name = this->GetCurrentTableName();
    auto iter = m_table_tree.begin();
    for (; iter != m_table_tree.end(); ++iter) {
        if (iter->first == current_table_name) {
            break;
        }
    }
    return iter->second.GetTableType();
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

compile_errcode SymbolTableTree::GetAddressString(const string& begin_func_name, const string& name, string& address_string) {
    int addr;
    int ret = COMPILE_OK;
    string cur_table_name = begin_func_name;
    do {
        auto iter = m_table_tree.begin();
        for (; iter != m_table_tree.end(); ++iter) {
            if (iter->first == cur_table_name) {
                break;
            }
        }
        if ((ret = iter->second.GetAddress(name, addr)) != COMPILE_OK) {
            cur_table_name = iter->second.GetPreviousTableName();
        } else {
            if (cur_table_name != string("global")) {
                address_string = string("fp") + std::to_string(addr);
            } else {
                int base_addr = 0;
                address_string = string("g") + std::to_string(addr + base_addr);
            }
            return COMPILE_OK;
        }
    } while (cur_table_name != m_BOTTOM_LEVEL);
    return COMPILE_OK;
}

compile_errcode SymbolTableTree::GetAddressStringInterface(const string& name, string& address_string) {
    string current_table_name = this->GetCurrentTableName();
    return this->GetAddressString(current_table_name, name, address_string);
}

compile_errcode SymbolTableTree::GetAddressStringInterface(const string& current_table_name, const string& name, string& address_string) {
    return this->GetAddressString(current_table_name, name, address_string);

}

compile_errcode SymbolTableTree::GetTermKind(const string& begin_func_name, const string& name, SymbolKind& kind) {
    int ret = COMPILE_OK;
    string cur_func_name = begin_func_name;
    do {
        auto iter = m_table_tree.begin(); 
        for (; iter != m_table_tree.end(); ++iter) {
            if (iter->first == cur_func_name) {
                break;
            }
        }
        if ((ret = iter->second.GetTermKind(name, kind)) != COMPILE_OK) {
            cur_func_name = iter->second.GetPreviousTableName();
        } else {
            return COMPILE_OK;
        }
    } while(cur_func_name != m_BOTTOM_LEVEL);
    fprintf(stderr, "(kind)no match term name: %s---%s\n", begin_func_name.c_str(), name.c_str());
    return NOT_FIND_TERM;
}

compile_errcode SymbolTableTree::GetTermKindInterface(const string& name, SymbolKind& kind) {
    string cur_func_name = this->GetCurrentTableName();
    return this->GetTermKind(cur_func_name, name, kind);
}

compile_errcode SymbolTableTree::GetTermKindInterface(const string& cur_func_name, const string& name, SymbolKind& kind) {
    return this->GetTermKind(cur_func_name, name, kind);
}

compile_errcode SymbolTableTree::GetTermType(const string& begin_func_name, const string& name, SymbolType& type) {
    int ret = COMPILE_OK;
    string cur_func_name = begin_func_name;
    do {
        auto iter = m_table_tree.begin(); 
        for (; iter != m_table_tree.end(); ++iter) {
            if (iter->first == cur_func_name) {
                break;
            }
        }
        if ((ret = iter->second.GetTermType(name, type)) != COMPILE_OK) {
            cur_func_name = iter->second.GetPreviousTableName();
        } else {
            return COMPILE_OK;
        }
    } while(cur_func_name != m_BOTTOM_LEVEL);
    fprintf(stderr, "(type)no match term name: %s---%s\n", begin_func_name.c_str(), name.c_str());
    return NOT_FIND_TERM;
}

compile_errcode SymbolTableTree::GetTermTypeInterface(const string& name, SymbolType& type) {
    string cur_func_name = this->GetCurrentTableName();
    return this->GetTermType(cur_func_name, name, type);
}

compile_errcode SymbolTableTree::GetTermTypeInterface(const string& cur_func_name, const string& name, SymbolType& type) {
    return this->GetTermType(cur_func_name, name, type);
}

compile_errcode SymbolTableTree::GetArraySpace(const string& begin_func_name, const string& name, int& array_space) {
    int ret = COMPILE_OK;
    string cur_func_name = begin_func_name;
    do {
        auto iter = m_table_tree.begin(); 
        for (; iter != m_table_tree.end(); ++iter) {
            if (iter->first == cur_func_name) {
                break;
            }
        }
        if ((ret = iter->second.GetArraySpace(name, array_space)) != COMPILE_OK) {
            cur_func_name = iter->second.GetPreviousTableName();
        } else {
            return COMPILE_OK;
        }
    } while(cur_func_name != m_BOTTOM_LEVEL);
    fprintf(stderr, "(array space)no match term name: %s---%s\n", begin_func_name.c_str(), name.c_str());
    return NOT_FIND_TERM;
}

compile_errcode SymbolTableTree::GetArraySpaceInterface(const string& name, int& array_space) {
    string cur_func_name = this->GetCurrentTableName();
    return this->GetArraySpace(cur_func_name, name, array_space);
}

compile_errcode SymbolTableTree::GetArraySpaceInterface(const string& cur_func_name, const string& name, int& array_space) {
    return this->GetArraySpace(cur_func_name, name, array_space);
}

compile_errcode SymbolTableTree::GetTermIntValue(const string& begin_func_name, const string& name, int& value) {
    int ret = COMPILE_OK;
    string cur_func_name = begin_func_name;
    do {
        auto iter = m_table_tree.begin(); 
        for (; iter != m_table_tree.end(); ++iter) {
            if (iter->first == cur_func_name) {
                break;
            }
        }
        if ((ret = iter->second.GetTermIntValue(name, value)) != COMPILE_OK) {
            cur_func_name = iter->second.GetPreviousTableName();
        } else {
            return COMPILE_OK;
        }
    } while(cur_func_name != m_BOTTOM_LEVEL);
    fprintf(stderr, "(int value)no match term name: %s---%s\n", begin_func_name.c_str(), name.c_str());
    return NOT_FIND_TERM;
}

compile_errcode SymbolTableTree::GetTermIntValueInterface(const string& name, int& value) {
    string cur_func_name = this->GetCurrentTableName();
    return this->GetTermIntValue(cur_func_name, name, value);
}

compile_errcode SymbolTableTree::GetTermIntValueInterface(const string& cur_func_name, const string& name, int& value) {
    return this->GetTermIntValue(cur_func_name, name, value);
}

compile_errcode SymbolTableTree::GetTableSpaceLength(const string& table_name, int& length) {
    auto iter = m_table_tree.begin();
    for (; iter != m_table_tree.end(); ++iter) {
        if (iter->first == table_name) {
            length = iter->second.GetTableSpace();
            return COMPILE_OK;
        }
    }
    return NOT_FIND_TERM;
}

void FunctionTableTerm::PrintTerm() const {
    fprintf(fp_symbol, "--------------------------------------\n");
    fprintf(fp_symbol, "function\nname: %s\ntop label: %s\nbottom label: %s\nargument space: %d\nreturn value space: %d\nspace length: %d\nargument type:\n",
    m_func_name.c_str(), m_top_label.c_str(), m_bottom_label.c_str(), m_argument_space_length, m_return_value_space_length, m_space_length);
    for (SymbolType tmp : m_argument_type) {
        fprintf(fp_symbol, "\t%s\n", symbol_type_string[tmp]);
    }
}

void FunctionTable::InsertTerm(const string& func_name,
                               int space_length,
                               int return_value_number,
                               const vector<SymbolType>& argument_type) {
    int argument_number = argument_type.size();
    FunctionTableTerm term(func_name, space_length, argument_number, return_value_number, argument_type);
    m_func_table.push_back(term);
    m_current_term_ptr++;
}

bool FunctionTable::Find(const string& func_name) {
    for (FunctionTableTerm term: m_func_table) {
        if (term.GetName() == func_name) {
            return true;
        }
    }
    return false;
}

void FunctionTable::GetCurrentTermTopLabel(string& top_label) const {
    top_label = m_func_table[m_current_term_ptr].GetTopLabel();
}

void FunctionTable::GetCurrentTermBottomLabel(string& bottom_label) const {
    bottom_label = m_func_table[m_current_term_ptr].GetBottomLabel();
}

void FunctionTable::GetCurrentTermName(string& term_name) const {
    term_name = m_func_table[m_current_term_ptr].GetName();
}

void FunctionTable::GetCurrentTermArgumentNumber(int& number) const {
    number = m_func_table[m_current_term_ptr].GetArgumentNumber();
}

compile_errcode FunctionTable::GetTermTopLabel(const string& term_name, string& top_label) const {
    auto iter = m_func_table.begin();
    for (; iter != m_func_table.end(); ++iter) {
        if (iter->GetName() == term_name) {
            top_label = iter->GetTopLabel();
            return COMPILE_OK;
        }
    }
    return NOT_FIND_TERM;
}

compile_errcode FunctionTable::GetTermBottomLabel(const string& term_name, string& bottom_label) const {
    auto iter = m_func_table.begin();
    for (; iter != m_func_table.end(); ++iter) {
        if (iter->GetName() == term_name) {
            bottom_label = iter->GetBottomLabel();
            return COMPILE_OK;
        }
    }
    return NOT_FIND_TERM;
}

compile_errcode FunctionTable::GetTermSpaceLength(const string& func_name, int& space_length) const {
    auto iter = m_func_table.begin();
    for (; iter != m_func_table.end(); ++iter) {
        if (iter->GetName() == func_name) {
            space_length = iter->GetSpaceLength();
            return COMPILE_OK;
        }
    }
    return NOT_FIND_TERM;
}

compile_errcode FunctionTable::GetTermArgumentType(const string& func_name, vector<SymbolType>& argument_type) const {
    auto iter = m_func_table.begin();
    for (; iter != m_func_table.end(); ++iter) {
        if (iter->GetName() == func_name) {
            argument_type = iter->GetArgumentType();
            return COMPILE_OK;
        }
    }
    return NOT_FIND_TERM;
}

void FunctionTable::SetTermTopLabel(const string& func_name, const string& top_label) {
    auto iter = m_func_table.begin();
    for (; iter != m_func_table.end(); ++iter) {
        if (iter->GetName() == func_name) {
            iter->SetTopLabel(top_label);
        }
    }
}

void FunctionTable::SetTermBottomLabel(const string& func_name, const string& bottom_label) {
    auto iter = m_func_table.begin();
    for (; iter != m_func_table.end(); ++iter) {
        if (iter->GetName() == func_name) {
            iter->SetBottomLabel(bottom_label);
        }
    }
}

bool SymbolTableTree::MatchKeyword(const string& name) {
    auto iter = keyword.find(name);
    if (iter == keyword.end()) {
        return false;
    } else {
        return true;
    }
}

bool FunctionTable::GetFuncLabel(string& top_label, string& bottom_label) {
    if (m_current_term_ptr == m_func_table.size()) {
        return false;
    } else {
        top_label = m_func_table[m_current_term_ptr].GetTopLabel();
        bottom_label = m_func_table[m_current_term_ptr].GetBottomLabel();
        //fprintf(stdout, "%s---%s\n", top_label.c_str(), bottom_label.c_str());
        return true;
    }
}

void FunctionTable::PrintAllTerm() const {
    for (FunctionTableTerm term: m_func_table) {
        term.PrintTerm();
    }
}

SymbolTableTree* symbol_table_tree;
FunctionTable* handle_func_table;
