#include <iostream>
#include "c0_compile_utils.hpp"
#include "c0_compile_symbol.hpp"
#include "c0_compile_pcode.hpp"
#include "c0_compile_mips.hpp"

#define IN_REG string("$s0")
#define OUT_REG string("$s1")
#define RA_REG string("$ra")
#define V0_REG string("$v0")
#define NUM1 string("$t0")
#define NUM2 string("$t1")
#define NUM3 string("$t2")
#define TMP "t"
#define GLOBAL "g"
#define FP "fp"
#define SP "sp"

using std::cout;
using std::endl;
extern FunctionTable* handle_func_table;
extern SymbolTableTree* symbol_table_tree;
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

void MipsGenerator::GenerateStore(string temp_name, string type) {
    if (type == TMP) {
        int store_offset = m_relative_addr;
        m_temp2address[temp_name] = store_offset;
        Output2File(string("sw ") + NUM1 + " -" + std::to_string(store_offset) + string("($sp)"));
        m_relative_addr += 4;
    } else if (type == GLOBAL) {
        Output2File(string("sw ") + NUM1 + " " + temp_name + string("($t9)"));
    } else {
        Output2File(string("sw ") + NUM1 + " -" + temp_name + string("($fp)"));
    }
}

void MipsGenerator::GenerateStore(const string& source, const string& offset, const string& base, const string& type) {
    if (type == TMP) {
        int store_offset = m_relative_addr;
        m_temp2address[offset] = store_offset;
        m_relative_addr += 4;
        Output2File("sw " + source + " -" + std::to_string(store_offset) + "($sp)");
    } else {
        Output2File("sw " + source + " " + offset + "(" + base + ")");
    }
}

void MipsGenerator::GenerateLoad(string target, string source, string type) {
    if (type == TMP) {
        int load_offset;
        FindRelativeAddr(source, load_offset);
        Output2File("lw " + target + " -" + std::to_string(load_offset) + "($sp)");
    } else if (type == GLOBAL) {
        Output2File("lw " + target + " " + source + "($t9)");
    } else {
        Output2File("lw " + target + " -" + source + "($fp)");
    }
}

void MipsGenerator::GetNextStringLabel(string& string_label) {
    m_string_label_count++;
    string_label = "str" + std::to_string(m_string_label_count);
}

void MipsGenerator::ExtractString() {
    Output2File(".data");
    auto iter = m_pcode_queue.begin();
    int string_count = 0;
    for (; iter != m_pcode_queue.end(); ++iter) {
        if (iter->GetOP() == OUTPUT && iter->GetNum2() == STRING) {
            string content = iter->GetNum1();
            auto string_iter = m_string_map.find(content);
            if (string_iter == m_string_map.end()){
                string string_label;
                this->GetNextStringLabel(string_label);
                m_string_map[content] = string_label;
                Output2File(string_label + string(": .asciiz \"") + content + string("\""));
                string_count += content.size() + 1;
            }
        }
    }
    m_global += (string_count/4*4)+4;
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
        GenerateLoad(NUM2, num2, TMP);
        GenerateLoad(NUM3, num3, TMP);
        Output2File("addu " + NUM1 + " " + NUM2 + " " + NUM3);
    } else if (f2 == string::npos) {
        GenerateLoad(NUM2, num3, TMP);
        Output2File("addiu " + NUM1 + " " + NUM2 + " " + num2);
    } else {
        GenerateLoad(NUM2, num2, TMP);
        Output2File("addiu " + NUM1 + " " + NUM2 + " " + num3);
    }
    GenerateStore(num1, TMP);
}

void MipsGenerator::TranslateSUB(const Pcode& item) {
    string num1 = item.GetNum1();
    string num2 = item.GetNum2();
    string num3 = item.GetNum3();
    size_t f2 = num2.find(TMP);
    size_t f3 = num3.find(TMP);
    if (f2 == string::npos && f3 == string::npos) {
        fprintf(stderr, "not implemented translate SUB\n");
    } else if (f2 != string::npos && f3 != string::npos) {
        GenerateLoad(NUM2, num2, TMP);
        GenerateLoad(NUM3, num3, TMP);
        Output2File("subu " + NUM1 + " " + NUM2 + " " + NUM3);
    } else if (f2 == string::npos) {
        Output2File("li " + NUM2 + " " + num2);
        GenerateLoad(NUM3, num3, TMP);
        Output2File("subu " + NUM1 + " " + NUM2 + " " + NUM3);
    } else {
        Output2File("li " + NUM3 + " " + num3);
        GenerateLoad(NUM2, num2, TMP);
        Output2File("subu " + NUM1 + " " + NUM2 + " " + NUM3);
    }
    GenerateStore(num1, TMP);
}

void MipsGenerator::TranslateMULType(Pcode& item) {
    string num1 = item.GetNum1();
    string num2 = item.GetNum2();
    string num3 = item.GetNum3();
    PcodeType op_type = item.GetOP();
    string op;
    if (op_type == MUL)
        op = string("mul ");
    else if (op_type == DIV)
        op = string("div ");
    else
        fprintf(stderr, "invalid mul type\n");
    size_t t2 = num2.find(TMP);
    size_t t3 = num3.find(TMP);
    size_t g2 = num2.find(GLOBAL);
    size_t g3 = num3.find(GLOBAL);
    size_t f2 = num2.find(FP);
    size_t f3 = num3.find(FP);
    if (t2 != string::npos) {
        GenerateLoad(NUM2, num2, TMP);
    } else if (g2 != string::npos) {
        string relative_addr = num2.substr(g2 + 1);
        int num_addr = atoi(relative_addr.c_str());
        //num_addr += m_global;
        GenerateLoad(NUM2, std::to_string(num_addr), GLOBAL); 
    } else if (f2 != string::npos) {
        string relative_addr = num2.substr(f2 + 2);
        GenerateLoad(NUM2, relative_addr, FP);
    } else {
        Output2File(string("li ") + NUM2 + " " + num2);
    }
    if (t3 != string::npos) {
        GenerateLoad(NUM3, num3, TMP);
    } else if (g3 != string::npos) {
        string relative_addr = num3.substr(g3 + 1);
        int num_addr = atoi(relative_addr.c_str());
        //num_addr += m_global;
        GenerateLoad(NUM3, std::to_string(num_addr), GLOBAL); 
    } else if (f3 != string::npos) {
        string relative_addr = num3.substr(f3 + 2);
        GenerateLoad(NUM3, relative_addr, FP);
    } else {
        Output2File(string("li ") + NUM3 + " " + num3);
    }
    Output2File(op + NUM1 + " " + NUM2 + " " + NUM3);
    GenerateStore(num1, TMP);
}

void MipsGenerator::TranslateInput(Pcode& item) {
    string num1 = item.GetNum1();
    string num2 = item.GetNum2();
    if (num2 == string("int")) {
        Output2File(string("li $v0 5"));
        Output2File("syscall");
    } else if (num2 == string("char")) {
        Output2File(string("li $v0 12"));
        Output2File("syscall");
    } else {
        fprintf(stderr, "invalid input type\n");
    }

    Output2File("move " + NUM1 + " $v0");
    GenerateStore(num1, TMP);
}

void MipsGenerator::TranslateOutput(Pcode& item) {
    string output_type = item.GetNum2();
    if (output_type == STRING) {
        string name = item.GetNum1();
        string string_label;
        auto iter = m_string_map.find(name);
        if (iter != m_string_map.end()) {
            string_label = iter->second;
        } else {
            fprintf(stderr, "undefined string label\n");
        }
        Output2File(string("li $v0 4"));
        Output2File(string("la $a0 ") + string_label);
        Output2File(string("syscall"));
    } else if (output_type == INT_EXPRESSION) {
        string temp_name = item.GetNum1();
        GenerateLoad(OUT_REG, temp_name, TMP);
        Output2File(string("li $v0 1"));
        Output2File(string("move $a0 ") + OUT_REG);
        Output2File(string("syscall"));
    } else if (output_type == CHAR_EXPRESSION) {
        string temp_name = item.GetNum1();
        GenerateLoad(OUT_REG, temp_name, TMP);
        Output2File(string("li $v0 11"));
        Output2File(string("move $a0 ") + OUT_REG);
        Output2File(string("syscall"));
    } else {
        fprintf(stderr, "undefined output behaviour\n");
    }
}


void MipsGenerator::TranslatePara(Pcode& item) {
    m_parameter_stack.push_back(item);
}
void MipsGenerator::TranslateCall(Pcode& item) {
    string top_level = item.GetNum1();
    string space_length = item.GetNum2();
    string func_name = item.GetNum3();
    Output2File(string("sw $ra -") + std::to_string(m_relative_addr) + "($sp)");
    Output2File(string("sw $fp -") + std::to_string(m_relative_addr + 4) + "($sp)");
    Output2File(string("addi $fp $sp -") + std::to_string(m_relative_addr + 8));
    for (Pcode para : m_parameter_stack) {
        if (para.GetNum3() == func_name){
            Output2File("# para");
            TranslateASSIGN(para);
        }
    }
    Output2File("addiu $sp $fp -" + space_length);
    Output2File("jal " + top_level);
    Output2File("addiu $sp $fp " + std::to_string(m_relative_addr + 8));
    Output2File("lw $fp -" + std::to_string(m_relative_addr + 4) + "($sp)");
    Output2File("lw $ra -" + std::to_string(m_relative_addr) + "($sp)");
    for (auto iter = m_parameter_stack.begin(); iter != m_parameter_stack.end();) {
        if (iter->GetNum3() == func_name) {
            iter = m_parameter_stack.erase(iter);
        } else {
            ++iter;
        }
    }
}

void MipsGenerator::TranslateASSIGN(Pcode& item) {
    string num1 = item.GetNum1();
    string num2 = item.GetNum2();
    string source;
    if (num2 == string("V0")) {
        source = string("$v0");
    } else {
        GenerateLoad(NUM2, num2, TMP);
        source = NUM2;
    }
    if (num1 == string("V0")) {
        Output2File(string("move ") + V0_REG + " " + source);
    } else if (num1.find(FP) != string::npos) {
        Output2File(string("move ") + NUM1 + " " + source);
        GenerateStore(num1.substr(num1.find(FP) + 2), FP);
    } else if (num1.find(GLOBAL) != string::npos) {
        Output2File(string("move ") + NUM1 + " " + source);
        string relative_addr = num1.substr(num1.find(GLOBAL) + 1);
        int num_addr = atoi(relative_addr.c_str());
        //num_addr += m_global;
        GenerateStore(std::to_string(num_addr), GLOBAL);
    } else {
        Output2File(string("move ") + NUM1 + " " + source);
        GenerateStore(num1, TMP);
    }
}

void MipsGenerator::TranslateLoadAddr(Pcode& item) {
    string source = item.GetNum1();
    string array_addr = item.GetNum2();
    string offset = item.GetNum3();
    size_t fp = array_addr.find(FP);
    size_t g = array_addr.find(GLOBAL);
    if (fp != string::npos) {
        GenerateLoad(NUM1, offset, TMP);
        Output2File("sll " + NUM3 + " " + NUM1 + " 2");
        Output2File("addiu " + NUM3 + " " + NUM3 + " " + array_addr.substr(fp + 2));
        Output2File("subu " + NUM2 + " $fp " + NUM3);
        GenerateLoad(NUM1, source, TMP);
        GenerateStore(NUM1, "0", NUM2, "0");
    } else if (g != string::npos) {
        int base = atoi(array_addr.substr(g + 1).c_str());
        base += m_global;
        GenerateLoad(NUM1, offset, TMP);
        Output2File("sll " + NUM3 + " " + NUM1 + " 2");
        Output2File("addiu " + NUM3 + " " + NUM3 + " " + std::to_string(base));
        Output2File("addu " + NUM2 + " $0 " + NUM3);
        GenerateLoad(NUM1, source, TMP);
        GenerateStore(NUM1, "0", NUM2, "0");
    } else {
        fprintf(stderr, "not support this type array_address---%s\n", array_addr.c_str());
    }
}

void MipsGenerator::TranslateLoadValue(Pcode& item) {
    string target = item.GetNum1();
    string array_addr = item.GetNum2();
    string offset = item.GetNum3();
    size_t fp = array_addr.find(FP);
    size_t g = array_addr.find(GLOBAL);
    if (fp != string::npos) {
        GenerateLoad(NUM1, offset, TMP);
        Output2File("sll " + NUM3 + " " + NUM1 + " 2");
        Output2File("addiu " + NUM3 + " " + NUM3 + " " + array_addr.substr(fp + 2));
        Output2File("subu " + NUM1 + " $fp " + NUM3);
        Output2File("lw " + NUM1 + " 0(" + NUM1 + ")");  // TODO
        GenerateStore(target, TMP);
    } else if (g != string::npos) {
        int base = atoi(array_addr.substr(g + 1).c_str());
        base += m_global;
        GenerateLoad(NUM1, offset, TMP);
        Output2File("sll " + NUM3 + " " + NUM1 + " 2");
        Output2File("addiu " + NUM1 + " " + NUM3 + " " + std::to_string(base));
        Output2File("lw " + NUM1 + " 0(" + NUM1 + ")");  // TODO
        GenerateStore(target, TMP);
    } else {
        fprintf(stderr, "not support this type address---%s\n", array_addr.c_str());
    }
    
}

void MipsGenerator::TranslateJUMP(Pcode& item) {
    string num1 = item.GetNum1();
    if (num1 == string("RA")) {
        //TODO
        Output2File(string("jr $ra"));
    } else {
        Output2File(string("j ") + num1);
    }
}

void MipsGenerator::TranslateBType(Pcode& item) {
    string num1 = item.GetNum1();
    string num2 = item.GetNum2();
    string num3 = item.GetNum3();
    PcodeType op = item.GetOP();
    size_t t1 = num1.find(TMP);
    size_t t2 = num2.find(TMP);
    if (t1 != string::npos) {
        GenerateLoad(NUM1, num1, TMP);
    } else {
        Output2File("li " + NUM1 + " " + num1);
    }
    if (t2 != string::npos) {
        GenerateLoad(NUM2, num2, TMP);
    } else {
        Output2File("li " + NUM2 + " " + num2);
    }
    switch (op) {
        case BNE: Output2File(string("bne ") + NUM1 + " " + NUM2 + " " + num3); break;
        case BEQ: Output2File(string("beq ") + NUM1 + " " + NUM2 + " " + num3); break;
        case BLE: Output2File(string("ble ") + NUM1 + " " + NUM2 + " " + num3); break;
        case BLT: Output2File(string("blt ") + NUM1 + " " + NUM2 + " " + num3); break;
        case BGE: Output2File(string("bge ") + NUM1 + " " + NUM2 + " " + num3); break;
        case BGT: Output2File(string("bgt ") + NUM1 + " " + NUM2 + " " + num3); break;
        default: {
            fprintf(stderr, "invalid b type\n");         
        }
    }
}

void MipsGenerator::Translate() {
    this->ExtractString();
    auto iter = m_pcode_queue.begin();
    int main_space_length;
    string main_bottom_label;
    handle_func_table->GetTermBottomLabel("main", main_bottom_label);
    handle_func_table->GetTermSpaceLength("main", main_space_length); 
    Output2File(".text");
    Output2File("li $t9 " + std::to_string(m_global));
    Output2File("move $fp $sp");
    Output2File("addiu $sp $fp -" + std::to_string(main_space_length)); 
    Output2File("la $ra " + main_bottom_label);
    Output2File("j main");
    for (; iter != m_pcode_queue.end(); ++iter) {
        switch (iter->GetOP()) {
            case LABEL: Output2File(iter->GetNum1() + string(":")); break;
            case OUTPUT: {
                TranslateOutput(*iter);
                break;
            }
            case INPUT: {
                TranslateInput(*iter);
                break;
            }
            case SUB: {
                TranslateSUB(*iter);
                break;
            }
            case ADD: {
                TranslateADD(*iter);
                break;
            }
            case DIV:
            case MUL: {
                TranslateMULType(*iter);
                break;
            }
            case ASSIGN: {
                TranslateASSIGN(*iter);
                break;
            }
            case BEQ:
            case BLT:
            case BLE:
            case BGT:
            case BGE:
            case BNE: {
                TranslateBType(*iter);          
                break;
            }
            case PARA: {
                TranslatePara(*iter);
                break;
            }
            case CALL: {
                TranslateCall(*iter);
                break;
            }
            case FUNC_BOTTOM: {
                m_relative_addr = 0;                  
                Output2File("jr $ra");
                break;
            }
            case JUMP: {
                TranslateJUMP(*iter);
                break;
            }
            case ARRAY_ASSIGN: {
                TranslateLoadAddr(*iter);
                break;
            }
            case LOAD_VALUE: {
                TranslateLoadValue(*iter);                 
                break;
            }
            default: {
                std::cerr << "unknown pcode: " << iter->GetOP() << std::endl;
                fprintf(stderr, "not implemented pcode2mips type\n");         
            }
        }
    }
}
