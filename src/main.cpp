#include <string.h>
#include <iostream>
#include "c0_compile_utils.hpp"
#include "c0_compile_lexical_analysis.hpp"
#include "c0_compile_gramma_analysis.hpp"
#include "c0_compile_symbol.hpp"

using std::cout;
using std::endl;

extern SymbolQueue* handle_symbol_queue;

void TestLexicalAnalysis(const char* test_file_name) {
    int ret = COMPILE_OK;
    LexicalAnalysis lexical_analysis(test_file_name);
    Symbol symbol;
    bool log_flag = false;
    while (true) {
        ret = lexical_analysis.GetSym(symbol);
        if (ret == COMPILE_OK) {
            SymbolName name = symbol.GetName();
            if (name == EOF_SYM) {
                break;
            } else if (!log_flag) {
                continue;
            } else if (name == IDENTIFIER_SYM) {
                cout << symbol_name_string[name] << " " << symbol.GetValue<std::string>() << endl;
            } else if (name == STRING_SYM) {
                cout << symbol_name_string[name] << " " << symbol.GetValue<std::string>() << endl;
            } else if (name == CHARACTER_SYM) {
                cout << symbol_name_string[name] << " " << symbol.GetValue<char>() << endl;
            } else if (name == INTERGER_SYM) {
                cout << symbol_name_string[name] << " " << symbol.GetValue<int>() << endl;
            } else {
                cout << symbol_name_string[name] << endl;
            }
        } else {
            std::cerr << "errcode:" << ret << endl;
        }
    }
}

void TestGrammaAnalysis(const char* test_file_name) {
    int ret = COMPILE_OK;
    LexicalAnalysis lexical_analysis(test_file_name);
    Symbol symbol;
    handle_symbol_queue = new SymbolQueue;
    while (true) {
        ret = lexical_analysis.GetSym(symbol);
        handle_symbol_queue->PushSymbol(symbol);
        SymbolName name = symbol.GetName();
        if (name == EOF_SYM)
            break;
    }
    cout << "push over" << endl;
    Program program;
    program.Parse();
    delete(handle_symbol_queue);
}

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Usage: ./compile_test /path_to_source_code" << endl;
    } else {
        TestLexicalAnalysis(argv[1]);
        TestGrammaAnalysis(argv[1]);
    }
    return 0;
}
