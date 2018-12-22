#include <string>
#include <iostream>
#include "c0_compile_utils.hpp"
#include "c0_compile_symbol.hpp"
#include "c0_compile_lexical_analysis.hpp"
#include "c0_compile_gramma.hpp"

using std::string;
using std::cout;
using std::endl;

extern SymbolQueue* handle_symbol_queue;
FILE* log_gramma = fopen("gramma_log.txt", "w");

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

FILE* gramma_error = fopen("gramma_error.txt", "w");
void GrammaErrorLogs(string error_content) {
    cout<<"bug ++"<<endl;
    int line_number = handle_symbol_queue->GetCurrentLine();
    int character_number = handle_symbol_queue->GetCurrentCharacter();
    if (gramma_error == NULL) {
        fprintf(stderr, "error: '%s' in line %d character %d\n", error_content.c_str(), line_number, character_number);
    } else {
        fprintf(gramma_error, "error: '%s' in line %d character %d\n", error_content.c_str(), line_number, character_number);
    }
}

compile_errcode Factor::Parse() {
    int ret = COMPILE_OK;
    SymbolName name = handle_symbol_queue->GetCurrentName();
    switch (name) {
        case INTERGER_SYM: break;
        case CHARACTER_SYM: break;
        case IDENTIFIER_SYM: {
            handle_symbol_queue->SetCacheLocate();
            handle_symbol_queue->NextSymbol();
            name = handle_symbol_queue->GetCurrentName();
            if (name == L_SQUARE_BRACKET_SYM) {
                handle_symbol_queue->NextSymbol();
                if ((ret = m_expression.Parse()) == COMPILE_OK) {
                    // m_expression.LogOutput();
                    name = handle_symbol_queue->GetCurrentName();
                    if (name == R_SQUARE_BRACKET_SYM) {
                        break;
                    } else {
                        GrammaErrorLogs("expected a ']'");
                        return NOT_MATCH;
                    }
                } else {
                    GrammaErrorLogs("expected a valid array index expression");
                    return NOT_MATCH;
                }
            } else if (name == L_CIRCLE_BRACKET_SYM) {
                handle_symbol_queue->NextSymbol();
                if ((ret = m_value_argument_list.Parse()) == COMPILE_OK) {
                    // m_value_argument_list.LogOutput();
                    name = handle_symbol_queue->GetCurrentName();
                    if (name == R_CIRCLE_BRACKET_SYM) {
                        string str = "This is a function call";
                        GRAMMA_LOG(str);
                        break;
                    } else {
                        GrammaErrorLogs("expected a ')'");
                        return NOT_MATCH;
                    }
                } else {
                    GrammaErrorLogs("expected a valid value argument list");
                    return NOT_MATCH;
                }
            } else {
                handle_symbol_queue->SetCurrentLocate();
                break;
            }
        }
        case L_CIRCLE_BRACKET_SYM: {
            handle_symbol_queue->NextSymbol();
            if ((ret = m_expression.Parse()) == COMPILE_OK) {
                // m_expression.LogOutput();
                name = handle_symbol_queue->GetCurrentName();
                if (name == R_CIRCLE_BRACKET_SYM) {
                    break;
                } else {
                    GrammaErrorLogs("expected a ')'");
                    return NOT_MATCH;
                }
            } else {
                GrammaErrorLogs("expected a valid expression in bracket");
                return NOT_MATCH;
            }
        }
        default: {
            GrammaErrorLogs("invalid symbol in factor parse");
            return NOT_MATCH;
        }
    }
    handle_symbol_queue->NextSymbol();
    return COMPILE_OK;
}

compile_errcode Term::Parse() {
    m_factor = new Factor;
    int ret = COMPILE_OK;
    int state = 0;
    while (true) {
        SymbolName name = handle_symbol_queue->GetCurrentName();
        switch (state) {
            case 0: {
                if ((ret = m_factor->Parse()) == COMPILE_OK) {
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
            handle_symbol_queue->NextSymbol();
    }
}

compile_errcode Expression::Parse() {
    int ret = COMPILE_OK;
    int state = 0;
    while (true) {
        SymbolName name = handle_symbol_queue->GetCurrentName();
        switch (state) {
            case 0: {
                if (IsAddOperation(name)) {
                    state = 0;
                    break;
                } else if ((ret = m_term.Parse()) == COMPILE_OK) {
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
                if ((ret = m_term.Parse()) == COMPILE_OK) {
                    m_term.LogOutput();
                    state = 1;
                    break;
                } else {
                    GrammaErrorLogs("expected a valid term");
                    return NOT_MATCH;
                }
            }
        }
        if (state != 1) {
            handle_symbol_queue->NextSymbol();
        }
    }
}

compile_errcode ConstantDefinition::Parse() {
    int state = 0;
    int ret = 0;
    while (true) {
        SymbolName name = handle_symbol_queue->GetCurrentName();
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
                    break;
                } else {
                    return INVALID_TYPE_ERROR;
                }
            }
            case 2: {
                if (name == IDENTIFIER_SYM) {
                    state = 3;
                    break;
                } else {
                    GrammaErrorLogs("expected a valid identifier");
                    return NOT_MATCH;
                }
            }
            case 3: {
                if (name == ASSIGN_SYM) {
                    state = 4;
                } else {
                    GrammaErrorLogs("expected a valid assign symbole");
                    return NOT_MATCH;
                }
                break;
            }
            case 4: {
                if (name == INTERGER_SYM || name == CHARACTER_SYM) {
                    state = 5;
                    break;
                } else {
                    GrammaErrorLogs("expected valid const init");
                    return NOT_MATCH;
                }
            }
            case 5: {
                if (name == COMMA_SYM) {
                    state = 2;
                } else if (name == SEMICOLON_SYM) {
                    state = 6;
                } else {
                    GrammaErrorLogs("expected a ',' or ';'");
                    return NOT_MATCH;
                }
                break;
            }
            case 6: return COMPILE_OK;
        }
        handle_symbol_queue->NextSymbol();
    }
}

compile_errcode ConstantDeclaration::Parse() {
    int ret = 0;
    int correct_count = 0;
    while (true) {
        SymbolName name = handle_symbol_queue->GetCurrentName();
        if (name == CONST_SYM) {
            if ((ret = m_constant_definition.Parse()) == COMPILE_OK) {
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

compile_errcode VariableDefinition::Parse() {
    int state = 0;
    while (true) {
        SymbolName name = handle_symbol_queue->GetCurrentName();
        switch (state) {
            case 0: {
                if (IsValidVariableType(name)) {
                    state = 1;
                    break;
                } else {
                    return NOT_MATCH;
                }
            }
            case 1: {
                if (name == IDENTIFIER_SYM) {
                    state = 2;
                    break;
                } else {
                    GrammaErrorLogs("expected a valid identifier");
                    return NOT_MATCH;
                }
            }
            case 2: {
                if (name == L_SQUARE_BRACKET_SYM) {
                    state = 11;
                    break;
                } else if (name == COMMA_SYM) {
                    state = 1;
                    break;
                } else if (name == SEMICOLON_SYM) {
                    state = 3;
                    break;
                } else {
                    GrammaErrorLogs("expected a '[' or ',' or ';'");
                    return NOT_MATCH;
                }
            }
            case 3: return COMPILE_OK;
            case 11: {
                if (name == INTERGER_SYM) {
                    state = 12;
                    break;
                } else {
                    GrammaErrorLogs("expected a valid identifier");
                    return NOT_MATCH;
                }
            }
            case 12: {
                if (name == R_SQUARE_BRACKET_SYM) {
                    state = 13;
                    break;
                } else {
                    GrammaErrorLogs("expected a ']'");
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
                    GrammaErrorLogs("expected a ',' or ';'");
                    return NOT_MATCH;
                }
            }
        }
        handle_symbol_queue->NextSymbol();
    }
}

compile_errcode VariableDeclaration::Parse() {
    int ret = 0;
    int correct_count = 0;
    while (true) {
        handle_symbol_queue->SetCacheLocate();
        SymbolName name = handle_symbol_queue->GetCurrentName();
        if (IsValidVariableType(name)) {
            handle_symbol_queue->NextSymbol();
            name = handle_symbol_queue->GetCurrentName();
            if (name == IDENTIFIER_SYM) {
                handle_symbol_queue->NextSymbol();
                name = handle_symbol_queue->GetCurrentName();
                if (name == L_CIRCLE_BRACKET_SYM) {
                    handle_symbol_queue->SetCurrentLocate();
                    break;
                } else {
                    handle_symbol_queue->SetCurrentLocate();
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
        if ((ret = m_variable_definition.Parse()) == COMPILE_OK) {
            m_variable_definition.LogOutput();
            correct_count++;
        } else {
            return NOT_MATCH;
        }
    }
    return NOT_MATCH;
}

compile_errcode InputStatement::Parse() {
    int ret = COMPILE_OK;
    int state = 0;
    while (true) {
        SymbolName name = handle_symbol_queue->GetCurrentName();
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
                    GrammaErrorLogs("expected a '('");
                    return NOT_MATCH;
                }
            }
            case 2: {
                if (name == IDENTIFIER_SYM) {
                    state = 3;
                    break;
                } else {
                    GrammaErrorLogs("expected a identifier in input statement");
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
                    GrammaErrorLogs("expected a ',' or ')'");
                    return NOT_MATCH;
                }
            }
            case 4: return COMPILE_OK;
        }
        handle_symbol_queue->NextSymbol();
    }
}

compile_errcode ReturnStatement::Parse() {
    int ret = COMPILE_OK;
    int state = 0;
    while (true) {
        SymbolName name = handle_symbol_queue->GetCurrentName();
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
                if ((ret = m_expression.Parse()) == COMPILE_OK) {
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
            handle_symbol_queue->NextSymbol();
    }
}

compile_errcode OutputStatement::Parse() {
    int ret = COMPILE_OK;
    int state = 0;
    while (true) {
        SymbolName name = handle_symbol_queue->GetCurrentName();
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
                } else if ((ret = m_expression.Parse()) == COMPILE_OK) {
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
                if ((ret = m_expression.Parse()) == COMPILE_OK) {
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
            handle_symbol_queue->NextSymbol();
    }
}

compile_errcode AssignStatement::Parse() {
    int ret = COMPILE_OK;
    int state = 0;
    while (true) {
        SymbolName name = handle_symbol_queue->GetCurrentName();
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
                if ((ret = m_expression.Parse()) == COMPILE_OK) {
                    state = 3;
                    break;
                } else {
                    return NOT_MATCH;
                }
            }
            case 3: return COMPILE_OK;
            case 11: {
                if ((ret = m_expression.Parse()) == COMPILE_OK) {
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
            handle_symbol_queue->NextSymbol();
    }
}

compile_errcode Condition::Parse() {
    int ret = COMPILE_OK;
    int state = 0;
    while (true) {
        SymbolName name = handle_symbol_queue->GetCurrentName();
        switch (state) {
            case 0: {
                if ((ret = m_expression.Parse()) == COMPILE_OK) {
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
                if ((ret = m_expression.Parse()) == COMPILE_OK) {
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
            handle_symbol_queue->NextSymbol();
    }
}

compile_errcode ConditionStatement::Parse() {
    int ret = COMPILE_OK;
    int state = 0;
    m_statement_ptr = new Statement;
    while (true) {
        SymbolName name = handle_symbol_queue->GetCurrentName();
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
                if ((ret = m_condition.Parse()) == COMPILE_OK) {
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
                if ((ret = m_statement_ptr->Parse()) == COMPILE_OK) {
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
            handle_symbol_queue->NextSymbol();
    }
    CORRECT_IF:
        delete(m_statement_ptr);
        return COMPILE_OK;
    ERROR_IF:
        delete(m_statement_ptr);
        return NOT_MATCH;
}

compile_errcode WhileLoopStatement::Parse() {
    int ret = COMPILE_OK;
    int state = 0;
    m_statement_ptr = new Statement;
    while (true) {
        SymbolName name = handle_symbol_queue->GetCurrentName();
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
                if ((ret = m_condition.Parse()) == COMPILE_OK) {
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
                if ((ret = m_statement_ptr->Parse()) == COMPILE_OK) {
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
            handle_symbol_queue->NextSymbol();
    }
    CORRECT_WHILE:
        delete(m_statement_ptr);
        return COMPILE_OK;
    ERROR_WHILE:
        delete(m_statement_ptr);
        return NOT_MATCH;
}

compile_errcode SwitchChildStatement::Parse() {
    int ret = COMPILE_OK;
    int state = 0;
    m_statement_ptr = new Statement;
    while (true) {
        SymbolName name = handle_symbol_queue->GetCurrentName();
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
                if ((ret = m_statement_ptr->Parse()) == COMPILE_OK) {
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
            handle_symbol_queue->NextSymbol();
    }
    CORRECT_SWITCH_CHILD:
        delete(m_statement_ptr);
        return COMPILE_OK;
    ERROR_SWITCH_CHILD:
        delete(m_statement_ptr);
        return NOT_MATCH;
}

compile_errcode SwitchTable::Parse() {
    int ret = 0;
    int count = 0;
    while (true) {
        if ((ret = m_switch_child_statement.Parse()) == COMPILE_OK) {
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

compile_errcode Default::Parse() {
    int ret = COMPILE_OK;
    int state = 0;
    while (true) {
        SymbolName name = handle_symbol_queue->GetCurrentName();
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
                    if ((ret = m_statement_ptr->Parse()) == COMPILE_OK) {
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
        handle_symbol_queue->NextSymbol();
    }
}
compile_errcode SwitchStatement::Parse() {
    int ret = COMPILE_OK;
    int state = 0;
    while (true) {
        SymbolName name = handle_symbol_queue->GetCurrentName();
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
                if ((ret = m_expression.Parse()) == COMPILE_OK) {
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
                if ((ret = m_switch_table.Parse()) == COMPILE_OK) {
                    m_switch_table.LogOutput();
                    state = 6;
                    break;
                } else {
                    goto ERROR_SWITCH;
                }
            }
            case 6: {
                if ((ret = m_default.Parse()) == COMPILE_OK) {
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
            handle_symbol_queue->NextSymbol();
    }
    ERROR_SWITCH:
       return NOT_MATCH;
}

compile_errcode Statement::Parse() {
    int ret = COMPILE_OK;
    SymbolName name = handle_symbol_queue->GetCurrentName();
    handle_symbol_queue->SetCacheLocate();
    if (name == L_CURLY_BRACKET_SYM) {
        handle_symbol_queue->NextSymbol();
        m_statement_list_ptr = new StatementList;
        if ((ret = m_statement_list_ptr->Parse()) == COMPILE_OK) {
            m_statement_list_ptr->LogOutput();
            delete(m_statement_list_ptr);
            name = handle_symbol_queue->GetCurrentName();
            if (name == R_CURLY_BRACKET_SYM) {
                handle_symbol_queue->NextSymbol();
                goto NO_SEMICOLON;
            } else {
                return NOT_MATCH;
            }
        } else {
            delete(m_statement_list_ptr);
            NOT_MATCH;
        }
    } else if ((ret = m_output_statement.Parse()) == COMPILE_OK) {
        m_output_statement.LogOutput();
        goto SEMICOLON_CHECK;
    } else if (handle_symbol_queue->SetCurrentLocate(), (ret = m_input_statement.Parse()) == COMPILE_OK) {
        m_input_statement.LogOutput();
        goto SEMICOLON_CHECK;
    } else if (handle_symbol_queue->SetCurrentLocate(), (ret = m_return_statement.Parse()) == COMPILE_OK) {
        m_return_statement.LogOutput();
        goto SEMICOLON_CHECK;
    } else if (handle_symbol_queue->SetCurrentLocate(), (ret = m_assign_statement.Parse()) == COMPILE_OK) {
        m_assign_statement.LogOutput();
        goto SEMICOLON_CHECK;
    } else if (handle_symbol_queue->SetCurrentLocate(), (ret = m_function_call.Parse()) == COMPILE_OK) {
        m_function_call.LogOutput();
        goto SEMICOLON_CHECK;
    } else if (handle_symbol_queue->SetCurrentLocate(), (ret = m_condition_statement.Parse()) == COMPILE_OK) {
        m_condition_statement.LogOutput();
        goto NO_SEMICOLON;
    } else if (handle_symbol_queue->SetCurrentLocate(), (ret = m_while_loop_statement.Parse()) == COMPILE_OK) {
        m_while_loop_statement.LogOutput();
        goto NO_SEMICOLON;
    } else if (handle_symbol_queue->SetCurrentLocate(), (ret = m_switch_statement.Parse()) == COMPILE_OK) {
        m_switch_statement.LogOutput();
        goto NO_SEMICOLON;
    } else {
        name = handle_symbol_queue->GetCurrentName();
        if (name == SEMICOLON_SYM) {
            handle_symbol_queue->NextSymbol();
            string str("This is a empty statement");
            GRAMMA_LOG(str);
            return COMPILE_OK;
        } else {
            return NOT_MATCH;
        }
    }
    SEMICOLON_CHECK:
        name = handle_symbol_queue->GetCurrentName();
        if (name == SEMICOLON_SYM) {
            handle_symbol_queue->NextSymbol();
            return COMPILE_OK;
        } else {
            fprintf(stderr, "expected a ':' in the end of statement\n");
            return COMPILE_OK;
        }
    NO_SEMICOLON:
        return COMPILE_OK;
}

compile_errcode StatementList::Parse() {
    int ret = COMPILE_OK;
    while (true) {
        handle_symbol_queue->SetCacheLocate();
        if ((ret = m_statement.Parse()) == COMPILE_OK) {
            m_statement.LogOutput();
        } else {
            handle_symbol_queue->SetCurrentLocate();
            return COMPILE_OK;
        }
    }
}

compile_errcode CompoundStatement::Parse() {
    int ret = COMPILE_OK;
    SymbolName name = handle_symbol_queue->GetCurrentName();
    if (name == CONST_SYM) {
        if ((ret = m_constant_declaration.Parse()) == COMPILE_OK) {
            m_constant_declaration.LogOutput();
        }
    }
    if ((ret = m_variable_declaration.Parse()) == COMPILE_OK) {
        m_variable_declaration.LogOutput();
    }
    m_statement_list.Parse();
    return COMPILE_OK;
}

compile_errcode ArgumentList::Parse() {
    int ret = COMPILE_OK;
    int state = 0;
    while (true) {
        SymbolName name = handle_symbol_queue->GetCurrentName();
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
        handle_symbol_queue->NextSymbol();
    }
}

compile_errcode ValueArgumentList::Parse() {
    int ret = COMPILE_OK;
    int state = 0;
    while (true) {
        SymbolName name = handle_symbol_queue->GetCurrentName();
        switch (state) {
            case 0: {
                if (name == R_CIRCLE_BRACKET_SYM) {
                    return COMPILE_OK;
                } else if ((ret = m_expression.Parse()) == COMPILE_OK) {
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
                if ((ret = m_expression.Parse()) == COMPILE_OK) {
                    state = 1;
                    break;
                } else {
                    return NOT_MATCH;
                }
            }
        }
        if (state != 1)
            handle_symbol_queue->NextSymbol();
    }
}

compile_errcode FunctionCall::Parse() {
    int ret = COMPILE_OK;
    int state = 0;
    while (true) {
        SymbolName name = handle_symbol_queue->GetCurrentName();
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
                if ((ret = m_value_argument_list.Parse()) == COMPILE_OK) {
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
            handle_symbol_queue->NextSymbol();
    }
}

compile_errcode FunctionDefinition::Parse() {
    int ret = COMPILE_OK;
    int state = 0;
    while (true) {
        SymbolName name = handle_symbol_queue->GetCurrentName();
        switch (state) {
            case 0: {
                if (name == VOID_SYM || name == INT_SYM || name == CHAR_SYM) {
                    state = 1;
                    break;
                } else {
                    return NOT_MATCH;
                }
            }
            case 1: {
                if (name == IDENTIFIER_SYM) {
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
                if ((ret = m_argument_list.Parse()) == COMPILE_OK) {
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
                if ((ret = m_compound_statement.Parse()) == COMPILE_OK) {
                    m_compound_statement.LogOutput();
                    state = 7;
                    break;
                } else {
                    return NOT_MATCH;
                }
            }
            case 7: {
                if (name == R_CURLY_BRACKET_SYM) {
                    state = 8;
                    break;
                } else {
                    return NOT_MATCH;
                }
            }
            case 8: return COMPILE_OK;
        }
        if (state != 4 && state != 7)
            handle_symbol_queue->NextSymbol();
    }
}

compile_errcode MainFunction::Parse() {
    int ret = COMPILE_OK;
    int state = 0;
    while (true) {
        SymbolName name = handle_symbol_queue->GetCurrentName();
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
                if ((ret = m_compound_statement.Parse()) == COMPILE_OK) {
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
            handle_symbol_queue->NextSymbol();
    }
}

compile_errcode Program::Parse() {
    int ret = COMPILE_OK;
    SymbolName name = handle_symbol_queue->GetCurrentName();
    if (name == CONST_SYM) {
        if ((ret = m_constant_declaration.Parse()) == COMPILE_OK) {
            m_constant_declaration.LogOutput();
        }
    }
    if ((ret = m_variable_declaration.Parse()) == COMPILE_OK) {
        m_variable_declaration.LogOutput();
    }
    while (true) {
        handle_symbol_queue->SetCacheLocate();
        if ((ret = m_function_definition.Parse()) == COMPILE_OK) {
            m_function_definition.LogOutput();
        } else {
            handle_symbol_queue->SetCurrentLocate();
            break;
        }
    }
    if ((ret = m_main_function.Parse()) == COMPILE_OK) {
        m_main_function.LogOutput();
    }
    return ret;
}
