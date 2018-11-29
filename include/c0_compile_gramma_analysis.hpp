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
};


class Factor;
class Term : AnalysisInterface {
public:
    compile_errcode Parse();
    void LogOutput() {
        string str("This is a term");
        GRAMMA_LOG(str);
    }
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
private:
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
};

class Condition : AnalysisInterface {
public:
    compile_errcode Parse();
    void LogOutput() {
        string str("This is a condition");
        GRAMMA_LOG(str);
    }
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
private:
    Condition m_condition;
    Statement* m_statement_ptr;
};

class WhileLoopStatement : AnalysisInterface {
public:
    compile_errcode Parse();
    void LogOutput() {
        string str("This is a while loop statement");
        GRAMMA_LOG(str);
    }
private:
    Condition m_condition;
    Statement* m_statement_ptr;
};

class SwitchChildStatement : AnalysisInterface {
public:
    compile_errcode Parse();
    void LogOutput() {
        string str("This is a switch child statement");
        GRAMMA_LOG(str);
    }
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
private:
    Expression m_expression;
    SwitchTable m_switch_table;
    Default m_default;
};

class FunctionCall : AnalysisInterface {
public:
    compile_errcode Parse();
    void LogOutput() {
        string str("This is a function call");
        GRAMMA_LOG(str);
    }
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
};

class ConstantDeclaration : AnalysisInterface{
public:
    compile_errcode Parse();
    void LogOutput() {
        string str("This is a constant declaration");
        GRAMMA_LOG(str);
    }
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
};

class VariableDeclaration : AnalysisInterface{
public:
    compile_errcode Parse();
    void LogOutput() {
        string str("This is a variable declaration");
        GRAMMA_LOG(str);
    }
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
};

class ReturnStatement : AnalysisInterface {
public:
    compile_errcode Parse();
    void LogOutput() {
        string str("This is a return statement");
        GRAMMA_LOG(str);
    }
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
private:
    Expression m_expression;
};

class StatementList;
class Statement : AnalysisInterface {
public:
    compile_errcode Parse();
    void LogOutput() {
        string str("This is a statement");
        GRAMMA_LOG(str);
    }
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
private:
    ArgumentList m_argument_list;
    CompoundStatement m_compound_statement;
};

class MainFunction : AnalysisInterface {
public:
    compile_errcode Parse();
    void LogOutput() {
        string str("This is a main function");
        GRAMMA_LOG(str);
    }
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
private:
    ConstantDeclaration m_constant_declaration;
    VariableDeclaration m_variable_declaration;
    FunctionDefinition m_function_definition;
    MainFunction m_main_function;
};


#endif // _C0_COMPILE_GRAMMA_ANALYSIS_H_
