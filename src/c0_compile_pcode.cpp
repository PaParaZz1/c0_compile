#include <stdio.h>
#include <unordered_map>
#include "c0_compile_pcode.hpp"
#include "c0_compile_symbol.hpp"
#define EMPTY_STR ""
using std::unordered_map;

extern FunctionTable* handle_func_table;

const char* pcode_string[] = {
    FOREACH_FUNC_PCODE(GENERATE_STRING)
};

PcodeGenerator* pcode_generator;

void PcodeGenerator::PrintAllPcode() {
    auto iter = m_pcode_queue.begin();
    int count = 0;
    for (; iter != m_pcode_queue.end(); ++iter) {
        this->PrintSinglePcode(*iter);
        count++;
    }
    printf("generated pcode count: %d\n", count);
}

void PcodeGenerator::CopyPcode(vector<Pcode>& target_queue) {
    auto iter = m_pcode_queue.begin();
    for (; iter != m_pcode_queue.end(); ++iter) {
        target_queue.push_back(*iter);
    }
}

void PcodeGenerator::MergeSelfAssign() {
    int count;
    do {
        count = 0;
        for (int i=0; i<m_pcode_queue.size()-1; ++i) {
            if (m_pcode_queue[i].GetNum1() == m_pcode_queue[i+1].GetNum2() && m_pcode_queue[i+1].GetOP() == ASSIGN) {
                m_pcode_queue[i].SetNum1(m_pcode_queue[i+1].GetNum1());
                m_pcode_queue[i+1].SetOP(NOP);
                i++;
                count++;
            }
        }
        for (auto iter = m_pcode_queue.begin(); iter != m_pcode_queue.end(); ++iter) {
            if (iter->GetOP() == NOP) {
                iter = m_pcode_queue.erase(iter);
            }
        }
    } while (count != 0);
}

void PcodeGenerator::DivideBasicBlock() {
    Pcode basic_line(BASIC_LINE, "-----------------------------------", EMPTY_STR, EMPTY_STR);
    vector<Pcode> temp_queue;
    this->CopyPcode(temp_queue);
    auto iter = temp_queue.begin();
    temp_queue.insert(iter, basic_line);
    iter++;
    for (int i=0; i<m_pcode_queue.size(); ++i) {
        PcodeType op = m_pcode_queue[i].GetOP();
        switch(op) {
            case BEQ:
            case BNE:
            case BLT:
            case BLE:
            case BGT:
            case BGE:
            case JUMP:
            case FUNC_BOTTOM:
            case CALL: {
                iter++;
                temp_queue.insert(iter, basic_line);
                iter++;
                break;
            }
            default: {
                iter++;
            }
        }
    }
    m_pcode_queue.swap(temp_queue);
}

bool PcodeGenerator::CanInline(const string& top_label, const string& bottom_label) {
    if (top_label == "main")
        return false;
    vector<Pcode>::iterator iter_top;
    vector<Pcode>::iterator iter_bottom;
    auto iter = m_pcode_queue.begin();
    for (; iter != m_pcode_queue.end(); ++iter) {
        PcodeType op = iter->GetOP();
        string num1 = iter->GetNum1();
        if (num1 == top_label && op == LABEL)
            iter_top = iter;
        if (num1 == bottom_label && op == LABEL)
            iter_bottom = iter;
    }
    for (auto iter = iter_top; iter != iter_bottom; ++iter) {
        PcodeType op = iter->GetOP();
        string num1 = iter->GetNum1();
        if ((op == JUMP && num1 != "RA") || op == CALL || pcode_string[op][0] == 'B')
        //if ((op == JUMP && num1 != "RA") || op == CALL)
            return false;
    }
    return true;
}

bool IsTempName(const string& str) {
    if (str[0] == 't') {
        if (atoi(str.substr(1).c_str()) != 0) {
            return true;
        }
    }
    return false;
}
void PcodeGenerator::CallReplace(const vector<Pcode>::iterator& iter_call, const string& top_label, const string& bottom_label, int argument_number) {
    vector<Pcode>::iterator iter_top;
    vector<Pcode>::iterator iter_bottom;
    for (auto iter=m_pcode_queue.begin(); iter != m_pcode_queue.end(); ++iter) {
        PcodeType op = iter->GetOP();
        string num1 = iter->GetNum1();
        if (num1 == top_label && op == LABEL)
            iter_top = iter;
        if (num1 == bottom_label && op == LABEL)
            iter_bottom = iter;
    }
    iter_top++;
    vector<Pcode> origin(iter_top, iter_bottom);
    // replace temp
    vector<string> temp_vector;
    for (auto iter=origin.begin(); iter != origin.end(); ++iter) {
        string num1 = iter->GetNum1();
        string num2 = iter->GetNum2();
        string num3 = iter->GetNum3();
        PcodeType op = iter->GetOP();
        if (IsTempName(num1)) {
            temp_vector.push_back(num1);
        }
        if (IsTempName(num2)) {
            temp_vector.push_back(num2);
        }
        if (IsTempName(num3)) {
            temp_vector.push_back(num3);
        }
        
        if (op == JUMP && num1 == "RA") {  // remove JUMP RA
            iter = origin.erase(iter);
            iter--;
        }
    }
    sort(temp_vector.begin(), temp_vector.end());
    temp_vector.erase(unique(temp_vector.begin(), temp_vector.end()), temp_vector.end());
    unordered_map<string, string> temp_map;
    for (auto iter=temp_vector.begin(); iter != temp_vector.end(); ++iter) {
        string new_temp = this->GetNextTemp();
        temp_map[*iter] = new_temp;
    }
    for (auto iter=origin.begin(); iter != origin.end(); ++iter) {
        string num1 = iter->GetNum1();
        string num2 = iter->GetNum2();
        string num3 = iter->GetNum3();
        PcodeType op = iter->GetOP();
        if (IsTempName(num1)) {
            //printf("%s---%s\n", num1.c_str(), temp_map[num1].c_str());
            iter->SetNum1(temp_map[num1]);
        }
        if (IsTempName(num2)) {
            //printf("%s---%s\n", num2.c_str(), temp_map[num2].c_str());
            iter->SetNum2(temp_map[num2]);
        }
        if (IsTempName(num3)) {
            //printf("%s---%s\n", num3.c_str(), temp_map[num3].c_str());
            iter->SetNum3(temp_map[num3]);
        }
    }
    // replace argument
    if (argument_number != 0) {
        unordered_map<string, string> para_map;
        auto iter = iter_call;
        int count = 0;
        string func_name = iter_call->GetNum3();
        for (; iter != m_pcode_queue.begin(); iter--) {
            PcodeType op = iter->GetOP();
            string num1 = iter->GetNum1();
            string num2 = iter->GetNum2();
            string num3 = iter->GetNum3();
            if (op == PARA && num3 == func_name) {
                int value = atoi(num2.c_str());
                if (value == 0) {
                    para_map[num1] = num2;
                    iter->SetOP(NOP);
                } else {
                    string temp_name = this->GetNextTemp();
                    //Pcode pcode(ASSIGN, temp_name, std::to_string(value), EMPTY_STR);
                    //iter = m_pcode_queue.insert(iter, pcode);
                    //iter--;
                    iter->SetOP(ASSIGN);
                    iter->SetNum1(temp_name);
                    iter->SetNum2(std::to_string(value));
                    iter->SetNum3(EMPTY_STR);
                    para_map[num1] = temp_name;
                }
                count++;
                if (count == argument_number) {
                    break;
                }
            }
        }
        if (iter == m_pcode_queue.begin()) {
            fprintf(stderr, "no enough argument\n");
            return;
        }
        for (auto iter=origin.begin(); iter != origin.end(); ++iter) {
            string num1 = iter->GetNum1();
            string num2 = iter->GetNum2();
            string num3 = iter->GetNum3();
            PcodeType op = iter->GetOP();
            if (para_map.find(num1) != para_map.end()) {
                iter->SetNum1(para_map[num1]);
            }
            if (para_map.find(num2) != para_map.end()) {
                iter->SetNum2(para_map[num2]);
            }
            if (para_map.find(num3) != para_map.end()) {
                iter->SetNum3(para_map[num3]);
            }
        }
    }
    // insert
    iter_call->SetOP(NOP);
    //printf("insert begin%d\n", m_pcode_queue.size());
    m_pcode_queue.insert(iter_call, origin.begin(), origin.end());
    //printf("insert end%d\n", m_pcode_queue.size());
}

void PcodeGenerator::InlineReplace() {
    handle_func_table->ZeroCurrentTermPtr();
    string top_label;
    string bottom_label;
    while (handle_func_table->GetFuncLabel(top_label, bottom_label)) {
        if (CanInline(top_label, bottom_label)){
            fprintf(stdout, "can inline label:%s---%s\n", top_label.c_str(), bottom_label.c_str());
            string func_name;
            handle_func_table->GetCurrentTermName(func_name);
            int argument_number;
            handle_func_table->GetCurrentTermArgumentNumber(argument_number);
            // replace func code
            for (auto iter=m_pcode_queue.begin(); iter!=m_pcode_queue.end(); ++iter) {
                PcodeType op = iter->GetOP();
                if (op == CALL) {
                    string num3 = iter->GetNum3();
                    if (num3 == func_name) {
                        CallReplace(iter, top_label, bottom_label, argument_number);
                    }
                }
            }
        }
        handle_func_table->NextTerm();
    }
    for (auto iter = m_pcode_queue.begin(); iter != m_pcode_queue.end(); ++iter) {
        if (iter->GetOP() == NOP) {
            iter = m_pcode_queue.erase(iter);
        }
    }
}
