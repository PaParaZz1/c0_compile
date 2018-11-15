#include <limits.h>
#include "c0_compile.hpp"
#include "c0_compile_utils.hpp"
#include "c0_compile_symbol.hpp"
#include "c0_compile_lexical_analysis.hpp"

using std::endl;

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
    } while (c0_compile::isdigit(ch));
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
        if (c0_compile::isdigit(ch)) {
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
        if (c0_compile::isdigit(ch)) {
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
            break;
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
    } while (c0_compile::isdigit(ch) || isalpha(ch));
    buffer[buffer_index] = '\0';
    std::string str = buffer;
    if (keyword.count(str)) {
        symbol.SetName(keyword.find(str)->second);
    } else {
        symbol.SetName(IDENTITY_SYM);
    }
    symbol.SetValue<std::string>(str);
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
            if (c0_compile::isdigit(ch) || isalpha(ch)) {
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
            break;
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
            } else if (c0_compile::isdigit(ch)) {
                ret = ParseDigit(symbol, false);
            } else {
                ret = UNKNOWN_CHARACTER_ERROR;
            }
        }
    }
    SymbolName ret_name = symbol.GetName();
    if (ret_name == INTERGER_SYM || ret_name == IDENTITY_SYM) {
        enable_number = false;
    } else {
        enable_number = true;
    }
    return ret;
}
