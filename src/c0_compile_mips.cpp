#include "c0_compile_pcode.hpp"
#include "c0_compile_mips.hpp"
#define IN_REG $s0
#define OUT_REG $s1
MipsGenerator* handle_mips_generator;

void MipsGenerator::ExtractString() {
    auto iter = m_pcode_queue.begin();
    for (; iter != m_pcode_queue.end(); ++iter) {
        if (iter->GetOP() == OUTPUT && iter->GetNum2() == STRING) {
            string content = iter->GetNum1();
            Output2File(content + string(": .asciiz ") + content + string(")"));
        }
    }
}
void MipsGenerator::Translate() {
    this->ExtractString();
    auto iter = m_pcode_queue.begin();
    for (; iter != m_pcode_queue.end(); ++iter) {
        switch (iter->GetOP()) {
            case LABEL: Output2File(iter->GetNum1() + string(":")); break;
            case OUTPUT: {
                string output_type = iter->GetNum2();
                if (output_type == STRING) {
                    string name = iter->GetNum1();
                    Output2File(string("li $v0 11"));
                    Output2File(string("la $a0") + name);
                    Output2File(string("syscall"));
                } else if (output_type == INT_EXPRESSION) {
                    Output2File(string("li $v0"));
                    //Output2File(string("mv");
                    //TODO
                } else if (output_type == CHAR_EXPRESSION) {
                    //TODO
                } else {
                    fprintf(stderr, "undefined output behaviour\n");
                }
                break;
            }
        }
    }
}
