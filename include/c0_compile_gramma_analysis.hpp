#ifndef _C0_COMPILE_GRAMMA_ANALYSIS_H_
#define _C0_COMPILE_GRAMMA_ANALYSIS_H_
#include <iostream>
#include <string>
#include "c0_compile_symbol.hpp"

#define LOG_SWITCH 1
extern FILE* log_fp;
#define LOG_OUTPUT(str) do { \
                            if (LOG_SWITCH) fprintf(log_fp, "%s\n", str.c_str()); \
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

class Identifier : AnalysisInterface {
public:
    Identifier() {
        m_is_definition = true;
    }
    compile_errcode Parse();
    void LogOutput() {
        string str("This is a identifier");
        LOG_OUTPUT(str);
    }
private:
    bool m_is_definition;
};

class Factor;
class Term : AnalysisInterface {
public:
    compile_errcode Parse();
    void LogOutput() {
        string str("This is a term");
        LOG_OUTPUT(str);
    }
private:
    Factor* m_factor;
};

class Expression : AnalysisInterface {
public:
    Expression() {
        m_first_term_factor = 1;
        m_first_term_flag = true;
    }
    compile_errcode Parse();
    void LogOutput() {
        string str("This is a expression");
        LOG_OUTPUT(str);
    }
private:
    int m_first_term_factor;
    bool m_first_term_flag;
    Term m_term;
};

class Factor : AnalysisInterface {
public:
    compile_errcode Parse();
    void LogOutput() {
        string str("This is a factor");
        LOG_OUTPUT(str);
    }
private:
    Expression m_expression;
};

class ArgumentList : AnalysisInterface {
public:
    compile_errcode Parse();
    void LogOutput() {
        string str("This is a argument list");
        LOG_OUTPUT(str);
    }
};

class FunctionCall : AnalysisInterface {
public:
    compile_errcode Parse();
    void LogOutput() {
        string str("THis is a function call");
        LOG_OUTPUT(str);
    }
};

class ValueArgumentList : AnalysisInterface {
public:
    compile_errcode Parse();
    void LogOutput() {
        string str("This is a value argument list");
        LOG_OUTPUT(str);
    }
};

class ConstantDefinition : AnalysisInterface {
public:
    compile_errcode Parse();
    void LogOutput() {
        string str("This is a constant definition");
        LOG_OUTPUT(str);
    }
private:
    Identifier m_identifier;
    int m_int_value;
    char m_char_value;
    SymbolName m_type;
    string m_identifier_name;
};

class ConstantDeclaration : AnalysisInterface{
public:
    compile_errcode Parse();
    void LogOutput() {
        string str("This is a constant declaration");
        LOG_OUTPUT(str);
    }
private:
    ConstantDefinition m_constant_definition;
};

class VariableDefinition : AnalysisInterface{
public:
    compile_errcode Parse();
    void LogOutput() {
        string str("This is a variable definition");
        LOG_OUTPUT(str);
    }
private:
    SymbolName m_type;
    string m_identifier_name;
    int m_array_length;
    Identifier m_identifier;
};

class VariableDeclaration : AnalysisInterface{
public:
    compile_errcode Parse();
    void LogOutput() {
        string str("This is a variable declaration");
        LOG_OUTPUT(str);
    }
private:
    VariableDefinition m_variable_definition;
};

class FunctionDefinition : AnalysisInterface {
public:
    compile_errcode Parse();
    void LogOutput() {
        string str("This is a funtion definition with return");
    }
};

class FunctionDefinitionNoReturn : AnalysisInterface {
public:
    compile_errcode Parse();
    void LogOutput() {
        string str("This is a fucntion definition without return");
    }
};

class CompoundStatement : AnalysisInterface {
public:
    compile_errcode Parse();
    void LogOutput() {
        string str("This is a compound statement");
        LOG_OUTPUT(str);
    }
private:
    ConstantDeclaration m_constant_declaration;
    VariableDeclaration m_variable_declaration;
};

class MainFunction : AnalysisInterface {
public:
    compile_errcode Parse();
    void LogOutput() {
        string str("This is a main function");
        LOG_OUTPUT(str);
    }
private:
    CompoundStatement m_compound_statement;
};

class Program : AnalysisInterface{
public:
    compile_errcode Parse();
    void LogOutput() {
        string str("This is a c0 program");
        LOG_OUTPUT(str);
    }
private:
    ConstantDeclaration m_constant_declaration;
    VariableDeclaration m_variable_declaration;
    MainFunction m_main_function;
};


#endif // _C0_COMPILE_GRAMMA_ANALYSIS_H_
