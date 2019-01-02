#include <stdio.h>
#include <c0_compile_pcode.hpp>

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
