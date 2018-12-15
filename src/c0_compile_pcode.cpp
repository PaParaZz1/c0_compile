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
