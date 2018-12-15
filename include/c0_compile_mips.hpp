#ifndef C0_COMPILE_MIPS_H_
#define C0_COMPILE_MIPS_H_
#include <vector>
#include "c0_compile_pcode.hpp"

class MipsGenerator {
public:
    MipsGenerator(const char* file_name, vector<Pcode>& source_queue) {
        m_fp_mips = fopen("mips.txt", "w");
        m_pcode_queue.assign(source_queue.begin(), source_queue.end());
    }
    ~MipsGenerator() {
        if (!m_fp_mips)
            fclose(m_fp_mips);
    }
private:
    FILE* m_fp_mips;
    vector<Pcode> m_pcode_queue;
};
extern MipsGenerator* handle_mips_generator;
#endif // C0_COMPILE_MIPS_H_
