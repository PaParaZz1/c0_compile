#include <string.h>
#include <stdio.h>
#include <limits.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <boost/variant.hpp>
#include "c0_compile_utils.hpp"

#define MAX_LINE_LENGTH 1024

#define FOREACH_FUNC(FUNC) \
        FUNC(WHILE_SYM) \
        FUNC(SWITCH_SYM) \
        FUNC(IF_SYM) \
        FUNC(CASE_SYM) \
        FUNC(DEFAULT_SYM) \
        FUNC(RETURN_SYM) \
        FUNC(PRINTF_SYM) \
        FUNC(SCANF_SYM) \
        FUNC(INT_SYM) \
        FUNC(CHAR_SYM) \
        FUNC(VOID_SYM) \
        FUNC(ADD_SYM) \
        FUNC(SUB_SYM) \
        FUNC(MUL_SYM) \
        FUNC(DIV_SYM) \
        FUNC(ASSIGN_SYM) \
        FUNC(EQUAL_SYM) \
        FUNC(NOT_EQUAL_SYM) \
        FUNC(SMALL_SYM) \
        FUNC(SMALL_EQUAL_SYM) \
        FUNC(LARGE_SYM) \
        FUNC(LARGE_EQUAL_SYM) \
        FUNC(CONST_SYM) \
        FUNC(COMMA_SYM) \
        FUNC(SEMICOLON_SYM) \
        FUNC(COLON_SYM) \
        FUNC(L_CIRCLE_BRACKET_SYM) \
        FUNC(L_SQUARE_BRACKET_SYM) \
        FUNC(L_CURLY_BRACKET_SYM) \
        FUNC(R_CIRCLE_BRACKET_SYM) \
        FUNC(R_SQUARE_BRACKET_SYM) \
        FUNC(R_CURLY_BRACKET_SYM) \
        FUNC(CHARACTER_SYM) \
        FUNC(STRING_SYM) \
        FUNC(IDENTITY_SYM) \
        FUNC(SINGLE_QUOTE_SYM) \
        FUNC(DOUBLE_QUOTE_SYM) \
        FUNC(INTERGER_SYM) \
        FUNC(EOF_SYM) \

#define GENERATE_ENUM(ENUM) ENUM,
#define GENERATE_STRING(STRING) #STRING,

using std::cout;
using std::endl;


typedef enum _SymbolName {
    FOREACH_FUNC(GENERATE_ENUM)
}SymbolName;

const char* symbol_name_string[] = {
    FOREACH_FUNC(GENERATE_STRING)
};

inline void PrintEnumString(SymbolName token) {
    cout << symbol_name_string[token] << endl;
}

inline bool isdigit(char ch) {
    return ch >= '0' && ch <= '9';
}

inline bool isalpha(char ch) {
    ch == '_' || ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z';
}

class SymbolValue {
public:
    SymbolValue() {}
    explicit SymbolValue(int _value) {
        value = _value;
    }
    explicit SymbolValue(char _value) {
        value = _value;
    }
    explicit SymbolValue(const std::string& _value) {
        value = _value;
    }
    template<typename T>
    T GetValue() {
        // TODO check type T
        return boost::get<T>(value);
    }
private:
    boost::variant<int, char, std::string> value;
};

class Symbol {
public:
    Symbol() {}
    void SetName(SymbolName _name) {
        this->name = _name;
    }
    template<typename T>
    void SetValue(T _value) {
        value = SymbolValue(_value);
    }
    SymbolName GetName() {
        return this->name;
    }
    template<typename T>
    T GetValue() {
        return value.GetValue<T>();
    }
private:
    SymbolName name;
    SymbolValue value;
};

class LexicalAnalysis {
public:
    LexicalAnalysis() {
        cout<<22;
        fp_in = fopen("test.cpp", "r");
        cout<<33;
        memset(buffer, 0, sizeof(buffer)*MAX_LINE_LENGTH);
        cout<<44;
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

void LexicalAnalysis::GetChar() {
    ch = fgetc(fp_in);
}

void LexicalAnalysis::UnGetChar() {
    ungetc(ch, fp_in);
}

void LexicalAnalysis::ParseSmallMark(Symbol& symbol) {
    GetChar();
    switch (ch) {
        case EOF: symbol.SetName(SMALL_SYM); UnGetChar(); break;
        case '=': symbol.SetName(SMALL_EQUAL_SYM); break;
        default: symbol.SetName(SMALL_SYM); UnGetChar();
    }
}

void LexicalAnalysis::ParseLargeMark(Symbol& symbol) {
    GetChar();
    switch (ch) {
        case EOF: symbol.SetName(LARGE_SYM); UnGetChar(); break;
        case '=': symbol.SetName(LARGE_EQUAL_SYM); break;
        default: symbol.SetName(LARGE_SYM); UnGetChar();
    }
}

void LexicalAnalysis::ParseEqualMark(Symbol& symbol) {
    GetChar();
    switch (ch) {
        case EOF: symbol.SetName(ASSIGN_SYM); UnGetChar(); break;
        case '=': symbol.SetName(EQUAL_SYM); break;
        default: symbol.SetName(ASSIGN_SYM); UnGetChar();
    }
}

compile_errcode LexicalAnalysis::ParseExclamatoryMark(Symbol& symbol) {
    int ret = COMPILE_OK;
    GetChar();
    switch (ch) {
        case EOF: ret = UNKNOWN_CHARACTER_ERROR; UnGetChar(); break;
        case '=': symbol.SetName(NOT_EQUAL_SYM); break;
        default: ret = UNKNOWN_CHARACTER_ERROR;
    }
    return ret;
}

compile_errcode LexicalAnalysis::ParseDigit(Symbol& symbol, bool negative) {
    long sum = 0;
    int number_count = 0;
    do {
        sum = sum * 10 + ch - '0';
        number_count++;
        GetChar();
    } while (!isdigit(ch));
    UnGetChar();
    if (number_count < 10) {
        sum = negative ? (-1*sum) : sum;
        if (sum >= INT_MIN && sum <= INT_MAX) {
            symbol.SetName(INTERGER_SYM);
            symbol.SetValue<int>(sum);
            return COMPILE_OK;
        }
    }
    return INVALID_DIGIT_ERROR;
}

compile_errcode LexicalAnalysis::ParseAdd(Symbol& symbol) {
    if (!enable_number) {
        symbol.SetName(ADD_SYM);
        return COMPILE_OK;
    } else {
        GetChar();
        if (isdigit(ch)) {
            return ParseDigit(symbol, false);
        } else {
            UnGetChar();
            symbol.SetName(ADD_SYM);
            return COMPILE_OK;
        }
    }
}

compile_errcode LexicalAnalysis::ParseSub(Symbol& symbol) {
    if (enable_number) {
        GetChar();
        if (isdigit(ch)) {
            return ParseDigit(symbol, true);
        } else {
            UnGetChar();
            symbol.SetName(SUB_SYM);
            return COMPILE_OK;
        }
    } else {
        symbol.SetName(SUB_SYM);
        return COMPILE_OK;
    }
}

compile_errcode LexicalAnalysis::ParseString(Symbol& symbol) {
    int ret = COMPILE_OK;
    buffer_index = 0;
ReadAgainString:
    GetChar();
    switch (ch) {
        case EOF: ret = INVALID_DOUBLE_QUOTE_ERROR; UnGetChar(); break;
        case '\n': ret = INVALID_DOUBLE_QUOTE_ERROR; break;
        case '\"': {
            buffer[buffer_index] = '\0';
            symbol.SetName(STRING_SYM);
            std::string str = buffer;
            symbol.SetValue<std::string>(str);
        }
        default: {
            if (buffer_index == MAX_LINE_LENGTH) {
                ret = INVALID_STRING_LENGTH_ERROR;
                buffer_index = 0;
            }
            buffer[buffer_index++] = ch;
            goto ReadAgainString;
        }
    }
    return ret;
}

compile_errcode LexicalAnalysis::ParseIdentity(Symbol& symbol) {
    int ret = COMPILE_OK;
    buffer_index = 0;
    do {
        if (buffer_index == MAX_LINE_LENGTH) {
            ret = INVALID_STRING_LENGTH_ERROR;
            buffer_index = 0;
        }
        buffer[buffer_index++] = ch;
        GetChar();
    } while (isdigit(ch) || isalpha(ch));
    UnGetChar();
    return ret;
}

compile_errcode LexicalAnalysis::ParseCharacter(Symbol& symbol) {
    GetChar();
    switch (ch) {
        case EOF: UnGetChar(); return INVALID_SINGLE_QUOTE_ERROR; 
        case '+':
        case '-':
        case '*':
        case '\\': buffer[0] = ch; goto CharacterCorrect;
        default: {
            if (isdigit(ch) || isalpha(ch)) {
                buffer[0] = ch;
                goto CharacterCorrect;
            } else {
                goto CharacterWrong;
            }
        }
    }
CharacterCorrect:
    GetChar();
    if (ch == '\'') {
        symbol.SetName(CHARACTER_SYM);
        symbol.SetValue<char>(buffer[0]);
        return COMPILE_OK;
    }
CharacterWrong:
    switch (ch) {
        case EOF: UnGetChar(); return INVALID_SINGLE_QUOTE_ERROR;
        case ' ':
        case '\n':
        case '\t':
        case '\r':
        case '\'': return INVALID_SINGLE_QUOTE_ERROR;
        default: GetChar(); goto CharacterWrong;
    }
}

compile_errcode LexicalAnalysis::GetSym(Symbol& symbol) {
    if (!fp_in) {
        std::cerr << "bad file" << endl;
        return BAD_FILE_ERROR;
    }
    int ret = COMPILE_OK;
ParseSym:
    GetChar();
    switch (ch) {
        case EOF: {
            symbol.SetName(EOF_SYM);
            break;
        }
        case '{': {
            symbol.SetName(L_CURLY_BRACKET_SYM);
            break;
        }
        case '}': {
            symbol.SetName(R_CURLY_BRACKET_SYM);
            break;
        }
        case '(': {
            symbol.SetName(L_CIRCLE_BRACKET_SYM);
            break;
        }
        case ')': {
            symbol.SetName(R_CIRCLE_BRACKET_SYM);
            break;
        }
        case '[': {
            symbol.SetName(L_SQUARE_BRACKET_SYM);
            break;
        }
        case ']': {
            symbol.SetName(R_SQUARE_BRACKET_SYM);
            break;
        }
        case '*': {
            symbol.SetName(MUL_SYM);
            break;
        }
        case '\\': {
            symbol.SetName(DIV_SYM);
            break;
        }
        case ',': {
            symbol.SetName(COMMA_SYM);
            break;
        }
        case ';': {
            symbol.SetName(SEMICOLON_SYM);
            break;
        }
        case ':': {
            symbol.SetName(COLON_SYM);
        }
        case '!': {
            ret = ParseExclamatoryMark(symbol);
            break;
        }
        case '=': {
            ParseEqualMark(symbol);
            break;
        }
        case '>': {
            ParseLargeMark(symbol);
            break;
        }
        case '<': {
            ParseSmallMark(symbol);
            break;
        }
        case '+': {
            ret = ParseAdd(symbol);
            break;
        }
        case '-': {
            ret = ParseSub(symbol);
            break;
        }
        case '\"': {
            ret = ParseString(symbol);
            break;
        }
        case '\'': {
            ret = ParseCharacter(symbol);
            break;
        }
        case ' ':
        case '\t':
        case '\n':
        case '\r': goto ParseSym;
        default: {
            if (isalpha(ch)) {
                ret = ParseIdentity(symbol);
            } else if (isdigit(ch)) {
                ret = ParseDigit(symbol, false);
            } else {
                ret = UNKNOWN_CHARACTER_ERROR;
            }
        }
    }
    enable_number = symbol.GetName() != INTERGER_SYM;
    return ret;
}

std::vector<std::string> keyword = {
    "while",
    "if",
    "switch",
    "case",
    "void",
    "default",
    "int",
    "char",
    "return",
    "const",
    "scanf",
    "printf",
    "main"
};
int main() {
    int ret = COMPILE_OK;
    const char test_file_name[] = "test.cpp";
    cout<<1<<endl;
    LexicalAnalysis handle_lexical_analysis;
    //LexicalAnalysis* handle_lexical_analysis = new LexicalAnalysis(test_file_name);
    cout<<2<<endl;
    Symbol symbol;
    cout<<3<<endl;
    while (true) {
        ret = handle_lexical_analysis.GetSym(symbol);
        if (ret == COMPILE_OK) {
            SymbolName name = symbol.GetName();
            if (name == EOF_SYM) {
                break;
            } else {
                cout << symbol_name_string[name] << endl;
            }
        } else {
            std::cerr << "errcode:" << ret << endl;
        }
    }
    printf("%s\n", symbol_name_string[DIV_SYM]);
    
    return 0;
}
