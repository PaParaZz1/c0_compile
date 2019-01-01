#include "c0_compile_tools.hpp"
#include <stdio.h>
#include <string>

using std::string;

LogTools* g_log_tools;
void LogTools::GrammaNormalLogs(const string& log_content) {
    if (m_gramma_normal_switch) {
        fprintf(m_fp_gramma_log, "%s\n", log_content.c_str());
    }
}

void LogTools::SemanticErrorLogs(const string& error_type, const string& error_content, int line_number, int character_number) {
    m_semantic_flag = false;
    if (m_fp_semantic == NULL) {
        fprintf(stderr, "%s error: '%s' in line %d character %d\n", error_type.c_str(), error_content.c_str(), line_number, character_number);
    } else {
        fprintf(m_fp_semantic, "%s error: '%s' in line %d character %d\n", error_type.c_str(),  error_content.c_str(), line_number, character_number);
    }
}
