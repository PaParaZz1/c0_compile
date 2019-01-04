#ifndef C0_COMPILE_PCODE_H_
#define C0_COMPILE_PCODE_H_
#include <string>
#include <vector>
#include <stack>
#include <iostream>
#include <set>

using std::string;
using std::vector;
using std::stack;
using std::pair;
using std::set;

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
        FUNC(FUNC_BOTTOM) \
        FUNC(ARRAY_ASSIGN) \
        FUNC(LOAD_VALUE) \
        FUNC(NOP) \
        FUNC(BASIC_LINE) \

#define GENERATE_ENUM(ENUM) ENUM,
#define GENERATE_STRING(STRING) #STRING,

#define STRING string("string")
#define INT_EXPRESSION string("int_expression")
#define CHAR_EXPRESSION string("char_expression")
        
typedef enum _PcodeType {
    FOREACH_FUNC_PCODE(GENERATE_ENUM)
}PcodeType;

extern const char* pcode_string[];

class Pcode {
public:
    Pcode(PcodeType op, string num1, string num2, string num3) : m_op(op), m_num1(num1), m_num2(num2), m_num3(num3) {
        m_comment = string("");
    }
    Pcode(PcodeType op, string num1, string num2, string num3, string comment) : m_op(op), m_num1(num1), m_num2(num2), m_num3(num3), m_comment(comment) {}
    string ToString() {
        if (m_comment == string(""))
            return m_num1 + string("\t") + m_num2 + string("\t") + string(pcode_string[m_op]) + string("\t") + m_num3;
        else
            return m_num1 + string("\t") + m_num2 + string("\t") + string(pcode_string[m_op]) + string("\t") + m_num3 + "\t" + m_comment;
    }
    PcodeType GetOP() const {
        return m_op;
    }
    string GetNum1() const {
        return m_num1;
    }
    string GetNum2() const {
        return m_num2;
    }
    string GetNum3() const {
        return m_num3;
    }
    string GetComment() const {
        if (m_comment == "")
            return m_comment;
        else
            return m_comment.substr(1);
    }
    void SetNum1(const string& other) {
        m_num1 = other;
    }
    void SetNum2(const string& other) {
        m_num2 = other;
    }
    void SetNum3(const string& other) {
        m_num3 = other;
    }
    void SetOP(const PcodeType& other) {
        m_op = other;
    }
private:
    // num1 : num2 op num3
    PcodeType m_op;
    string m_num1;
    string m_num2;
    string m_num3;
    string m_comment;
};

class PcodeGenerator {
public:
    class BasicBlock{
    public:
        BasicBlock(int top, int bottom) : m_top(top), m_bottom(bottom) {}
        bool CalculateDU();
        bool CalculateGK();  // TODO
    private:
        int m_top;
        int m_bottom;
        set<string> m_define_set;
        set<string> m_use_set;
        bool m_is_valid;
    };
    typedef vector<pair<string, int> > RefCount;
    typedef pair<string, string> ReplaceMap;
    explicit PcodeGenerator(const char* pcode_file_name) {
        m_fp_pcode = fopen(pcode_file_name, "w");
        m_temp_count = 0;
        m_label_count = 0;
        m_argument_count = 0;
    }
    ~PcodeGenerator() {
        if (!m_fp_pcode)
            fclose(m_fp_pcode);
    }
    void Insert(Pcode& pcode) {
        m_pcode_queue.push_back(pcode);
    }
    int PcodeLen() {
        return m_pcode_queue.size();
    }
    void PrintSinglePcode(Pcode& pcode) {
        fprintf(m_fp_pcode, "%s\n", pcode.ToString().c_str());
    }
    void PrintAllPcode();
    string GetNextTemp() {
        m_temp_count++;
        string str = string("t") + std::to_string(m_temp_count);
        return str;
    }
    string GetNextLabel() {
        m_label_count++;
        string label = string("label") + std::to_string(m_label_count);
        return label;
    }
    void ZeroArgumentCount() {
      m_argument_count = 0;
    }
    string GetNextArgument() {
        m_argument_count++;
        string argument = string("argument") + std::to_string(m_argument_count);
        return argument;
    }
    void CopyPcode(vector<Pcode>& target_queue);
    // optimization
    void MergeSelfAssign();
    void DivideBasicBlock();
    void InlineReplace();
    void ActiveStreamAnalysis();
    void ReferenceCount();
private:
    int m_temp_count;
    int m_label_count;
    int m_argument_count;
    FILE* m_fp_pcode;
    vector<Pcode> m_pcode_queue;
    vector<BasicBlock> m_basic_block;
    vector<vector<ReplaceMap> > m_replace_vec;
    bool CanInline(const string& top_label, const string& bottom_label);
    void CallReplace(const vector<Pcode>::iterator& iter_call, const string& top_label, const string& bottom_label, int argument_number);
    bool ReferenceCountSearch(const RefCount& vec, const string& source, string& replace);
};
#endif // C0_COMPILE_PCODE_H_
