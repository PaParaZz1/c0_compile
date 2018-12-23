#ifndef _C0_COMPILE_GRAMMA_ANALYSIS_H_
#define _C0_COMPILE_GRAMMA_ANALYSIS_H_
#include <iostream>
#include <string>
#include "c0_compile_symbol.hpp"

#define LOG_SWITCH 1
extern FILE* log_gramma;
#define GRAMMA_LOG(str) do { \
                            if (LOG_SWITCH) fprintf(log_gramma, "%s\n", str.c_str()); \
                        }while(0) 

typedef int compile_errcode;
using std::string;


/*class BaseAnalysisTool {
public:
    BaseAnalysisTool(const char* filename) {
        m_lexical_analysis = new LexicalAnalysis(filename);
    }
    ~BaseAnalysisTool() {
        ~m_lexical_analysis();
        delete(m_lexical_analysis);
    }
protected:
    compile_errcode GetSym(Symbol& symbol) {
        return m_lexical_analysis->GetSym(symbol);
    }
private:
    LexicalAnalysis* m_lexical_analysis;
};*/

class AnalysisInterface {
public:
    virtual compile_errcode Parse() = 0;
    virtual void LogOutput() = 0;
    virtual compile_errcode Action() = 0;
    virtual compile_errcode Generate() = 0;
};


class Factor;
class Term : AnalysisInterface {
public:
    compile_errcode Parse();
    void LogOutput() {
        string str("This is a term");
        GRAMMA_LOG(str);
    }
    compile_errcode Action() {
        fprintf(stderr, "This func has not implemented, please check the head file use another form\n");
        return FUNC_NOT_IMPLEMENTED;
    }
    compile_errcode Action(SymbolType& term_type);
    compile_errcode Generate() {
        fprintf(stderr, "This func has not implemented, please check the head file use another form\n");
        return FUNC_NOT_IMPLEMENTED;
    }
    compile_errcode Generate(string& term_string);
private:
    Factor* m_factor;
};

class Expression : AnalysisInterface {
public:
    compile_errcode Parse();
    void LogOutput() {
        string str("This is a expression");
        GRAMMA_LOG(str);
    }
    compile_errcode Action() {
        fprintf(stderr, "This func has not implemented, please check the head file use another form\n");
        return FUNC_NOT_IMPLEMENTED;
    }
    compile_errcode Action(SymbolType& expression_type);
    compile_errcode Generate() {
        fprintf(stderr, "This func has not implemented, please check the head file use another form\n");
        return FUNC_NOT_IMPLEMENTED;
    }
    compile_errcode Generate(string& expression_string);
private:
    Term m_term;
};

class ValueArgumentList : AnalysisInterface {
public:
    compile_errcode Parse();
    void LogOutput() {
        string str("This is a value argument list");
        GRAMMA_LOG(str);
    }
    compile_errcode Action() {
        fprintf(stderr, "This func has not implemented, please check the head file use another form\n");
        return FUNC_NOT_IMPLEMENTED;
    }
    compile_errcode Action(vector<SymbolType>& argument_type);
    compile_errcode Generate() {
        fprintf(stderr, "This func has not implemented, please check the head file use another form\n");
        return FUNC_NOT_IMPLEMENTED;
    }
    compile_errcode Generate(const string& call_name);
private:
    Expression m_expression;
};

class Factor : AnalysisInterface {
public:
    compile_errcode Parse();
    void LogOutput() {
        string str("This is a factor");
        GRAMMA_LOG(str);
    }
    compile_errcode Action() {
        fprintf(stderr, "This func has not implemented, please check the head file use another form\n");
        return FUNC_NOT_IMPLEMENTED;
    }
    compile_errcode Action(SymbolType& factor_type);
    compile_errcode Generate() {
        fprintf(stderr, "This func has not implemented, please check the head file use another form\n");
        return FUNC_NOT_IMPLEMENTED;
    }
    compile_errcode Generate(string& factor_string);
private:
    bool m_valid;
    string m_identifier_name;
    Expression m_expression;
    ValueArgumentList m_value_argument_list;
};

class ArgumentList : AnalysisInterface {
public:
    compile_errcode Parse();
    void LogOutput() {
        string str("This is a argument list");
        GRAMMA_LOG(str);
    }
    compile_errcode Action() {
        fprintf(stderr, "This func has not implemented, please check the head file use another form\n");
        return FUNC_NOT_IMPLEMENTED;
    }
    compile_errcode Action(vector<SymbolType>& argument_number);
    compile_errcode Generate() {
        fprintf(stderr, "This func has not implemented, please check the head file use another form\n");
        return FUNC_NOT_IMPLEMENTED;
    }
    compile_errcode Generate(int& argument_number);
private:
    string m_identifier_name;
    SymbolName m_type;
};

class Condition : AnalysisInterface {
public:
    compile_errcode Parse();
    void LogOutput() {
        string str("This is a condition");
        GRAMMA_LOG(str);
    }
    compile_errcode Action();
    compile_errcode Generate() {
        fprintf(stderr, "This func has not implemented, please check the head file use another form\n");
        return FUNC_NOT_IMPLEMENTED;
    }
    compile_errcode Generate(string& jump_label);
private:
    Expression m_expression;
};

class Statement;
class ConditionStatement : AnalysisInterface {
public:
    compile_errcode Parse();
    void LogOutput() {
        string str("This is a condition statement");
        GRAMMA_LOG(str);
    }
    compile_errcode Action();
    compile_errcode Generate();
private:
    Condition m_condition;
    Statement* m_statement_ptr;
    string m_bottom_label;
};

class WhileLoopStatement : AnalysisInterface {
public:
    compile_errcode Parse();
    void LogOutput() {
        string str("This is a while loop statement");
        GRAMMA_LOG(str);
    }
    compile_errcode Action();
    compile_errcode Generate();
private:
    Condition m_condition;
    Statement* m_statement_ptr;
    string m_top_label;
    string m_bottom_label;
};

class SwitchChildStatement : AnalysisInterface {
public:
    compile_errcode Parse();
    void LogOutput() {
        string str("This is a switch child statement");
        GRAMMA_LOG(str);
    }
    compile_errcode Action(const SymbolType& parent_type);
    compile_errcode Action() {
        fprintf(stderr, "This func has not implemented, please check the head file use another form\n");
        return FUNC_NOT_IMPLEMENTED;
    }
    compile_errcode Generate() {
        fprintf(stderr, "This func has not implemented, please check the head file use another form\n");
        return FUNC_NOT_IMPLEMENTED;
    }
    compile_errcode Generate(string compare_string, string jump_label, string& next_case_label);
private:
    Statement* m_statement_ptr;
};

class SwitchTable : AnalysisInterface {
public:
    compile_errcode Parse();
    void LogOutput() {
        string str("This is a switch table");
        GRAMMA_LOG(str);
    }
    compile_errcode Action(const SymbolType& parent_type);
    compile_errcode Action() {
        fprintf(stderr, "This func has not implemented, please check the head file use another form\n");
        return FUNC_NOT_IMPLEMENTED;
    }
    compile_errcode Generate() {
        fprintf(stderr, "This func has not implemented, please check the head file use another form\n");
        return FUNC_NOT_IMPLEMENTED;
    }
    compile_errcode Generate(string compare_string, string& jump_label);
private:
    SwitchChildStatement m_switch_child_statement;
};

class Default : AnalysisInterface {
public:
    compile_errcode Parse();
    void LogOutput() {
        string str("This is a default");
        GRAMMA_LOG(str);
    }
    compile_errcode Action();
    compile_errcode Generate();
private:
    Statement* m_statement_ptr;
};

class SwitchStatement : AnalysisInterface {
public:
    compile_errcode Parse();
    void LogOutput() {
        string str("This is a switch loop statement");
        GRAMMA_LOG(str);
    }
    compile_errcode Action();
    compile_errcode Generate();
private:
    Expression m_expression;
    SwitchTable m_switch_table;
    Default m_default;
    string m_bottom_label;
};

class FunctionCall : AnalysisInterface {
public:
    compile_errcode Parse();
    void LogOutput() {
        string str("This is a function call");
        GRAMMA_LOG(str);
    }
    compile_errcode Action();
    compile_errcode Generate();
private:
    ValueArgumentList m_value_argument_list;
};

class ConstantDefinition : AnalysisInterface {
public:
    compile_errcode Parse();
    void LogOutput() {
        string str("This is a constant definition");
        GRAMMA_LOG(str);
    }
    compile_errcode Action();
    compile_errcode Generate();
private:
    SymbolName m_type;
    string m_identifier_name;
    bool m_valid;
};

class ConstantDeclaration : AnalysisInterface{
public:
    compile_errcode Parse();
    void LogOutput() {
        string str("This is a constant declaration");
        GRAMMA_LOG(str);
    }
    compile_errcode Action();
    compile_errcode Generate();
private:
    ConstantDefinition m_constant_definition;
};

class VariableDefinition : AnalysisInterface{
public:
    compile_errcode Parse();
    void LogOutput() {
        string str("This is a variable definition");
        GRAMMA_LOG(str);
    }
    compile_errcode Action();
    compile_errcode Generate();
private:
    SymbolName m_type;
    string m_identifier_name;
    int m_array_length;
    bool m_valid;
};

class VariableDeclaration : AnalysisInterface{
public:
    compile_errcode Parse();
    void LogOutput() {
        string str("This is a variable declaration");
        GRAMMA_LOG(str);
    }
    compile_errcode Action();
    compile_errcode Generate();
private:
    VariableDefinition m_variable_definition;
};

class OutputStatement: AnalysisInterface {
public:
    compile_errcode Parse();
    void LogOutput() {
        string str("This is a output statement");
        GRAMMA_LOG(str);
    }
    compile_errcode Action();
    compile_errcode Generate();
private:
    Expression m_expression;
};

class InputStatement : AnalysisInterface {
public:
    compile_errcode Parse();
    void LogOutput() {
        string str("This is a input statement");
        GRAMMA_LOG(str);
    }
    compile_errcode Action();
    compile_errcode Generate();
};

class ReturnStatement : AnalysisInterface {
public:
    compile_errcode Parse();
    void LogOutput() {
        string str("This is a return statement");
        GRAMMA_LOG(str);
    }
    compile_errcode Action() {
        fprintf(stderr, "This func has not implemented, please check the head file use another form\n");
        return FUNC_NOT_IMPLEMENTED;
    }
    compile_errcode Action(SymbolType& function_type, string funtion_name);
    compile_errcode Generate();
private:
    Expression m_expression;
};

class AssignStatement : AnalysisInterface {
public:
    compile_errcode Parse();
    void LogOutput() {
        string str("This is a assign statement");
        GRAMMA_LOG(str);
    }
    compile_errcode Action();
    compile_errcode Generate();
private:
    Expression m_expression;
    string m_identifier_name;
};

class StatementList;
class Statement : AnalysisInterface {
public:
    compile_errcode Parse();
    void LogOutput() {
        string str("This is a statement");
        GRAMMA_LOG(str);
    }
    compile_errcode Action();
    compile_errcode Generate();
private:
    OutputStatement m_output_statement;
    InputStatement m_input_statement;
    ReturnStatement m_return_statement;
    AssignStatement m_assign_statement;
    FunctionCall m_function_call;
    ConditionStatement m_condition_statement;
    WhileLoopStatement m_while_loop_statement;
    SwitchStatement m_switch_statement;
    StatementList* m_statement_list_ptr;
};

class StatementList : AnalysisInterface {
public:
    compile_errcode Parse();
    void LogOutput() {
        string str("This is a statement list");
        GRAMMA_LOG(str);
    }
    compile_errcode Action();
    compile_errcode Generate();
private:
    Statement m_statement;
};

class CompoundStatement : AnalysisInterface {
public:
    compile_errcode Parse();
    void LogOutput() {
        string str("This is a compound statement");
        GRAMMA_LOG(str);
    }
    compile_errcode Action();
    compile_errcode Generate();
private:
    ConstantDeclaration m_constant_declaration;
    VariableDeclaration m_variable_declaration;
    StatementList m_statement_list;
};

class FunctionDefinition : AnalysisInterface {
public:
    compile_errcode Parse();
    void LogOutput() {
        string str("This is a funtion definition");
        GRAMMA_LOG(str);
    }
    compile_errcode Action();
    compile_errcode Generate();
private:
    ArgumentList m_argument_list;
    CompoundStatement m_compound_statement;
    bool m_valid;
    string m_identifier_name;
    SymbolName m_type;
    int m_argument_number;
};

class MainFunction : AnalysisInterface {
public:
    compile_errcode Parse();
    void LogOutput() {
        string str("This is a main function");
        GRAMMA_LOG(str);
    }
    compile_errcode Action();
    compile_errcode Generate();
private:
    CompoundStatement m_compound_statement;
};

class Program : AnalysisInterface{
public:
    compile_errcode Parse();
    void LogOutput() {
        string str("This is a c0 program");
        GRAMMA_LOG(str);
    }
    compile_errcode Action();
    compile_errcode Generate();
private:
    ConstantDeclaration m_constant_declaration;
    VariableDeclaration m_variable_declaration;
    FunctionDefinition m_function_definition;
    MainFunction m_main_function;
};


#endif // _C0_COMPILE_GRAMMA_ANALYSIS_H_
