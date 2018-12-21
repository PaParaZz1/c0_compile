#ifndef C0_COMPILE_MIPS_H_
#define C0_COMPILE_MIPS_H_
#include <vector>
#include <string>
#include <unordered_map>
#include "c0_compile_pcode.hpp"

using std::string;
using std::vector;
using std::unordered_map;

class MipsGenerator {
public:
    MipsGenerator(const char* file_name, vector<Pcode>& source_queue) {
        m_fp_mips = fopen(file_name, "w");
        m_pcode_queue.assign(source_queue.begin(), source_queue.end());
        m_relative_addr = 0;
        m_string_label_count = 0;
        m_global = 0x2ffc;
    }
    ~MipsGenerator() {
        if (!m_fp_mips)
            fclose(m_fp_mips);
    }
    void Translate();
private:
    int m_sp;
    int m_fp;
    int m_global;
    int m_string_label_count;
    FILE* m_fp_mips;
    vector<Pcode> m_pcode_queue;
    vector<Pcode> m_parameter_stack;
    unordered_map<string, int> m_temp2address;
    map<string, string> m_string_map;
    int m_relative_addr;
    compile_errcode FindRelativeAddr(string temp_name, int& addr);
    void GenerateStore(string temp_name, string type);
    void GenerateLoad(string target, string source, string type);
    void GetNextStringLabel(string& string_label);
    void ExtractString();
    void TranslateADDType(Pcode& item);
    void TranslateMULType(Pcode& item);
    void TranslateBType(Pcode& item);
    void TranslateASSIGN(Pcode& item);
    void TranslatePara(Pcode& item);
    void TranslateCall(Pcode& item);
    void TranslateJUMP(Pcode& item);
    void TranslateInput(Pcode& item);
    void TranslateOutput(Pcode& item);
    void TranslateLoadAddr(Pcode& item);
    void TranslateLoadValue(Pcode& item);
    void Output2File(string str) {
        fprintf(m_fp_mips, "%s\n", str.c_str());
    }
};
extern MipsGenerator* handle_mips_generator;
#endif // C0_COMPILE_MIPS_H_
