#include <string>
#include <iostream>
#include "c0_compile_utils.hpp"
#include "c0_compile_symbol.hpp"
#include "c0_compile_lexical_analysis.hpp"
#include "c0_compile_gramma_analysis.hpp"

using std::string;
using std::cout;
using std::endl;

extern SymbolTable* handle_symbol_table;
extern SymbolQueue* handle_symbol_queue;
FILE* log_fp = fopen("log.txt", "w");

compile_errcode Identifier::Parse() {
    if (m_is_definition) {
        return COMPILE_OK;
    } else {
        string name = handle_symbol_queue->GetCurrentValue<string>();
        if (handle_symbol_table->Find(name)) {
            // (TODO)
            return COMPILE_OK;
        } else {
            return UNDEFINED_IDENTIFIER_ERROR;
        }
    }
}

compile_errcode ConstantDefinition::Parse() {
    int state = 0;
    int ret = 0;
    while (true) {
        SymbolName symbol_name = handle_symbol_queue->GetCurrentName();
        switch (state) {
            case 0: {
                if (symbol_name == CONST_SYM) {
                    state = 1;
                    break;
                } else {
                    return NOT_MATCH;
                }
            }
            case 1: {
                if (symbol_name == INT_SYM || symbol_name == CHAR_SYM) {
                    m_type = symbol_name;
                    state = 2;
                    break;
                } else {
                    return INVALID_TYPE_ERROR;
                }
            }
            case 2: {
                if (symbol_name == IDENTIFIER_SYM) {
                    if ((ret = m_identifier.Parse()) == COMPILE_OK) {
                        state = 3;
                        m_identifier_name = handle_symbol_queue->GetCurrentValue<string>();
                    } else {
                        // (TODO)
                    }
                }
                break;
            }
            case 3: {
                if (symbol_name == ASSIGN_SYM) {
                    state = 4;
                } else {
                    // (TODO)
                }
                break;
            }
            case 4: {
                if (symbol_name == INTERGER_SYM) {
                    if (m_type == INT_SYM) {
                        m_int_value = handle_symbol_queue->GetCurrentValue<int>();
                    }
                    state = 5;
                    // Table
                } else if (symbol_name == CHARACTER_SYM) {
                    if (m_type == CHAR_SYM) {
                        m_char_value = handle_symbol_queue->GetCurrentValue<char>();
                    }
                    state = 5;
                    // Table
                }
                break;
            }
            case 5: {
                if (symbol_name == COMMA_SYM) {
                    state = 2;
                } else if (symbol_name == SEMICOLON_SYM) {
                    state = 6;
                } else {
                    
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
                if (name == INT_SYM || name == CHAR_SYM) {
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
                    m_identifier_name = name;
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
                    // Table
                    break;
                } else if (name == SEMICOLON_SYM) {
                    state = 3;
                    break;
                }
            }
            case 3: return COMPILE_OK;
            case 11: {
                if (name == INTERGER_SYM) {
                    state = 12;
                    m_array_length = handle_symbol_queue->GetCurrentValue<int>();
                    break;
                }
            }
            case 12: {
                if (name == R_SQUARE_BRACKET_SYM) {
                    state = 2;
                    break;
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
        if (name == INT_SYM || name == CHAR_SYM) {
            handle_symbol_queue->NextSymbol();
            name = handle_symbol_queue->GetCurrentName();
            if (name == IDENTIFIER_SYM) {
                handle_symbol_queue->NextSymbol();
                name = handle_symbol_queue->GetCurrentName();
                if (name == L_CIRCLE_BRACKET_SYM) {
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
    return COMPILE_OK;
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
                    state = 6;
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
    if ((ret = m_main_function.Parse()) == COMPILE_OK) {
        m_main_function.LogOutput();
    }
    return ret;
}
