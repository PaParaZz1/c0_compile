#ifndef C0_COMPILE_TOOLS_H_
#define C0_COMPILE_TOOLS_H_
#include <stdio.h>
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

class LogTools {
public:
    LogTools() {
        m_fp_gramma_log = fopen("gramma_log.txt", "w");
        m_fp_gramma_error = fopen("gramma_error.txt", "w");
        m_fp_semantic = fopen("semantic_error.txt", "w");
        m_fp_symbol = fopen("symbol_log.txt", "w");
        m_gramma_normal_switch = true;
        m_gramma_error_flag = true;
        m_semantic_flag = true;
    }
    ~LogTools() {
        fclose(m_fp_gramma_log);
        fclose(m_fp_gramma_error);
        fclose(m_fp_semantic);
        fclose(m_fp_symbol);
    }
    bool GetGrammaFlag() const {
        return m_gramma_error_flag;
    }
    bool GetSemanticFlag() const {
        return m_semantic_flag;
    }
    void GrammaNormalLogs(const string& log_content);
    friend void GrammaErrorLogs(LogTools* log_tools_ptr, const string& error_content);
    void SemanticErrorLogs(const string& error_type, const string& error_content, int line_number, int character_number);
    void SymbolTableLogs(const string& table_content);
private:
    FILE* m_fp_symbol;
    FILE* m_fp_gramma_log;
    FILE* m_fp_gramma_error;
    FILE* m_fp_semantic;
    FILE* m_fp_pcode;
    bool m_gramma_normal_switch;
    bool m_gramma_error_flag;
    bool m_semantic_flag;
};

class GrammaTools {

};

class SemanticTools {

};
extern LogTools* g_log_tools;
#endif // C0_COMPILE_TOOLS_H_
