#ifndef _C0_COMPILE_LEXICAL_ANALYSIS_H_
#define _C0_COMPILE_LEXICAL_ANALYSIS_H_
#include <string.h>
#include <stdio.h>
#include <string>
#include "c0_compile.hpp"
#include "c0_compile_utils.hpp"
#include "c0_compile_symbol.hpp"

namespace c0_compile {
    inline bool isdigit(char ch) {
        return ch >= '0' && ch <= '9';
    }

    inline bool isalpha(char ch) {
        return ch == '_' || ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z';
    }
}

class LexicalAnalysis {
public:
    explicit LexicalAnalysis(const char* filename) {
        fp_in = fopen(filename, "r");
        memset(buffer, 0, sizeof(char)*MAX_LINE_LENGTH);
        buffer_index = 0;
        enable_number = true;
    }
    ~LexicalAnalysis() {
        if (!fp_in)
            fclose(fp_in);
    }
    compile_errcode GetSym(Symbol& symbol);
private: 
    FILE* fp_in;
    char ch;
    char buffer[MAX_LINE_LENGTH];
    int buffer_index;
    bool enable_number;
    void GetChar();
    void UnGetChar();
    void ParseSmallMark(Symbol& symbol);
    void ParseLargeMark(Symbol& symbol);
    void ParseEqualMark(Symbol& symbol);
    compile_errcode ParseExclamatoryMark(Symbol& symbol);
    compile_errcode ParseDigit(Symbol& symbol, bool negative);
    compile_errcode ParseAdd(Symbol& symbol);
    compile_errcode ParseSub(Symbol& symbol);
    compile_errcode ParseString(Symbol& symbol);
    compile_errcode ParseIdentity(Symbol& symbol);
    compile_errcode ParseCharacter(Symbol& symbol);
};

#endif // _C0_COMPILE_LEXICAL_ANALYSIS_H_
