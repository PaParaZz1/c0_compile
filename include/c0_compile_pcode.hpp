#ifndef C0_COMPILE_PCODE_H_
#define C0_COMPILE_PCODE_H_
#include <string>
#include <vector>
#include <stack>
#include <iostream>
using std::string;
using std::vector;
using std::stack;
#define FOREACH_FUNC_PCODE(FUNC) \
        FUNC(ADD) \
        FUNC(SUB) \
        FUNC(MUL) \
        FUNC(DIV) \
        FUNC(ASSIGN) \
        FUNC(CALL) \
        FUNC(BEQ) \
        FUNC(BNE) \
        FUNC(BGE) \
        FUNC(BGT) \
        FUNC(BLE) \
        FUNC(BLT) \
        FUNC(LABEL) \
        FUNC(RETURN) \
        FUNC(JUMP) \
        FUNC(INPUT) \
        FUNC(OUTPUT) \
        FUNC(PARA) \

#define GENERATE_ENUM(ENUM) ENUM,
#define GENERATE_STRING(STRING) #STRING,
        
typedef enum _PcodeType {
    FOREACH_FUNC_PCODE(GENERATE_ENUM)
}PcodeType;

extern const char* pcode_string[];

class Pcode {
public:
    Pcode(PcodeType op, string num1, string num2, string num3) : m_op(op), m_num1(num1), m_num2(num2), m_num3(num3) {}
    string ToString() {
        return m_num1 + string("\t") + m_num2 + string("\t") + string(pcode_string[m_op]) + string("\t") + m_num3;
    }
private:
    // num1 : num2 op num3
    PcodeType m_op;
    string m_num1;
    string m_num2;
    string m_num3;
};

class PcodeGenerator {
public:
    explicit PcodeGenerator(const char* pcode_file_name) {
        m_fp = fopen(pcode_file_name, "w");
        m_temp_count = 0;
        m_label_count = 0;
    }
    void Insert(Pcode& pcode) {
        m_pcode_queue.push_back(pcode);
    }
    int PcodeLen() {
        return m_pcode_queue.size();
    }
    void PrintSinglePcode(Pcode& pcode) {
        fprintf(m_fp, "%s\n", pcode.ToString().c_str());
    }
    void AddTempCount() {
        m_temp_count++;
    }
    void PrintAllPcode();
    string TempNameGenerator() {
        AddTempCount();
        string str = string("t") + std::to_string(m_temp_count);
        return str;
    }
    void AddLabelCount() {
        m_label_count++;
    }
    string GetNextLabel() {
        this->AddLabelCount();
        string label = string("label") + std::to_string(m_label_count);
        return label;
    }
    int m_temp_count;
    int m_label_count;
private:
    FILE* m_fp;
    vector<Pcode> m_pcode_queue;
};

#endif // C0_COMPILE_PCODE_H_
