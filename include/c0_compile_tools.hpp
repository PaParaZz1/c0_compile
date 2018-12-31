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
        m_fp_symbol = fopen("symbol_log", "w");
        m_fp_gramma = fopen("gramma_error", "w");
        m_fp_semantic = fopen("semantic_error", "w");
        m_gramma_flag = true;
        m_semantic_flag = true;
    }
    ~LogTools() {
        fclose(m_fp_symbol);
        fclose(m_fp_gramma);
        fclose(m_fp_semantic);
    }
    void GrammaErrorLogs(const string& error_content);
private:
    FILE* m_fp_symbol;
    FILE* m_fp_gramma;
    FILE* m_fp_semantic;
    bool m_gramma_flag;
    bool m_semantic_flag;
};

class GrammaTools {

};

class SemanticTools {

};
#endif // C0_COMPILE_TOOLS_H_
