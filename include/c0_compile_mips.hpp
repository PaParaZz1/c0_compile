#ifndef C0_COMPILE_MIPS_H_
#define C0_COMPILE_MIPS_H_
#include <vector>
#include <string>
#include "c0_compile_pcode.hpp"

using std::string;
using std::vector;

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
    void Translate();
    void Output2File(string str) {
        fprintf(m_fp_mips, "%s]n", str.c_str());
    }
private:
    FILE* m_fp_mips;
    vector<Pcode> m_pcode_queue;
    void ExtractString();
};
extern MipsGenerator* handle_mips_generator;
#endif // C0_COMPILE_MIPS_H_
