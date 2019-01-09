#include <stdlib.h>
#include <iostream>
#include "c0_compile_utils.hpp"
#include "c0_compile_symbol.hpp"
#include "c0_compile_pcode.hpp"
#include "c0_compile_mips.hpp"

#define IN_REG string("$s0")
#define OUT_REG string("$s1")
#define RA_REG string("$ra")
#define V0_REG string("$v0")
#define NUM1 string("$25")
#define NUM2 string("$26")
#define NUM3 string("$27")
#define TMP "t"
#define GLOBAL "g"
#define FP "fp"
#define SP "sp"

using std::cout;
using std::endl;
extern FunctionTable* handle_func_table;
extern SymbolTableTree* symbol_table_tree;
MipsGenerator* handle_mips_generator;
const int global_register_number = 18;


string reg1;
string reg2;
string reg3;
bool GlobalJudgeMips(const string& str) {
    std::regex re("g\\d+");
    return std::regex_match(str, re);
}

bool FPJudgeMips(const string& str) {
    std::regex re("fp\\d+");
    return std::regex_match(str, re);
}

bool TMPJudge(const string& str) {
    std::regex re("t\\d+");
    return std::regex_match(str, re);
}

bool REGJudge(const string& str) {
    std::regex re1("\\$\\d+");
    std::regex re2("\\$a0");
    return std::regex_match(str, re1) || std::regex_match(str, re2);
}

int MipsGenerator::PrepareLoadREG(const string& num, string& reg, const string& empty_reg) {
    if (REGJudge(num)) {
        reg = num;
        return 0;
    } else if (FPJudgeMips(num)) {
        reg = empty_reg;
        string relative_addr = num.substr(2);
        GenerateLoad(empty_reg, relative_addr, FP);
        return 1;
    } else if (GlobalJudgeMips(num)) {
        reg = empty_reg;
        string relative_addr = num.substr(1);
        GenerateLoad(empty_reg, relative_addr, GLOBAL);
        return 1;
    } else if (TMPJudge(num)) {
        reg = empty_reg;
        GenerateLoad(empty_reg, num, TMP);
        return 1;
    } else {
        return -1;
    }
}

int MipsGenerator::PrepareStoreREG(const string& num, string& reg, const string& empty_reg) {
    if (REGJudge(num)) {
        reg = num;
        return 0;
    } else if (FPJudgeMips(num) || GlobalJudgeMips(num) || TMPJudge(num)){
        reg = empty_reg; 
        return 1;
    } else {
        fprintf(stderr, "invalid reg num:%s\n", num.c_str());
        return -2;
    }
}

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
        Output2File(string("sw ") + NUM1 + " " + temp_name + string("($28)"));
    } else {
        Output2File(string("sw ") + NUM1 + " -" + temp_name + string("($fp)"));
    }
}

void MipsGenerator::GenerateStore(const string& source, const string& offset, const string& base, const string& type) {
    if (type == TMP) {
        if (!TMPJudge(offset)) {
            fprintf(stderr, "invalid tmp offset:%s\n", offset.c_str());
        }
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
        Output2File("lw " + target + " " + source + "($28)");
    } else {
        Output2File("lw " + target + " -" + source + "($fp)");
    }
}

void AdvancedMipsGenerator::Transform2REG(const string& in, string& out) {
    if (REGJudge(in)) {
        out = in;
    } else if (in == V0_REG) {
        out = "$v0";
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
    int ret1 = PrepareStoreREG(num1, reg1, NUM1);
    int ret2 = PrepareLoadREG(num2, reg2, NUM2);
    int ret3 = PrepareLoadREG(num3, reg3, NUM3);
    if (ret2 == -1 && ret3 == -1) {
        int value = atoi(num2.c_str()) + atoi(num3.c_str());
        Output2File("li " + reg1 + " " + std::to_string(value));
    } else if (ret2 == -1) {
        Output2File("addiu " + reg1 + " " + reg3 + " " + num2);
    } else if (ret3 == -1) {
        Output2File("addiu " + reg1 + " " + reg2 + " " + num3);
    } else {
        Output2File("addu " + reg1 + " " + reg2 + " " + reg3);
    }
    if (ret1 == 1) {
        GenerateStore(reg1, num1, "", TMP);
    }
}

void MipsGenerator::TranslateSUB(const Pcode& item) {
    string num1 = item.GetNum1();
    string num2 = item.GetNum2();
    string num3 = item.GetNum3();
    int ret1 = PrepareStoreREG(num1, reg1, NUM1);
    int ret2 = PrepareLoadREG(num2, reg2, NUM2);
    int ret3 = PrepareLoadREG(num3, reg3, NUM3);
    if (ret2 == -1 && ret3 == -1) {
        int value = atoi(num2.c_str()) - atoi(num3.c_str());
        Output2File("li " + reg1 + " " + std::to_string(value));
    } else if (ret2 == -1) {
        int value = -1 * atoi(num2.c_str());
        Output2File("addiu " + reg1 + " " + reg3 + " " + std::to_string(value));
    } else if (ret3 == -1) {
        int value = -1 * atoi(num3.c_str());
        Output2File("addiu " + reg1 + " " + reg2 + " " + std::to_string(value));
    } else {
        Output2File("subu " + reg1 + " " + reg2 + " " + reg3);
    }
    if (ret1 == 1) {
        GenerateStore(reg1, num1, "", TMP);
    }
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
    int ret1 = PrepareStoreREG(num1, reg1, NUM1);
    int ret2 = PrepareLoadREG(num2, reg2, NUM2);
    int ret3 = PrepareLoadREG(num3, reg3, NUM3);
    if (ret2 == -1 && ret3 == -1) {
        int value;
        if (op_type == MUL)
            value = atoi(num2.c_str()) * atoi(num3.c_str());
        else
            value = atoi(num2.c_str()) / atoi(num3.c_str());
        Output2File("li " + reg1 + " " + std::to_string(value));
    } else if (ret2 == -1) {
        reg2 = NUM2;
        Output2File("li " + reg2 + " " + num2);
        Output2File(op + reg1 + " " + reg2 + " " + reg3);
    } else if (ret3 == -1) {
        reg3 = NUM3;
        Output2File("li " + reg3 + " " + num3);
        Output2File(op + reg1 + " " + reg2 + " " + reg3);
    } else {
        Output2File(op + reg1 + " " + reg2 + " " + reg3);
    }
    if (ret1 == 1) {
        GenerateStore(reg1, num1, "", TMP);
    }
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
    Pcode pcode(ASSIGN, num1, "$2", "");
    TranslateASSIGN(pcode);
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
        Output2File(string("li $v0 1"));
        Pcode pcode(ASSIGN, "$a0", temp_name, "");
        TranslateASSIGN(pcode);
        Output2File(string("syscall"));
    } else if (output_type == CHAR_EXPRESSION) {
        string temp_name = item.GetNum1();
        Output2File(string("li $v0 11"));
        Pcode pcode(ASSIGN, "$a0", temp_name, "");
        TranslateASSIGN(pcode);
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
    int ret1 = PrepareStoreREG(num1, reg1, NUM1);
    int ret2 = PrepareLoadREG(num2, reg2, NUM2);
    if (ret2 == -1) {
        Output2File("li " + reg1 + " " + num2);
    } else {
        Output2File("move " + reg1 + " " + reg2);
    }
    if (ret1 == 1) {
        if (FPJudgeMips(num1)) {
            GenerateStore(reg1, num1.substr(2), "$fp", FP);
        } else if (GlobalJudgeMips(num1)) {
            GenerateStore(reg1, num1.substr(1), "$28", GLOBAL);
        } else {
            GenerateStore(reg1, num1, "", TMP);
        }
    }
}

void MipsGenerator::TranslateLoadAddr(Pcode& item) {
    string source = item.GetNum1();
    string array_addr = item.GetNum2();
    string offset = item.GetNum3();
    int ret1 = PrepareLoadREG(source, reg1, NUM1);
    if (ret1 == -1) {
        reg1 = NUM1;
        Output2File("li " + reg1 + " " + source);
    }
    int ret3 = PrepareLoadREG(offset, reg3, NUM3);
    if (FPJudgeMips(array_addr)) {
        Output2File("sll " + NUM3 + " " + reg3 + " 2  # addr");
        Output2File("addiu " + NUM3 + " " + NUM3 + " " + array_addr.substr(2));
        Output2File("subu " + NUM2 + " $fp " + NUM3);
        GenerateStore(reg1, "0", NUM2, "0");
    } else if (GlobalJudgeMips(array_addr)) {
        int base = atoi(array_addr.substr(1).c_str());
        base += m_global;
        Output2File("sll " + NUM3 + " " + reg3 + " 2");
        Output2File("addiu " + NUM2 + " " + NUM3 + " " + std::to_string(base));
        //Output2File("addu " + NUM2 + " $0 " + NUM3);
        GenerateStore(reg1, "0", NUM2, "0");
    } else if (REGJudge(array_addr)) {
        Output2File("sll " + NUM3 + " " + reg3 + " 2  # addr reg");
        Output2File("addu " + NUM2 + " " + NUM3 + " " + array_addr);
        GenerateStore(reg1, "0", NUM2, "0");
    } else {
        fprintf(stderr, "not support this type array_address---%s\n", array_addr.c_str());
    }
}

void MipsGenerator::TranslateLoadValue(Pcode& item) {
    string target = item.GetNum1();
    string array_addr = item.GetNum2();
    string offset = item.GetNum3();
    int ret1 = PrepareLoadREG(target, reg1, NUM1);
    int ret3 = PrepareLoadREG(offset, reg3, NUM3);
    if (FPJudgeMips(array_addr)) {
        Output2File("sll " + NUM3 + " " + reg3 + " 2  # addr");
        Output2File("addiu " + NUM3 + " " + NUM3 + " " + array_addr.substr(2));
        Output2File("subu " + NUM2 + " $fp " + NUM3);
        Output2File("lw " + reg1 + " 0(" + NUM2 + ")");  // TODO
    } else if (GlobalJudgeMips(array_addr)) {
        int base = atoi(array_addr.substr(1).c_str());
        base += m_global;
        Output2File("sll " + NUM3 + " " + reg3 + " 2");
        Output2File("addiu " + NUM2 + " " + NUM3 + " " + std::to_string(base));
        Output2File("lw " + reg1 + " 0(" + NUM2 + ")");  // TODO
    } else if (REGJudge(array_addr)) {
        Output2File("sll " + NUM3 + " " + reg3 + " 2");
        Output2File("addu " + NUM2 + " " + NUM3 + " " + array_addr);
        Output2File("lw " + reg1 + " 0(" + NUM2 + ")");  // TODO
    } else {
        fprintf(stderr, "not support this type array_address---%s\n", array_addr.c_str());
    }
    if (ret1 == 1) {
        GenerateStore(reg1, target, "", TMP);
    }
}

void MipsGenerator::TranslateJUMP(Pcode& item) {
    string num1 = item.GetNum1();
    if (num1 == "RA") {
        Output2File("jr $ra");
    } else {
        Output2File("j " + num1);
    }
}

void MipsGenerator::TranslateBType(Pcode& item) {
    string num1 = item.GetNum1();
    string num2 = item.GetNum2();
    string num3 = item.GetNum3();
    PcodeType op = item.GetOP();
    int ret1 = PrepareLoadREG(num1, reg1, NUM1);
    int ret2 = PrepareLoadREG(num2, reg2, NUM2);
    if (ret1 == -1) {
        reg1 = NUM1;
        Output2File("li " + reg1 + " " + num1);
    }
    if (ret2 == -1) {
        reg2 = NUM2;
        Output2File("li " + reg2 + " " + num2);
    }
    switch (op) {
        case BNE: Output2File("bne " + reg1 + " " + reg2 + " " + num3); break;
        case BEQ: Output2File("beq " + reg1 + " " + reg2 + " " + num3); break;
        case BLE: Output2File("ble " + reg1 + " " + reg2 + " " + num3); break;
        case BLT: Output2File("blt " + reg1 + " " + reg2 + " " + num3); break;
        case BGE: Output2File("bge " + reg1 + " " + reg2 + " " + num3); break;
        case BGT: Output2File("bgt " + reg1 + " " + reg2 + " " + num3); break;
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
    Output2File("li $28 " + std::to_string(m_global));
    Output2File("move $fp $sp");
    Output2File("addiu $sp $fp -" + std::to_string(main_space_length)); 
    Output2File("la $ra " + main_bottom_label);
    Output2File("j main");
    for (; iter != m_pcode_queue.end(); ++iter) {
        string num1 = iter->GetNum1();
        string num2 = iter->GetNum2();
        string num3 = iter->GetNum3();
        if (num1 == "V0")
            iter->SetNum1("$2");
        if (num2 == "V0")
            iter->SetNum2("$2");
        if (num3 == "V0")
            iter->SetNum3("$2");
    }
    for (iter=m_pcode_queue.begin(); iter != m_pcode_queue.end(); ++iter) {
        switch (iter->GetOP()) {
            case LABEL: Output2File(iter->GetNum1() + ":"); break;
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
            case BASIC_LINE:
            case NOP: break;
            default: {
                std::cerr << "unknown pcode: " << iter->GetOP() << std::endl;
                fprintf(stderr, "not implemented pcode2mips type\n");         
            }
        }
    }
}

string RegisterPool::NaiveAcquireRegister() {
    for (Register tmp : m_register_array) {
        if (!tmp.IsUse()) {
            tmp.SetUse();
            return tmp.GetID();
        }
    }
    // (TODO)
    int random_number = GetRandom();
    m_register_array[random_number].SetUse();
    return m_register_array[random_number].GetID();
}
