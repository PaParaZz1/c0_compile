#ifndef C0_COMPILE_MIPS_H_
#define C0_COMPILE_MIPS_H_
#include <vector>
#include <string>
#include <unordered_map>
#include <regex>
#include "c0_compile_pcode.hpp"

using std::string;
using std::vector;
using std::unordered_map;

class Register {
public:
    Register(const string& id, bool is_float_register) : m_id(id), m_is_float_register(is_float_register) {
        m_is_use = false;
    }
    string GetID() const {
        return m_id;
    }
    bool IsUse() const {
        return m_is_use;
    }
    void SetUse() {
        m_is_use = true;
    }
private:
    string m_id;
    bool m_is_use;
    bool m_is_float_register;
};

class RegisterPool {
public:
    RegisterPool(bool enable_float_register) {
        for (int i=3; i<29; ++i) {
            m_register_array.push_back(Register("$" + std::to_string(i), false));
        }
        if (enable_float_register) {
            for (int i=0; i<31; ++i) {
                m_register_array.push_back(Register("$f" + std::to_string(i), true));
            }
        }
    }
    int GetAllRegisterNumber() const {
        return m_register_array.size();
    }
    int GetRandom() const {
        return rand()%(GetAllRegisterNumber() + 1) - 1;
    }
    string NaiveAcquireRegister();
private:
    vector<Register> m_register_array;
};

class MipsGenerator {
public:
    MipsGenerator(const char* file_name, vector<Pcode>& source_queue) {
        m_fp_mips = fopen(file_name, "w");
        m_pcode_queue.assign(source_queue.begin(), source_queue.end());
        m_relative_addr = 0;
        m_string_label_count = 0;
        m_global = 0x10010000;
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
    void GenerateStore(const string& source, const string& offset, const string& base, const string& type);
    void GenerateLoad(string target, string source, string type);
    void GetNextStringLabel(string& string_label);
    void ExtractString();
    void TranslateADD(Pcode& item);
    void TranslateSUB(const Pcode& item);
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

class AdvancedMipsGenerator : public MipsGenerator {
public:
    using MipsGenerator::MipsGenerator;
private:
    void Transform2REG(const string& in, string& out);
    bool GlobalJudge(const string& str) const {
        std::regex re("g\\d+");
        return std::regex_match(str, re);
    }

    bool FPJudge(const string& str) const {
        std::regex re("fp\\d+");
        return std::regex_match(str, re);
    }

    bool TMPJudge(const string& str) const {
        std::regex re("t\\d+");
        return std::regex_match(str, re);
    }

    bool REGJudge(const string& str) const {
        std::regex re("\\$\\d+");
        return std::regex_match(str, re);
    }
};
extern MipsGenerator* handle_mips_generator;
extern const int global_register_number;
#endif // C0_COMPILE_MIPS_H_
