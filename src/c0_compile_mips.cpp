#include "c0_compile_utils.hpp"
#include "c0_compile_pcode.hpp"
#include "c0_compile_mips.hpp"
#define IN_REG $s0
#define OUT_REG $s1
#define NUM1 string("$t0")
#define NUM2 string("$t1")
#define NUM3 string("$t2")
#define TMP string("t")
#define SP string("sp")
MipsGenerator* handle_mips_generator;

compile_errcode MipsGenerator::FindRelativeAddr(string temp_name, int& addr) {
    auto iter = m_temp2address.find(temp_name);
    if (iter != m_temp2address.end()) {
        addr = iter->second; 
        return COMPILE_OK;
    } else {
        return -3;
    }
}

void MipsGenerator::GenerateStore(string temp_name) {
    int store_offset = m_relative_addr;
    m_temp2address[temp_name] = store_offset;
    Output2File(string("sw ") + NUM1 + string(" ") + std::to_string(store_offset) + string("($fp)"));
    m_relative_addr += 4;
}

void MipsGenerator::GenerateLoad(string target, string source) {
    int load_offset;
    FindRelativeAddr(source, load_offset);
    Output2File(string("lw ") + target + string(" ") + std::to_string(load_offset) + string("($fp)"));
}

void MipsGenerator::ExtractString() {
    auto iter = m_pcode_queue.begin();
    for (; iter != m_pcode_queue.end(); ++iter) {
        if (iter->GetOP() == OUTPUT && iter->GetNum2() == STRING) {
            string content = iter->GetNum1();
            Output2File(content + string(": .asciiz \"") + content + string("\""));
        }
    }
}

void MipsGenerator::TranslateADD(Pcode& item) {
    string num1 = item.GetNum1();
    string num2 = item.GetNum2();
    string num3 = item.GetNum3();
    size_t f2 = num2.find(TMP);
    size_t f3 = num3.find(TMP);
    if (f2 == string::npos && f3 == string::npos) {
        fprintf(stderr, "not implemented translate ADD type\n");
    } else if (f2 != string::npos && f3 != string::npos) {
        GenerateLoad(NUM2, num2);
        GenerateLoad(NUM3, num3);
        Output2File(string("add ") + NUM1 + string(" ") + NUM2 + string(" ") + NUM3);
    } else if (f2 == string::npos) {
        GenerateLoad(NUM2, num3);
        Output2File(string("addi ") + NUM1 + string(" ") + NUM2 + string(" ") + num2);
    } else {
        GenerateLoad(NUM2, num2);
        Output2File(string("addi ") + NUM1 + string(" ") + NUM2 + string(" ") + num3);
    }
    GenerateStore(num1);
}

void MipsGenerator::TranslateSUB(Pcode& item) {
    string num1 = item.GetNum1();
    string num2 = item.GetNum2();
    string num3 = item.GetNum3();

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
                    Output2File(string("li $v0 4"));
                    Output2File(string("la $a0 ") + name);
                    Output2File(string("syscall"));
                } else if (output_type == INT_EXPRESSION) {
                    string output_content = iter->GetNum1();
                    //TODO
                    Output2File(string("li $v0 1"));
                    Output2File(string("move $a0 OUT_REG"));
                    Output2File(string("syscall"));
                } else if (output_type == CHAR_EXPRESSION) {
                    string output_content = iter->GetNum1();
                    //TODO
                    Output2File(string("li $v0 11"));
                    Output2File(string("move $a0 OUT_REG"));
                    Output2File(string("syscall"));
                } else {
                    fprintf(stderr, "undefined output behaviour\n");
                }
                break;
            }
            case ADD: {
                TranslateADD(*iter);
                break;
            }
            case SUB: {
                TranslateSUB(*iter);
            }
            default: {
                fprintf(stderr, "not implemented pcode2mips type\n");         
            }
        }
    }
}
