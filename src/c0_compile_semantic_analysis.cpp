#include <string>
#include <iostream>
#include "c0_compile_utils.hpp"
#include "c0_compile_symbol.hpp"
#include "c0_compile_lexical_analysis.hpp"
#include "c0_compile_gramma.hpp"
#include "c0_compile_tools.hpp"

using std::string;
using std::cout;
using std::endl;

extern SymbolTableTree* symbol_table_tree;
extern FunctionTable* handle_func_table;
extern SymbolQueue* handle_symbol_queue;
extern LogTools* g_log_tools;
SymbolQueue* handle_correct_queue = handle_symbol_queue;

inline bool IsAddOperation(SymbolName name) {
    return (name == ADD_SYM) || (name == SUB_SYM);
}

inline bool IsMultiplyOperation(SymbolName name) {
    return (name == MUL_SYM) || (name == DIV_SYM);
}

inline bool IsValidVariableType(SymbolName name) {
    return (name == INT_SYM) || (name == CHAR_SYM);
}

inline bool IsValidFunctionType(SymbolName name) {
    return (name == INT_SYM) || (name == CHAR_SYM) || (name == VOID_SYM);
}

inline bool IsRelationalOpeartor(SymbolName name) {
    return (name == EQUAL_SYM ||
            name == NOT_EQUAL_SYM ||
            name == SMALL_SYM ||
            name == SMALL_EQUAL_SYM ||
            name == LARGE_SYM ||
            name == LARGE_EQUAL_SYM);
}

inline int SymbolTypeMap(SymbolType& item) {
    switch (item) {
        case CHAR: return 1;
        case INT: return 2;
        default: fprintf(stderr, "invalid symbol type\n");
    }
    return -2;
}

inline SymbolType SymbolTypeInverseMap(int map_value) {
    switch (map_value) {
        case 1: return CHAR;
        case 2: return INT;
        default: fprintf(stderr, "invalid symbol type\n");
    }
    return VOID;
}

inline SymbolType MaxDataType(SymbolType& item1, SymbolType& item2) {
    int value1 = SymbolTypeMap(item1);
    int value2 = SymbolTypeMap(item2);
    int max_value = value1 >= value2 ? value1 : value2;
    return SymbolTypeInverseMap(max_value);
}

inline SymbolType Name2Type(SymbolName name) {
    switch (name) {
        case (INT_SYM): return INT;
        case (CHAR_SYM): return CHAR;
        case (VOID_SYM): return VOID;
        default: {
            fprintf(stderr, "invalid enum content in func Name2Type\n");
            return VOID;
        }
    }
}

/*FILE* semantic_error = fopen("semantic_error.txt", "w");
bool semantic_flag = true;
void SemanticErrorLog(string error_type, string content, int line_number, int character_number) {
    semantic_flag = false;
    if (semantic_error == NULL) {
        fprintf(stderr, "%s error: '%s' in line %d character %d\n", error_type.c_str(), content.c_str(), line_number, character_number);
    } else {
        fprintf(semantic_error, "%s error: '%s' in line %d character %d\n", error_type.c_str(),  content.c_str(), line_number, character_number);
    }
}*/

void ArrayCheck(const string& array_name, int line_number, int character_number) {
    SymbolKind identifier_kind = FUNCTION;  // temp init
    symbol_table_tree->GetTermKindInterface(array_name, identifier_kind);
    if (identifier_kind != ARRAY) {
        g_log_tools->SemanticErrorLogs("invalid array identifier: ", array_name, line_number, character_number);
        return;
    }
    handle_correct_queue->SetCacheLocate();
    SymbolName name;
    name = handle_correct_queue->GetCurrentName();
    if (name == INTERGER_SYM) {
        int value = handle_correct_queue->GetCurrentValue<int>();
        handle_correct_queue->NextSymbol();
        name = handle_correct_queue->GetCurrentName();
        if (name == R_SQUARE_BRACKET_SYM) {
            int array_space;
            symbol_table_tree->GetArraySpaceInterface(array_name, array_space);
            if (value<0 || value>=array_space)
                g_log_tools->SemanticErrorLogs("invalid array index value:" + std::to_string(value), array_name, line_number, character_number);
        }
    } else if (name == IDENTIFIER_SYM) {
        SymbolKind kind;
        string identifier_name = handle_correct_queue->GetCurrentValue<string>();
        symbol_table_tree->GetTermKindInterface(identifier_name, kind);
        if (kind == CONST) {
            int value;
            symbol_table_tree->GetTermIntValueInterface(identifier_name, value);
            handle_correct_queue->NextSymbol();
            name = handle_correct_queue->GetCurrentName();
            if (name == R_SQUARE_BRACKET_SYM) {
                int array_space;
                symbol_table_tree->GetArraySpaceInterface(array_name, array_space);
                if (value<0 || value>=array_space)
                    g_log_tools->SemanticErrorLogs("invalid array index value:" + std::to_string(value), array_name, line_number, character_number);
            }
        }
    }
    handle_correct_queue->SetCurrentLocate();
}

compile_errcode IdentifierCheck(const string& identifier_name, int line_number, int character_number) {
    if (symbol_table_tree->FindTerm(identifier_name, false)) {
        return COMPILE_OK;
    } else {
        g_log_tools->SemanticErrorLogs(string("undefined identifier error"), identifier_name, line_number, character_number);
        return SEMANTIC_ERROR;
    }
}

void AssignCheck(const string& identifier_name, int line_number, int character_number) {
    SymbolKind kind = VARIABLE;
    symbol_table_tree->GetTermKindInterface(identifier_name, kind);
    switch(kind) {
        case VARIABLE:
        case PARAMETER: break;
        case ARRAY: {
            handle_correct_queue->SetCacheLocate();
            handle_correct_queue->NextSymbol();
            SymbolName name = handle_correct_queue->GetCurrentName();
            if (name != L_SQUARE_BRACKET_SYM) {
                string str = symbol_kind_string[kind];
                g_log_tools->SemanticErrorLogs("invalid assign left value---kind:" + str, identifier_name, line_number, character_number);         
            }
            handle_correct_queue->SetCurrentLocate();
            break;
        }
        default: {
            string str = symbol_kind_string[kind];
            g_log_tools->SemanticErrorLogs("invalid assign left value---kind:" + str, identifier_name, line_number, character_number);         
        }
    }
}

void ArgumentCheck(const string& identifier_name, int line_number, int character_number, vector<SymbolType>& value_argument_type) {
    if (!handle_func_table->Find(identifier_name)) {
        return;
    }
    vector<SymbolType> argument_type;
    handle_func_table->GetTermArgumentType(identifier_name, argument_type);
    int argument_type_len = argument_type.size();
    int value_argument_type_len = value_argument_type.size();
    if (argument_type_len != value_argument_type_len) {
        g_log_tools->SemanticErrorLogs("argument list expected: " + std::to_string(argument_type_len) + ", but value argument list had: "
                + std::to_string(value_argument_type_len), identifier_name, line_number, character_number);
        return;
    }
    for (int i=0; i<value_argument_type_len; ++i) {
        if (argument_type[i] != value_argument_type[i]) {
            string str1 = symbol_type_string[argument_type[i]];
            string str2 = symbol_type_string[value_argument_type[i]];
            g_log_tools->SemanticErrorLogs("argument expected: " + str1 + ", but value argument had: " + str2, identifier_name, line_number, character_number);
        }
    }
}

compile_errcode Factor::Action(SymbolType& factor_type) {
    int ret = COMPILE_OK;
    SymbolType expression_type;
    SymbolKind identifier_kind;
    SymbolName name = handle_correct_queue->GetCurrentName();
    int line_number = handle_correct_queue->GetCurrentLine();
    int character_number = handle_correct_queue->GetCurrentCharacter();
    switch (name) {
        case INTERGER_SYM: factor_type = INT; break;
        case CHARACTER_SYM: factor_type = CHAR; break;
        case IDENTIFIER_SYM: {
            // check identifier
            m_identifier_name = handle_correct_queue->GetCurrentValue<string>();
            m_valid = (ret = IdentifierCheck(m_identifier_name, line_number, character_number)) == COMPILE_OK;
            handle_correct_queue->SetCacheLocate();
            handle_correct_queue->NextSymbol();
            name = handle_correct_queue->GetCurrentName();
            // array
            if (name == L_SQUARE_BRACKET_SYM) {
                handle_correct_queue->NextSymbol();
                if (m_valid)
                    ArrayCheck(m_identifier_name, line_number, character_number);
                if ((ret = m_expression.Action(expression_type)) == COMPILE_OK) {
                    name = handle_correct_queue->GetCurrentName();
                    if (name == R_SQUARE_BRACKET_SYM) {
                        if (m_valid) {
                            symbol_table_tree->GetTermTypeInterface(m_identifier_name, factor_type);
                        } else {
                            factor_type = VOID;
                        }
                        break;
                    } else {
                        return NOT_MATCH;
                    }
                } else {
                    return NOT_MATCH;
                }
            } else if (name == L_CIRCLE_BRACKET_SYM) {  // function
                handle_correct_queue->NextSymbol();
                vector<SymbolType> argument_type;
                if ((ret = m_value_argument_list.Action(argument_type)) == COMPILE_OK) {
                    ArgumentCheck(m_identifier_name, line_number, character_number, argument_type);
                    name = handle_correct_queue->GetCurrentName();
                    if (name == R_CIRCLE_BRACKET_SYM) {
                        string str = "This is a function call";
                        if (m_valid) {
                            symbol_table_tree->GetTermTypeInterface(m_identifier_name, factor_type);
                            if (factor_type == VOID) {
                                m_valid = false; // (doubt)
                                g_log_tools->SemanticErrorLogs(string("no return value func can't be used as factor"), m_identifier_name, line_number, character_number);
                            }
                        } else {
                            factor_type = VOID;
                        }
                        break;
                    } else {
                        return NOT_MATCH;
                    }
                } else {
                    return NOT_MATCH;
                }
            } else {
                handle_correct_queue->SetCurrentLocate();
                if (m_valid) {
                    symbol_table_tree->GetTermTypeInterface(m_identifier_name, factor_type);
                } else {
                    factor_type = VOID;
                }
                break;
            }
        }
        case L_CIRCLE_BRACKET_SYM: {
            handle_correct_queue->NextSymbol();
            if ((ret = m_expression.Action(factor_type)) == COMPILE_OK) {
                factor_type = INT;
                name = handle_correct_queue->GetCurrentName();
                if (name == R_CIRCLE_BRACKET_SYM) {
                    break;
                } else {
                    return NOT_MATCH;
                }
            } else {
                return NOT_MATCH;
            }
        }
        default: {
            fprintf(stderr, "invalid enum content in func factor action\n");
            return NOT_MATCH;
        }
    }
    handle_correct_queue->NextSymbol();
    return COMPILE_OK;
}

compile_errcode Term::Action(SymbolType& term_type) {
    m_factor = new Factor;
    int ret = COMPILE_OK;
    int state = 0;
    term_type = CHAR;
    SymbolType cur_factor_type;
    while (true) {
        SymbolName name = handle_correct_queue->GetCurrentName();
        switch (state) {
            case 0: {
                if ((ret = m_factor->Action(cur_factor_type)) == COMPILE_OK) {
                    state = 1;
                    term_type = MaxDataType(term_type, cur_factor_type);
                    break;
                } else {
                    delete(m_factor);
                    return NOT_MATCH;
                }
            }
            case 1: {
                if (IsMultiplyOperation(name)) {
                    term_type = INT;
                    state = 0;
                    break;
                } else {
                    delete(m_factor);
                    return COMPILE_OK;
                }
            }
        }
        if (state == 0)
            handle_correct_queue->NextSymbol();
    }
}

compile_errcode Expression::Action(SymbolType& expression_type) {
    int ret = COMPILE_OK;
    int state = 0;
    expression_type = CHAR;
    SymbolType cur_term_type;
    while (true) {
        SymbolName name = handle_correct_queue->GetCurrentName();
        switch (state) {
            case 0: {
                if (IsAddOperation(name)) {
                    expression_type = INT;
                    state = 0;
                    break;
                } else if ((ret = m_term.Action(cur_term_type)) == COMPILE_OK) {
                    m_term.LogOutput();
                    expression_type = MaxDataType(expression_type, cur_term_type);
                    state = 1;
                    break;
                } else {
                    return NOT_MATCH;
                }
            }
            case 1: {
                if (IsAddOperation(name)) {
                    expression_type = INT;
                    state = 2;
                    break;
                } else {
                    return COMPILE_OK;
                }
            }
            case 2: {
                if ((ret = m_term.Action(cur_term_type)) == COMPILE_OK) {
                    m_term.LogOutput();
                    expression_type = MaxDataType(expression_type, cur_term_type);
                    state = 1;
                    break;
                } else {
                    return NOT_MATCH;
                }
            }
        }
        if (state != 1) {
            handle_correct_queue->NextSymbol();
        }
    }
}

compile_errcode ConstantDefinition::Action() {
    int state = 0;
    int ret = 0;
    while (true) {
        SymbolName name = handle_correct_queue->GetCurrentName();
        int line_number = handle_correct_queue->GetCurrentLine();
        int character_number = handle_correct_queue->GetCurrentCharacter();
        switch (state) {
            case 0: {
                if (name == CONST_SYM) {
                    state = 1;
                    break;
                } else {
                    return NOT_MATCH;
                }
            }
            case 1: {
                if (IsValidVariableType(name)) {
                    state = 2;
                    m_type = name;
                    break;
                } else {
                    return INVALID_TYPE_ERROR;
                }
            }
            case 2: {
                if (name == IDENTIFIER_SYM) {
                    state = 3;
                    m_identifier_name = handle_correct_queue->GetCurrentValue<string>();
                    if (symbol_table_tree->FindTerm(m_identifier_name, true)) {
                        g_log_tools->SemanticErrorLogs(string("repeat definition identifier"), m_identifier_name, line_number, character_number);
                        m_valid = false;
                    } else {
                        if (symbol_table_tree->MatchKeyword(m_identifier_name)) {
                            m_valid = false;
                            g_log_tools->SemanticErrorLogs("identifier repeat with the keyword: " + m_identifier_name, "", line_number, character_number);
                        } else {
                            m_valid = true;
                        }
                    }
                    break;
                } else {
                    return NOT_MATCH;
                }
            }
            case 3: {
                if (name == ASSIGN_SYM) {
                    state = 4;
                } else {
                    return NOT_MATCH;
                }
                break;
            }
            case 4: {
                if (name == INTERGER_SYM || name == CHARACTER_SYM) {
                    state = 5;
                    if (m_type == INT_SYM && name != INTERGER_SYM) {
                        g_log_tools->SemanticErrorLogs(string("invalid assign match(int)"), m_identifier_name, line_number, character_number);
                        break;
                    }
                    if (m_type == CHAR_SYM && name != CHARACTER_SYM) {
                        g_log_tools->SemanticErrorLogs(string("invalid assign match(char)"), m_identifier_name, line_number, character_number);
                        break;
                    }
                    if (m_valid) {
                        SymbolTableTerm term(m_identifier_name, CONST, m_type);
                        if (name == INTERGER_SYM)
                            term.SetConstInformation<int>(handle_correct_queue->GetCurrentValue<int>());
                        else if (name == CHARACTER_SYM)
                            term.SetConstInformation<char>(handle_correct_queue->GetCurrentValue<char>());
                        symbol_table_tree->Insert(term);
                    }
                    break;
                } else {
                    return NOT_MATCH;
                }
            }
            case 5: {
                if (name == COMMA_SYM) {
                    state = 2;
                } else if (name == SEMICOLON_SYM) {
                    state = 6;
                } else {
                   return NOT_MATCH;
                }
                break;
            }
            case 6: return COMPILE_OK;
        }
        handle_correct_queue->NextSymbol();
    }
}

compile_errcode ConstantDeclaration::Action() {
    int ret = 0;
    int correct_count = 0;
    while (true) {
        SymbolName name = handle_correct_queue->GetCurrentName();
        if (name == CONST_SYM) {
            if ((ret = m_constant_definition.Action()) == COMPILE_OK) {
                m_constant_definition.LogOutput();
                correct_count++;
            } else {
                return NOT_MATCH;
            }
        } else {
            if (correct_count > 0)
                return COMPILE_OK;
            else
                return NOT_MATCH;
        }
    }
}

compile_errcode VariableDefinition::Action() {
    int state = 0;
    while (true) {
        SymbolName name = handle_correct_queue->GetCurrentName();
        int line_number = handle_correct_queue->GetCurrentLine();
        int character_number = handle_correct_queue->GetCurrentCharacter();
        switch (state) {
            case 0: {
                if (IsValidVariableType(name)) {
                    state = 1;
                    m_type = name;
                    break;
                } else {
                    return NOT_MATCH;
                }
            }
            case 1: {
                if (name == IDENTIFIER_SYM) {
                    state = 2;
                    m_identifier_name = handle_correct_queue->GetCurrentValue<string>();
                    if (symbol_table_tree->FindTerm(m_identifier_name, true)) {
                        g_log_tools->SemanticErrorLogs(string("repeat definition identifier"), m_identifier_name, line_number, character_number);
                        m_valid = false;
                    } else {
                        if (symbol_table_tree->MatchKeyword(m_identifier_name)) {
                            m_valid = false;
                            g_log_tools->SemanticErrorLogs("identifier repeat with the keyword: " + m_identifier_name, "", line_number, character_number);
                        } else {
                            m_valid = true;
                        }
                    }
                    break;
                } else {
                    return NOT_MATCH;
                }
            }
            case 2: {
                if (name == L_SQUARE_BRACKET_SYM) {
                    state = 11;
                    break;
                } else if (name == COMMA_SYM) {
                    state = 1;
                    if (m_valid) {
                        SymbolTableTerm term(m_identifier_name, VARIABLE, m_type);
                        symbol_table_tree->Insert(term);
                    }
                    break;
                } else if (name == SEMICOLON_SYM) {
                    state = 3;
                    if (m_valid) {
                        SymbolTableTerm term(m_identifier_name, VARIABLE, m_type);
                        symbol_table_tree->Insert(term);
                    }
                    break;
                } else {
                    return NOT_MATCH;
                }
            }
            case 3: return COMPILE_OK;
            case 11: {
                if (name == INTERGER_SYM) {
                    state = 12;
                    m_array_length = handle_correct_queue->GetCurrentValue<int>();
                    if (m_array_length <= 0) {
                        m_valid = false;
                        g_log_tools->SemanticErrorLogs(string("invalid array length"), m_identifier_name, line_number, character_number);
                    }
                    break;
                } else {
                    return NOT_MATCH;
                }
            }
            case 12: {
                if (name == R_SQUARE_BRACKET_SYM) {
                    state = 13;
                    if (m_valid) {
                        SymbolTableTerm term(m_identifier_name, ARRAY, m_type);
                        term.SetArrayInformation(m_array_length);
                        symbol_table_tree->Insert(term);
                    }
                    break;
                } else {
                    return NOT_MATCH;
                }
            }
            case 13: {
                if (name == COMMA_SYM) {
                    state = 1;
                    break;
                } else if (name == SEMICOLON_SYM) {
                    state = 3;
                    break;
                } else {
                    return NOT_MATCH;
                }
            }
        }
        handle_correct_queue->NextSymbol();
    }
}

compile_errcode VariableDeclaration::Action() {
    int ret = 0;
    int correct_count = 0;
    while (true) {
        handle_correct_queue->SetCacheLocate();
        SymbolName name = handle_correct_queue->GetCurrentName();
        if (IsValidVariableType(name)) {
            handle_correct_queue->NextSymbol();
            name = handle_correct_queue->GetCurrentName();
            if (name == IDENTIFIER_SYM) {
                handle_correct_queue->NextSymbol();
                name = handle_correct_queue->GetCurrentName();
                if (name == L_CIRCLE_BRACKET_SYM) {
                    handle_correct_queue->SetCurrentLocate();
                    break;
                } else {
                    handle_correct_queue->SetCurrentLocate();
                }
            } else {
                break;
            }
        } else {
            if (correct_count > 0)
                return COMPILE_OK;
            else
                return NOT_MATCH;
        }
        if ((ret = m_variable_definition.Action()) == COMPILE_OK) {
            m_variable_definition.LogOutput();
            correct_count++;
        } else {
            return NOT_MATCH;
        }
    }
    return NOT_MATCH;
}

compile_errcode InputStatement::Action() {
    int ret = COMPILE_OK;
    int state = 0;
    while (true) {
        SymbolName name = handle_correct_queue->GetCurrentName();
        int line_number = handle_correct_queue->GetCurrentLine();
        int character_number = handle_correct_queue->GetCurrentCharacter();
        switch (state) {
            case 0: {
                if (name == SCANF_SYM) {
                    state = 1;
                    break;
                } else {
                    return NOT_MATCH;
                }
            }
            case 1: {
                if (name == L_CIRCLE_BRACKET_SYM) {
                    state = 2;
                    break;
                } else {
                    return NOT_MATCH;
                }
            }
            case 2: {
                if (name == IDENTIFIER_SYM) {
                    string identifier_name = handle_correct_queue->GetCurrentValue<string>();
                    IdentifierCheck(identifier_name, line_number, character_number);
                    state = 3;
                    break;
                } else {
                    return NOT_MATCH;
                }
            }
            case 3: {
                if (name == COMMA_SYM) {
                    state = 2;
                    break;
                } else if (name == R_CIRCLE_BRACKET_SYM) {
                    state = 4;
                    break;
                } else {
                    return NOT_MATCH;
                }
            }
            case 4: return COMPILE_OK;
        }
        handle_correct_queue->NextSymbol();
    }
}

compile_errcode ReturnStatement::Action(SymbolType& function_type, string funtion_name) {
    int ret = COMPILE_OK;
    int state = 0;
    int line_number = handle_correct_queue->GetCurrentLine();
    int character_number = handle_correct_queue->GetCurrentCharacter();
    SymbolType expression_type;
    while (true) {
        SymbolName name = handle_correct_queue->GetCurrentName();
        switch (state) {
            case 0: {
                if (name == RETURN_SYM) {
                    state = 1;
                    break;
                } else {
                    return NOT_MATCH;
                }
            }
            case 1: {
                if (name == L_CIRCLE_BRACKET_SYM) {
                    state = 2;
                    break;
                } else if (name == SEMICOLON_SYM) {
                    if (function_type != VOID) {
                        g_log_tools->SemanticErrorLogs(string("non void funtion with void return value"), funtion_name, line_number, character_number);
                    }
                    return COMPILE_OK;
                } else {
                    return NOT_MATCH;
                }
            }
            case 2: {
                if ((ret = m_expression.Action(expression_type)) == COMPILE_OK) {
                    state = 3;
                    if (function_type != expression_type) {
                        g_log_tools->SemanticErrorLogs(string("funtion return value not match"), funtion_name, line_number, character_number);
                    }
                    m_expression.LogOutput();
                    break;
                } else {
                    return NOT_MATCH;
                }
            }
            case 3: {
                if (name == R_CIRCLE_BRACKET_SYM) {
                    state = 4;
                    break;
                } else {
                    return NOT_MATCH;
                }
            }
            case 4: return COMPILE_OK;
        }
        if (state != 3)
            handle_correct_queue->NextSymbol();
    }
}

compile_errcode OutputStatement::Action() {
    int ret = COMPILE_OK;
    int state = 0;
    SymbolType expression_type;
    while (true) {
        SymbolName name = handle_correct_queue->GetCurrentName();
        switch (state) {
            case 0: {
                if (name == PRINTF_SYM) {
                    state = 1;
                    break;
                } else {
                    return NOT_MATCH;
                }
            }
            case 1: {
                if (name == L_CIRCLE_BRACKET_SYM) {
                    state = 2;
                    break;
                } else {
                    return NOT_MATCH;
                }
            }
            case 2: {
                if (name == STRING_SYM) {
                    string str("This is a string");
                    state = 3;
                    break;
                } else if ((ret = m_expression.Action(expression_type)) == COMPILE_OK) {
                    state = 5;
                    break;
                } else {
                    return NOT_MATCH;
                }
            }
            case 3: {
                if (name == COMMA_SYM) {
                    state = 4;
                    break;
                } else if (name == R_CIRCLE_BRACKET_SYM) {
                    state = 6;
                    break;
                } else {
                    return NOT_MATCH;
                }
            }
            case 4: {
                if ((ret = m_expression.Action(expression_type)) == COMPILE_OK) {
                    state = 5;
                    break;
                } else {
                    return NOT_MATCH;
                }
            }
            case 5: {
                if (name == R_CIRCLE_BRACKET_SYM) {
                    state = 6;
                    break;
                } else {
                    return NOT_MATCH;
                }
            }
            case 6: return COMPILE_OK;
        }
        if (state != 5)
            handle_correct_queue->NextSymbol();
    }
}

compile_errcode AssignStatement::Action() {
    int ret = COMPILE_OK;
    int id_ret = COMPILE_OK;
    int state = 0;
    SymbolType expression_type;
    SymbolType identifier_type;
    SymbolKind identifier_kind;
    string identifier_name;
    while (true) {
        SymbolName name = handle_correct_queue->GetCurrentName();
        int line_number = handle_correct_queue->GetCurrentLine();
        int character_number = handle_correct_queue->GetCurrentCharacter();
        switch (state) {
            case 0: {
                if (name == IDENTIFIER_SYM) {
                    identifier_name = handle_correct_queue->GetCurrentValue<string>();
                    id_ret = IdentifierCheck(identifier_name, line_number, character_number);
                    state = 1;
                    break;
                } else {
                    return NOT_MATCH;
                }
            }
            case 1: {
                if (name == ASSIGN_SYM) {
                    if (ret == COMPILE_OK)
                        AssignCheck(identifier_name, line_number, character_number);
                    state = 2;
                    break;
                } else if (name == L_SQUARE_BRACKET_SYM) {
                    handle_correct_queue->NextSymbol();
                    ArrayCheck(identifier_name, line_number, character_number);
                    state = 11;
                    break;
                } else {
                    return NOT_MATCH;
                }
            }
            case 2: {
                if ((ret = m_expression.Action(expression_type)) == COMPILE_OK) {
                    if (id_ret == COMPILE_OK) {
                        symbol_table_tree->GetTermTypeInterface(identifier_name, identifier_type);
                        if (identifier_type != expression_type) {
                            g_log_tools->SemanticErrorLogs("assign type not match", identifier_name, line_number, character_number);
                        }
                    }
                    state = 3;
                    break;
                } else {
                    return NOT_MATCH;
                }
            }
            case 3: return COMPILE_OK;
            case 11: {
                if ((ret = m_expression.Action(expression_type)) == COMPILE_OK) {
                    m_expression.LogOutput();
                    state = 12;
                    break;
                } else {
                    return NOT_MATCH;
                }
            }
            case 12: {
                if (name == R_SQUARE_BRACKET_SYM) {
                    state = 13;
                    break;
                } else {
                    return NOT_MATCH;
                }
            }
            case 13: {
                if (name == ASSIGN_SYM) {
                    state = 2;
                    break;
                } else {
                    return NOT_MATCH;
                }
            }
        }
        if (state != 3 && state != 11 && state!=12)
            handle_correct_queue->NextSymbol();
    }
}

compile_errcode Condition::Action() {
    int ret = COMPILE_OK;
    int state = 0;
    SymbolType expression_type;
    while (true) {
        SymbolName name = handle_correct_queue->GetCurrentName();
        int line_number = handle_correct_queue->GetCurrentLine();
        int character_number = handle_correct_queue->GetCurrentCharacter();
        switch (state) {
            case 0: {
                if ((ret = m_expression.Action(expression_type)) == COMPILE_OK) {
                    if (expression_type == CHAR) {
                        g_log_tools->SemanticErrorLogs("condition must be int", string(""), line_number, character_number);
                    }
                    m_expression.LogOutput();
                    state = 1;
                    break;
                } else {
                    return NOT_MATCH;
                }
            }
            case 1: {
                if (IsRelationalOpeartor(name)) {
                    state = 2;
                    break;
                } else {
                    return COMPILE_OK;
                }
            }
            case 2: {
                if ((ret = m_expression.Action(expression_type)) == COMPILE_OK) {
                    if (expression_type == CHAR) {
                        g_log_tools->SemanticErrorLogs("condition must be int", string(""), line_number, character_number);
                    }
                    m_expression.LogOutput();
                    state = 3;
                    break;
                } else {
                    return NOT_MATCH;
                }
            }
            case 3: return COMPILE_OK;
        }
        if (state == 2)
            handle_correct_queue->NextSymbol();
    }
}

compile_errcode ConditionStatement::Action() {
    int ret = COMPILE_OK;
    int state = 0;
    m_statement_ptr = new Statement;
    while (true) {
        SymbolName name = handle_correct_queue->GetCurrentName();
        switch (state) {
            case 0: {
                if (name == IF_SYM) {
                    state = 1;
                    break;
                } else {
                    goto ERROR_IF;
                }
            }
            case 1: {
                if (name == L_CIRCLE_BRACKET_SYM) {
                    state = 2;
                    break;
                } else {
                    goto ERROR_IF;
                }
            }
            case 2: {
                if ((ret = m_condition.Action()) == COMPILE_OK) {
                    m_condition.LogOutput();
                    state = 3;
                    break;
                } else {
                    goto ERROR_IF;
                }
            }
            case 3: {
                if (name == R_CIRCLE_BRACKET_SYM) {
                    state = 4;
                    break;
                } else {
                    goto ERROR_IF;
                }
            }
            case 4: {
                if ((ret = m_statement_ptr->Action()) == COMPILE_OK) {
                    m_statement_ptr->LogOutput();
                    state = 5;
                    break;
                } else {
                    goto ERROR_IF;
                }
            }
            case 5: goto CORRECT_IF;
        }
        if (state != 3 && state != 5)
            handle_correct_queue->NextSymbol();
    }
    CORRECT_IF:
        delete(m_statement_ptr);
        return COMPILE_OK;
    ERROR_IF:
        delete(m_statement_ptr);
        return NOT_MATCH;
}

compile_errcode WhileLoopStatement::Action() {
    int ret = COMPILE_OK;
    int state = 0;
    m_statement_ptr = new Statement;
    while (true) {
        SymbolName name = handle_correct_queue->GetCurrentName();
        switch (state) {
            case 0: {
                if (name == WHILE_SYM) {
                    state = 1;
                    break;
                } else {
                    goto ERROR_WHILE;
                }
            }
            case 1: {
                if (name == L_CIRCLE_BRACKET_SYM) {
                    state = 2;
                    break;
                } else {
                    goto ERROR_WHILE;
                }
            }
            case 2: {
                if ((ret = m_condition.Action()) == COMPILE_OK) {
                    m_condition.LogOutput();
                    state = 3;
                    break;
                } else {
                    goto ERROR_WHILE;
                }
            }
            case 3: {
                if (name == R_CIRCLE_BRACKET_SYM) {
                    state = 4;
                    break;
                } else {
                    goto ERROR_WHILE;
                }
            }
            case 4: {
                if ((ret = m_statement_ptr->Action()) == COMPILE_OK) {
                    m_statement_ptr->LogOutput();
                    state = 5;
                    break;
                } else {
                    goto ERROR_WHILE;
                }
            }
            case 5: goto CORRECT_WHILE;
        }
        if (state != 3 && state != 5)
            handle_correct_queue->NextSymbol();
    }
    CORRECT_WHILE:
        delete(m_statement_ptr);
        return COMPILE_OK;
    ERROR_WHILE:
        delete(m_statement_ptr);
        return NOT_MATCH;
}

compile_errcode SwitchChildStatement::Action(const SymbolType& parent_type) {
    int ret = COMPILE_OK;
    int state = 0;
    m_statement_ptr = new Statement;
    while (true) {
        SymbolName name = handle_correct_queue->GetCurrentName();
        int line_number = handle_correct_queue->GetCurrentLine();
        int character_number = handle_correct_queue->GetCurrentCharacter();
        switch (state) {
            case 0: {
                if (name == CASE_SYM) {
                    state = 1;
                    break;
                } else {
                    goto ERROR_SWITCH_CHILD;
                }
            }
            case 1: {
                if (name == INTERGER_SYM || name == CHARACTER_SYM) {
                    SymbolType constant_type = name == INTERGER_SYM ? INT :
                                               name == CHARACTER_SYM ? CHAR : VOID;
                    if (parent_type != constant_type) {
                        string str1 = symbol_type_string[parent_type];
                        string str2 = symbol_type_string[constant_type];
                        g_log_tools->SemanticErrorLogs("case type not match between " + str1 + "and " + str2, string(""), line_number, character_number);
                    }
                    state = 2;
                    break;
                } else {
                    goto ERROR_SWITCH_CHILD;
                }
            }
            case 2: {
                if (name == COLON_SYM) {
                    state = 3;
                    break;
                } else {
                    goto ERROR_SWITCH_CHILD;
                }
            }
            case 3: {
                if ((ret = m_statement_ptr->Action()) == COMPILE_OK) {
                    m_statement_ptr->LogOutput();
                    state = 4;
                    break;
                } else {
                    goto ERROR_SWITCH_CHILD;
                }
            }
            case 4: goto CORRECT_SWITCH_CHILD;
        }
        if (state != 4)
            handle_correct_queue->NextSymbol();
    }
    CORRECT_SWITCH_CHILD:
        delete(m_statement_ptr);
        return COMPILE_OK;
    ERROR_SWITCH_CHILD:
        delete(m_statement_ptr);
        return NOT_MATCH;
}

compile_errcode SwitchTable::Action(const SymbolType& parent_type) {
    int ret = 0;
    int count = 0;
    while (true) {
        if ((ret = m_switch_child_statement.Action(parent_type)) == COMPILE_OK) {
            m_switch_child_statement.LogOutput();
            count++;
        } else {
            break;
        }
    }
    if (count > 0)
        return COMPILE_OK;
    else
        return NOT_MATCH;
}

compile_errcode Default::Action() {
    int ret = COMPILE_OK;
    int state = 0;
    while (true) {
        SymbolName name = handle_correct_queue->GetCurrentName();
        switch (state) {
            case 0: {
                if (name == DEFAULT_SYM) {
                    state = 1;
                    break;
                } else {
                    return NOT_MATCH;
                }
            }
            case 1: {
                if (name == COLON_SYM) {
                    state = 2;
                    break;
                } else {
                    return NOT_MATCH;
                }
            }
            case 2: {
                m_statement_ptr = new Statement;
                if ((ret = m_statement_ptr->Action()) == COMPILE_OK) {
                    m_statement_ptr->LogOutput();
                    delete(m_statement_ptr);
                    return COMPILE_OK;
                } else {
                    delete(m_statement_ptr);
                    return NOT_MATCH;
                }
            }
        }
        handle_correct_queue->NextSymbol();
    }
}
compile_errcode SwitchStatement::Action() {
    int ret = COMPILE_OK;
    int state = 0;
    SymbolType expression_type;
    while (true) {
        SymbolName name = handle_correct_queue->GetCurrentName();
        switch (state) {
            case 0: {
                if (name == SWITCH_SYM) {
                    state = 1;
                    break;
                } else {
                    goto ERROR_SWITCH;
                }
            }
            case 1: {
                if (name == L_CIRCLE_BRACKET_SYM) {
                    state = 2;
                    break;
                } else {
                    goto ERROR_SWITCH;
                }
            }
            case 2: {
                if ((ret = m_expression.Action(expression_type)) == COMPILE_OK) {
                    m_expression.LogOutput();
                    state = 3;
                    break;
                } else {
                    goto ERROR_SWITCH;
                }
            }
            case 3: {
                if (name == R_CIRCLE_BRACKET_SYM) {
                    state = 4;
                    break;
                } else {
                    goto ERROR_SWITCH;
                }
            }
            case 4: {
                if (name == L_CURLY_BRACKET_SYM) {
                    state = 5;
                    break;
                } else {
                    goto ERROR_SWITCH;
                }
            }
            case 5: {
                if ((ret = m_switch_table.Action(expression_type)) == COMPILE_OK) {
                    m_switch_table.LogOutput();
                    state = 6;
                    break;
                } else {
                    goto ERROR_SWITCH;
                }
            }
            case 6: {
                if ((ret = m_default.Action()) == COMPILE_OK) {
                    m_default.LogOutput();
                    state = 7;
                    break;
                } else if (name == R_CURLY_BRACKET_SYM) {
                    state = 8;
                    break;
                } else {
                    goto ERROR_SWITCH;
                }
            }
            case 7: {
                if (name == R_CURLY_BRACKET_SYM) {
                    state = 8;
                    break;
                } else {
                    goto ERROR_SWITCH;
                }
            }
            case 8: return COMPILE_OK;
        }
        if (state != 3 && state != 6 && state != 7)
            handle_correct_queue->NextSymbol();
    }
    ERROR_SWITCH:
       return NOT_MATCH;
}

compile_errcode Statement::Action() {
    int ret = COMPILE_OK;
    SymbolType function_type;
    function_type = symbol_table_tree->GetCurrentTableType();
    string funtion_name = symbol_table_tree->GetCurrentTableName();
    SymbolName name = handle_correct_queue->GetCurrentName();
    handle_correct_queue->SetCacheLocate();
    if (name == L_CURLY_BRACKET_SYM) {
        handle_correct_queue->NextSymbol();
        m_statement_list_ptr = new StatementList;
        if ((ret = m_statement_list_ptr->Action()) == COMPILE_OK) {
            m_statement_list_ptr->LogOutput();
            delete(m_statement_list_ptr);
            name = handle_correct_queue->GetCurrentName();
            if (name == R_CURLY_BRACKET_SYM) {
                handle_correct_queue->NextSymbol();
                goto NO_SEMICOLON;
            } else {
                return NOT_MATCH;
            }
        } else {
            delete(m_statement_list_ptr);
            NOT_MATCH;
        }
    } else if ((ret = m_output_statement.Action()) == COMPILE_OK) {
        m_output_statement.LogOutput();
        goto SEMICOLON_CHECK;
    } else if (handle_correct_queue->SetCurrentLocate(), (ret = m_input_statement.Action()) == COMPILE_OK) {
        m_input_statement.LogOutput();
        goto SEMICOLON_CHECK;
    } else if (handle_correct_queue->SetCurrentLocate(), (ret = m_return_statement.Action(function_type, funtion_name)) == COMPILE_OK) {
        m_return_statement.LogOutput();
        goto SEMICOLON_CHECK;
    } else if (handle_correct_queue->SetCurrentLocate(), (ret = m_assign_statement.Action()) == COMPILE_OK) {
        m_assign_statement.LogOutput();
        goto SEMICOLON_CHECK;
    } else if (handle_correct_queue->SetCurrentLocate(), (ret = m_function_call.Action()) == COMPILE_OK) {
        m_function_call.LogOutput();
        goto SEMICOLON_CHECK;
    } else if (handle_correct_queue->SetCurrentLocate(), (ret = m_condition_statement.Action()) == COMPILE_OK) {
        m_condition_statement.LogOutput();
        goto NO_SEMICOLON;
    } else if (handle_correct_queue->SetCurrentLocate(), (ret = m_while_loop_statement.Action()) == COMPILE_OK) {
        m_while_loop_statement.LogOutput();
        goto NO_SEMICOLON;
    } else if (handle_correct_queue->SetCurrentLocate(), (ret = m_switch_statement.Action()) == COMPILE_OK) {
        m_switch_statement.LogOutput();
        goto NO_SEMICOLON;
    } else {
        name = handle_correct_queue->GetCurrentName();
        if (name == SEMICOLON_SYM) {
            handle_correct_queue->NextSymbol();
            string str("This is a empty statement");
            return COMPILE_OK;
        } else {
            return NOT_MATCH;
        }
    }
    SEMICOLON_CHECK:
        name = handle_correct_queue->GetCurrentName();
        if (name == SEMICOLON_SYM) {
            handle_correct_queue->NextSymbol();
            return COMPILE_OK;
        } else {
            fprintf(stderr, "expected a ':' in the end of statement\n");
            return COMPILE_OK;
        }
    NO_SEMICOLON:
        return COMPILE_OK;
}

compile_errcode StatementList::Action() {
    int ret = COMPILE_OK;
    while (true) {
        handle_correct_queue->SetCacheLocate();
        if ((ret = m_statement.Action()) == COMPILE_OK) {
            m_statement.LogOutput();
        } else {
            handle_correct_queue->SetCurrentLocate();
            return COMPILE_OK;
        }
    }
}

compile_errcode CompoundStatement::Action() {
    int ret = COMPILE_OK;
    SymbolName name = handle_correct_queue->GetCurrentName();
    if (name == CONST_SYM) {
        if ((ret = m_constant_declaration.Action()) == COMPILE_OK) {
            m_constant_declaration.LogOutput();
        }
    }
    if ((ret = m_variable_declaration.Action()) == COMPILE_OK) {
        m_variable_declaration.LogOutput();
    }
    m_statement_list.Action();
    return COMPILE_OK;
}

compile_errcode ArgumentList::Action(vector<SymbolType>& argument_type) {
    int ret = COMPILE_OK;
    int state = 0;
    while (true) {
        SymbolName name = handle_correct_queue->GetCurrentName();
        int line_number = handle_correct_queue->GetCurrentLine();
        int character_number = handle_correct_queue->GetCurrentCharacter();
        switch (state) {
            case 0: {
                if (name == R_CIRCLE_BRACKET_SYM) {
                    return COMPILE_OK;
                } else if (IsValidVariableType(name)) {
                    if (name == INT_SYM) {
                        argument_type.push_back(INT);
                    } else if (name == CHAR_SYM) {
                        argument_type.push_back(CHAR);
                    } else {
                        fprintf(stderr, "invalid function argument type\n");
                    }
                    state = 1;
                    m_type = name;
                    break;
                } else {
                    return NOT_MATCH;
                }
            }
            case 1: {
                if (name == IDENTIFIER_SYM) {
                    m_identifier_name = handle_correct_queue->GetCurrentValue<string>();
                    if (symbol_table_tree->FindTerm(m_identifier_name, true)) {
                        g_log_tools->SemanticErrorLogs(string("repeat definition identifier(para)"), m_identifier_name, line_number, character_number);
                    }
                    SymbolTableTerm term(m_identifier_name, PARAMETER, m_type);
                    symbol_table_tree->Insert(term);
                    state = 2;
                    break;
                } else {
                    return NOT_MATCH;
                }
            }
            case 2: {
                if (name == COMMA_SYM) {
                    state = 3;
                    break;
                } else {
                    return COMPILE_OK;
                }
            }
            case 3: {
                if (IsValidVariableType(name)) {
                    if (name == INT_SYM) {
                        argument_type.push_back(INT);
                    } else if (name == CHAR_SYM) {
                        argument_type.push_back(CHAR);
                    } else {
                        fprintf(stderr, "invalid function argument type\n");
                    }
                    state = 1;
                    m_type = name;
                    break;
                } else {
                    return NOT_MATCH;
                }
            }
        }
        handle_correct_queue->NextSymbol();
    }
}

compile_errcode ValueArgumentList::Action(vector<SymbolType>& argument_type) {
    int ret = COMPILE_OK;
    int state = 0;
    SymbolType expression_type;
    while (true) {
        SymbolName name = handle_correct_queue->GetCurrentName();
        switch (state) {
            case 0: {
                if (name == R_CIRCLE_BRACKET_SYM) {
                    return COMPILE_OK;
                } else if ((ret = m_expression.Action(expression_type)) == COMPILE_OK) {
                    argument_type.push_back(expression_type);
                    state = 1;
                    break;
                } else {
                    return NOT_MATCH;
                }
            }
            case 1: {
                if (name == COMMA_SYM) {
                    state = 2;
                    break;
                } else {
                    return COMPILE_OK;
                }
            }
            case 2: {
                if ((ret = m_expression.Action(expression_type)) == COMPILE_OK) {
                    argument_type.push_back(expression_type);
                    state = 1;
                    break;
                } else {
                    return NOT_MATCH;
                }
            }
        }
        if (state != 1)
            handle_correct_queue->NextSymbol();
    }
}

compile_errcode FunctionCall::Action() {
    int ret = COMPILE_OK;
    int state = 0;
    vector<SymbolType> argument_type;
    string identifier_name;
    while (true) {
        SymbolName name = handle_correct_queue->GetCurrentName();
        int line_number = handle_correct_queue->GetCurrentLine();
        int character_number = handle_correct_queue->GetCurrentCharacter();
        switch (state) {
            case 0: {
                if (name == IDENTIFIER_SYM) {
                    identifier_name = handle_correct_queue->GetCurrentValue<string>();
                    IdentifierCheck(identifier_name, line_number, character_number);
                    state = 1;
                    break;
                } else {
                    return NOT_MATCH;
                }
            }
            case 1: {
                if (name == L_CIRCLE_BRACKET_SYM) {
                    state = 2;
                    break;
                } else {
                    return NOT_MATCH;
                }
            }
            case 2: {
                if ((ret = m_value_argument_list.Action(argument_type)) == COMPILE_OK) {
                    ArgumentCheck(identifier_name, line_number, character_number, argument_type);
                    state = 3;
                    break;
                } else {
                    return NOT_MATCH;
                }
            }
            case 3: {
                if (name == R_CIRCLE_BRACKET_SYM) {
                    state = 4;
                    break;
                } else {
                    return NOT_MATCH;
                }
            }
            case 4: return COMPILE_OK;
        }
        if (state != 3)
            handle_correct_queue->NextSymbol();
    }
}

compile_errcode FunctionDefinition::Action() {
    int ret = COMPILE_OK;
    int state = 0;
    int return_value_number = 0;
    vector<SymbolType> argument_type;
    while (true) {
        SymbolName name = handle_correct_queue->GetCurrentName();
        int line_number = handle_correct_queue->GetCurrentLine();
        int character_number = handle_correct_queue->GetCurrentCharacter();
        switch (state) {
            case 0: {
                if (IsValidFunctionType(name)) {
                    state = 1;
                    m_type = name;
                    if (IsValidVariableType(name)) {
                        return_value_number = 1;        
                    } else {
                        return_value_number = 0;
                    }
                    break;
                } else {
                    return NOT_MATCH;
                }
            }
            case 1: {
                if (name == IDENTIFIER_SYM) {
                    m_identifier_name = handle_correct_queue->GetCurrentValue<string>();
                    if (symbol_table_tree->FindTerm(m_identifier_name, false)) {
                        m_valid = false;
                        g_log_tools->SemanticErrorLogs(string("repeat definition identifier(func)"), m_identifier_name, line_number, character_number);
                        m_identifier_name = "error_" + m_identifier_name + "_error";
                    } else {
                        if (symbol_table_tree->MatchKeyword(m_identifier_name)) {
                            m_valid = false;
                            g_log_tools->SemanticErrorLogs("identifier repeat with the keyword: " + m_identifier_name, "", line_number, character_number);
                            m_identifier_name = "error_" + m_identifier_name + "_error";
                        } else {
                            m_valid = true;
                        }
                    }
                    string previous_table_name = symbol_table_tree->GetCurrentTableName();
                    symbol_table_tree->InsertTable(m_identifier_name, Name2Type(m_type), previous_table_name);
                    symbol_table_tree->SetCurrentTableName(m_identifier_name);
                    state = 2;
                    break;
                } else {
                    return NOT_MATCH;
                }
            }
            case 2: {
                if (name == L_CIRCLE_BRACKET_SYM) {
                    state = 3;
                    break;
                } else {
                    return NOT_MATCH;
                }
            }
            case 3: {
                if ((ret = m_argument_list.Action(argument_type)) == COMPILE_OK) {
                    m_argument_list.LogOutput();
                    string previous_table_name = symbol_table_tree->GetCurrentPreviousTableName();
                    symbol_table_tree->SetCurrentTableName(previous_table_name);
                    SymbolTableTerm term(m_identifier_name, FUNCTION, m_type);
                    term.SetFuncInformation(m_argument_number);
                    symbol_table_tree->Insert(term);
                    symbol_table_tree->SetCurrentTableName(m_identifier_name);
                    state = 4;
                    break;
                } else {
                    return NOT_MATCH;
                }
            }
            case 4: {
                if (name == R_CIRCLE_BRACKET_SYM) {
                    state = 5;
                    break;
                } else {
                    return NOT_MATCH;
                }
            }
            case 5: {
                if (name == L_CURLY_BRACKET_SYM) {
                    state = 6;
                    break;
                } else {
                    return NOT_MATCH;
                }
            }
            case 6: {
                if ((ret = m_compound_statement.Action()) == COMPILE_OK) {
                    m_compound_statement.LogOutput();
                    state = 7;
                    break;
                } else {
                    return NOT_MATCH;
                }
            }
            case 7: {
                if (name == R_CURLY_BRACKET_SYM) {
                    int space_length = 0;
                    symbol_table_tree->GetTableSpaceLength(m_identifier_name, space_length);
                    handle_func_table->InsertTerm(m_identifier_name, space_length, return_value_number, argument_type);
                    symbol_table_tree->UpgradeAddress();
                    string previous_table_name = symbol_table_tree->GetCurrentPreviousTableName();
                    symbol_table_tree->SetCurrentTableName(previous_table_name);
                    state = 8;
                    break;
                } else {
                    return NOT_MATCH;
                }
            }
            case 8: return COMPILE_OK;
        }
        if (state != 4 && state != 7)
            handle_correct_queue->NextSymbol();
    }
}

compile_errcode MainFunction::Action() {
    int ret = COMPILE_OK;
    int state = 0;
    while (true) {
        SymbolName name = handle_correct_queue->GetCurrentName();
        switch (state) {
            case 0: {
                if (name == VOID_SYM) {
                    state = 1;
                    break;
                } else {
                    return NOT_MATCH;
                }
            }
            case 1: {
                if (name == MAIN_SYM) {
                    string previous_table_name = symbol_table_tree->GetCurrentTableName();
                    symbol_table_tree->InsertTable(string("main"), VOID, previous_table_name);
                    symbol_table_tree->SetCurrentTableName(string("main"));
                    state = 2;
                    break;
                } else {
                    return NOT_MATCH;
                }
            }
            case 2: {
                if (name == L_CIRCLE_BRACKET_SYM) {
                    state = 3;
                    break;
                } else {
                    return NOT_MATCH;
                }
            }
            case 3: {
                if (name == R_CIRCLE_BRACKET_SYM) {
                    state = 4;
                    break;
                } else {
                    return NOT_MATCH;
                }
            }
            case 4: {
                if (name == L_CURLY_BRACKET_SYM) {
                    state = 5;
                    break;
                } else {
                    return NOT_MATCH;
                }
            }
            case 5: {
                if ((ret = m_compound_statement.Action()) == COMPILE_OK) {
                    m_compound_statement.LogOutput();
                    state = 6;
                    break;
                } else {
                    return NOT_MATCH;
                }
            }
            case 6: {
                if (name == R_CURLY_BRACKET_SYM) {
                    int space_length = 0;
                    symbol_table_tree->GetTableSpaceLength(string("main"), space_length);
                    handle_func_table->InsertTerm(string("main"), space_length, 0, vector<SymbolType>());
                    string previous_table_name = symbol_table_tree->GetCurrentPreviousTableName();
                    symbol_table_tree->SetCurrentTableName(previous_table_name);
                    state = 7;
                    break;
                } else {
                    return NOT_MATCH;
                }
            }
            case 7: return COMPILE_OK;
        }
        if (state != 6)
            handle_correct_queue->NextSymbol();
    }
}

compile_errcode Program::Action() {
    int ret = COMPILE_OK;
    SymbolName name = handle_correct_queue->GetCurrentName();
    if (name == CONST_SYM) {
        if ((ret = m_constant_declaration.Action()) == COMPILE_OK) {
            m_constant_declaration.LogOutput();
        }
    }
    if ((ret = m_variable_declaration.Action()) == COMPILE_OK) {
        m_variable_declaration.LogOutput();
    }
    symbol_table_tree->UpgradeAddress();
    while (true) {
        handle_correct_queue->SetCacheLocate();
        if ((ret = m_function_definition.Action()) == COMPILE_OK) {
            m_function_definition.LogOutput();
        } else {
            handle_correct_queue->SetCurrentLocate();
            break;
        }
    }
    if ((ret = m_main_function.Action()) == COMPILE_OK) {
        m_main_function.LogOutput();
    }
    if (g_log_tools->GetSemanticFlag() == false)
        ret = SEMANTIC_ERROR;
    return ret;
}
