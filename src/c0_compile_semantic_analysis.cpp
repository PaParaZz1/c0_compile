#include <string>
#include <iostream>
#include "c0_compile_utils.hpp"
#include "c0_compile_symbol.hpp"
#include "c0_compile_lexical_analysis.hpp"
#include "c0_compile_gramma.hpp"

using std::string;
using std::cout;
using std::endl;

extern SymbolTableTree* symbol_table_tree;
extern SymbolQueue* handle_symbol_queue;
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

FILE* semantic_error = fopen("semantic_error.txt", "w");
void SemanticErrorLog(string error_type, string content, int line_number, int character_number) {
    if (semantic_error == NULL) {
        fprintf(stderr, "%s error: '%s' in line %d character %d\n", error_type.c_str(), content.c_str(), line_number, character_number);
    } else {
        fprintf(semantic_error, "%s error: '%s' in line %d character %d\n", error_type.c_str(),  content.c_str(), line_number, character_number);
    }
}

compile_errcode Factor::Action() {
    int ret = COMPILE_OK;
    SymbolName name = handle_correct_queue->GetCurrentName();
    switch (name) {
        case INTERGER_SYM: break;
        case CHARACTER_SYM: break;
        case IDENTIFIER_SYM: {
            handle_correct_queue->SetCacheLocate();
            handle_correct_queue->NextSymbol();
            name = handle_correct_queue->GetCurrentName();
            if (name == L_SQUARE_BRACKET_SYM) {
                handle_correct_queue->NextSymbol();
                if ((ret = m_expression.Action()) == COMPILE_OK) {
                    // m_expression.LogOutput();
                    name = handle_correct_queue->GetCurrentName();
                    if (name == R_SQUARE_BRACKET_SYM) {
                        break;
                    } else {
                        return NOT_MATCH;
                    }
                } else {
                    return NOT_MATCH;
                }
            } else if (name == L_CIRCLE_BRACKET_SYM) {
                handle_correct_queue->NextSymbol();
                if ((ret = m_value_argument_list.Action()) == COMPILE_OK) {
                    // m_value_argument_list.LogOutput();
                    name = handle_correct_queue->GetCurrentName();
                    if (name == R_CIRCLE_BRACKET_SYM) {
                        string str = "This is a function call";
                        GRAMMA_LOG(str);
                        break;
                    } else {
                        return NOT_MATCH;
                    }
                } else {
                    return NOT_MATCH;
                }
            } else {
                handle_correct_queue->SetCurrentLocate();
                break;
            }
        }
        case L_CIRCLE_BRACKET_SYM: {
            handle_correct_queue->NextSymbol();
            if ((ret = m_expression.Action()) == COMPILE_OK) {
                // m_expression.LogOutput();
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
    }
    handle_correct_queue->NextSymbol();
    return COMPILE_OK;
}

compile_errcode Term::Action() {
    m_factor = new Factor;
    int ret = COMPILE_OK;
    int state = 0;
    while (true) {
        SymbolName name = handle_correct_queue->GetCurrentName();
        switch (state) {
            case 0: {
                if ((ret = m_factor->Action()) == COMPILE_OK) {
                    state = 1;
                    break;
                } else {
                    delete(m_factor);
                    return NOT_MATCH;
                }
            }
            case 1: {
                if (IsMultiplyOperation(name)) {
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

compile_errcode Expression::Action() {
    int ret = COMPILE_OK;
    int state = 0;
    while (true) {
        SymbolName name = handle_correct_queue->GetCurrentName();
        switch (state) {
            case 0: {
                if (IsAddOperation(name)) {
                    state = 0;
                    break;
                } else if ((ret = m_term.Action()) == COMPILE_OK) {
                    m_term.LogOutput();
                    state = 1;
                    break;
                } else {
                    return NOT_MATCH;
                }
            }
            case 1: {
                if (IsAddOperation(name)) {
                    state = 2;
                    break;
                } else {
                    return COMPILE_OK;
                }
            }
            case 2: {
                if ((ret = m_term.Action()) == COMPILE_OK) {
                    m_term.LogOutput();
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
                    if (symbol_table_tree->Find(m_identifier_name, true)) {
                        SemanticErrorLog(string("repeat definition identifier"), m_identifier_name, line_number, character_number);
                        m_valid = false;
                    } else {
                        m_valid = true;
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
                        SemanticErrorLog(string("invalid assign match(int)"), m_identifier_name, line_number, character_number);
                        break;
                    }
                    if (m_type == CHAR_SYM && name != CHARACTER_SYM) {
                        SemanticErrorLog(string("invalid assign match(char)"), m_identifier_name, line_number, character_number);
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
                    if (symbol_table_tree->Find(m_identifier_name, true)) {
                        SemanticErrorLog(string("repeat definition identifier"), m_identifier_name, line_number, character_number);
                        m_valid = false;
                    } else {
                        m_valid = true;
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
                        SemanticErrorLog(string("invalid array length"), m_identifier_name, line_number, character_number);
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

compile_errcode ReturnStatement::Action() {
    int ret = COMPILE_OK;
    int state = 0;
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
                    return COMPILE_OK;
                } else {
                    return NOT_MATCH;
                }
            }
            case 2: {
                if ((ret = m_expression.Action()) == COMPILE_OK) {
                    state = 3;
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
                    GRAMMA_LOG(str);
                    state = 3;
                    break;
                } else if ((ret = m_expression.Action()) == COMPILE_OK) {
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
                if ((ret = m_expression.Action()) == COMPILE_OK) {
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
    int state = 0;
    while (true) {
        SymbolName name = handle_correct_queue->GetCurrentName();
        switch (state) {
            case 0: {
                if (name == IDENTIFIER_SYM) {
                    state = 1;
                    break;
                } else {
                    return NOT_MATCH;
                }
            }
            case 1: {
                if (name == ASSIGN_SYM) {
                    state = 2;
                    break;
                } else if (name == L_SQUARE_BRACKET_SYM) {
                    state = 11;
                    break;
                } else {
                    return NOT_MATCH;
                }
            }
            case 2: {
                if ((ret = m_expression.Action()) == COMPILE_OK) {
                    state = 3;
                    break;
                } else {
                    return NOT_MATCH;
                }
            }
            case 3: return COMPILE_OK;
            case 11: {
                if ((ret = m_expression.Action()) == COMPILE_OK) {
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
        if (state != 3 && state != 12)
            handle_correct_queue->NextSymbol();
    }
}

compile_errcode Condition::Action() {
    int ret = COMPILE_OK;
    int state = 0;
    while (true) {
        SymbolName name = handle_correct_queue->GetCurrentName();
        switch (state) {
            case 0: {
                if ((ret = m_expression.Action()) == COMPILE_OK) {
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
                if ((ret = m_expression.Action()) == COMPILE_OK) {
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

compile_errcode SwitchChildStatement::Action() {
    int ret = COMPILE_OK;
    int state = 0;
    m_statement_ptr = new Statement;
    while (true) {
        SymbolName name = handle_correct_queue->GetCurrentName();
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

compile_errcode SwitchTable::Action() {
    int ret = 0;
    int count = 0;
    while (true) {
        if ((ret = m_switch_child_statement.Action()) == COMPILE_OK) {
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
                if (name == R_CURLY_BRACKET_SYM) {
                    return COMPILE_OK;
                } else {
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
        }
        handle_correct_queue->NextSymbol();
    }
}
compile_errcode SwitchStatement::Action() {
    int ret = COMPILE_OK;
    int state = 0;
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
                if (name = L_CIRCLE_BRACKET_SYM) {
                    state = 2;
                    break;
                } else {
                    goto ERROR_SWITCH;
                }
            }
            case 2: {
                if ((ret = m_expression.Action()) == COMPILE_OK) {
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
                if ((ret = m_switch_table.Action()) == COMPILE_OK) {
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
    } else if (handle_correct_queue->SetCurrentLocate(), (ret = m_return_statement.Action()) == COMPILE_OK) {
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
            GRAMMA_LOG(str);
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

compile_errcode ArgumentList::Action(int& argument_number) {
    int ret = COMPILE_OK;
    int state = 0;
    argument_number = 0;
    while (true) {
        SymbolName name = handle_correct_queue->GetCurrentName();
        switch (state) {
            case 0: {
                if (name == R_CIRCLE_BRACKET_SYM) {
                    return COMPILE_OK;
                } else if (IsValidVariableType(name)) {
                    state = 1;
                    break;
                } else {
                    return NOT_MATCH;
                }
            }
            case 1: {
                if (name == IDENTIFIER_SYM) {
                    state = 2;
                    argument_number++;
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
                    state = 1;
                    break;
                } else {
                    return NOT_MATCH;
                }
            }
        }
        handle_correct_queue->NextSymbol();
    }
}

compile_errcode ValueArgumentList::Action() {
    int ret = COMPILE_OK;
    int state = 0;
    while (true) {
        SymbolName name = handle_correct_queue->GetCurrentName();
        switch (state) {
            case 0: {
                if (name == R_CIRCLE_BRACKET_SYM) {
                    return COMPILE_OK;
                } else if ((ret = m_expression.Action()) == COMPILE_OK) {
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
                if ((ret = m_expression.Action()) == COMPILE_OK) {
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
    while (true) {
        SymbolName name = handle_correct_queue->GetCurrentName();
        switch (state) {
            case 0: {
                if (name == IDENTIFIER_SYM) {
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
                if ((ret = m_value_argument_list.Action()) == COMPILE_OK) {
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
    while (true) {
        SymbolName name = handle_correct_queue->GetCurrentName();
        int line_number = handle_correct_queue->GetCurrentLine();
        int character_number = handle_correct_queue->GetCurrentCharacter();
        switch (state) {
            case 0: {
                if (name == VOID_SYM || name == INT_SYM || name == CHAR_SYM) {
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
                    if (symbol_table_tree->Find(m_identifier_name, false)) {
                        m_valid = false;
                        SemanticErrorLog(string("repeat definition identifier(func)"), m_identifier_name, line_number, character_number);
                        m_identifier_name = "error_" + m_identifier_name + "_error";
                        string previous_table_name = symbol_table_tree->GetCurrentTableName();
                        symbol_table_tree->CreateTable(m_identifier_name, previous_table_name);
                        symbol_table_tree->SetCurrentTableName(m_identifier_name);
                    } else {
                        string previous_table_name = symbol_table_tree->GetCurrentTableName();
                        symbol_table_tree->CreateTable(m_identifier_name, previous_table_name);
                        symbol_table_tree->SetCurrentTableName(m_identifier_name);
                        m_valid = true;
                    }
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
                if ((ret = m_argument_list.Action(m_argument_number)) == COMPILE_OK) {
                    m_argument_list.LogOutput();
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
                    string previous_table_name = symbol_table_tree->GetCurrentPreviousTableName();
                    symbol_table_tree->SetCurrentTableName(previous_table_name);
                    SymbolTableTerm term(m_identifier_name, FUNCTION, m_type);
                    term.SetFuncInformation(m_argument_number);
                    symbol_table_tree->Insert(term);
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
    return ret;
}
