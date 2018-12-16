#include <string.h>
#include <iostream>
#include "c0_compile_utils.hpp"
#include "c0_compile_lexical_analysis.hpp"
#include "c0_compile_gramma.hpp"
#include "c0_compile_symbol.hpp"
#include "c0_compile_pcode.hpp"
#include "c0_compile_mips.hpp"

using std::cout;
using std::endl;

extern SymbolQueue* handle_symbol_queue;
extern SymbolQueue* handle_correct_queue;
extern SymbolTableTree* symbol_table_tree;
extern PcodeGenerator* pcode_generator;
extern FunctionTable* handle_func_table;

void TestLexicalAnalysis(const char* test_file_name) {
    int ret = COMPILE_OK;
    LexicalAnalysis lexical_analysis(test_file_name);
    if (!lexical_analysis.CheckFile()) {
        std::cerr << "bad file" << endl;
        return;
    }
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
    if (!lexical_analysis.CheckFile()) {
        std::cerr << "bad file" << endl;
        return;
    }
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

void TestSemanticAnalysis(const char* test_file_name) {
    int ret = COMPILE_OK;
    LexicalAnalysis lexical_analysis(test_file_name);
    if (!lexical_analysis.CheckFile()) {
        std::cerr << "bad file" << endl;
        return;
    }
    Symbol symbol;
    handle_symbol_queue = new SymbolQueue;
    symbol_table_tree = new SymbolTableTree;
    Program program;
    pcode_generator = new PcodeGenerator("pcode.txt");
    while (true) {
        ret = lexical_analysis.GetSym(symbol);
        if (ret != COMPILE_OK) {
            std::cerr << "lexical analysys error, please run TestLexicalAnalysis to check" << endl;
            goto ERROR1;
        }
        handle_symbol_queue->PushSymbol(symbol);
        SymbolName name = symbol.GetName();
        if (name == EOF_SYM)
            break;
    }
    cout << "push over" << endl;
    program.Parse();
    symbol_table_tree->CreateTable(string("global"), VOID, string("end"));
    symbol_table_tree->SetCurrentTableName(string("global"));
    handle_correct_queue = handle_symbol_queue;
    handle_correct_queue->Restart();
    program.Action();
    symbol_table_tree->PrintTree();
ERROR1:
    delete(pcode_generator);
    delete(symbol_table_tree);
    delete(handle_symbol_queue);
}

void MipsGenerate(vector<Pcode>& source_queue) {
    handle_mips_generator = new MipsGenerator("mips.txt", source_queue);
    handle_mips_generator->Translate();
    delete(handle_mips_generator);
}

void TestGenerate(const char* test_file_name) {
    int ret = COMPILE_OK;
    LexicalAnalysis lexical_analysis(test_file_name);
    if (!lexical_analysis.CheckFile()) {
        std::cerr << "bad file" << endl;
        return;
    }
    Symbol symbol;
    handle_symbol_queue = new SymbolQueue;
    symbol_table_tree = new SymbolTableTree;
    Program program;
    pcode_generator = new PcodeGenerator("pcode.txt");
    handle_func_table = new FunctionTable;
    vector<Pcode> pcode_copy;
    // lexical analysis
    while (true) {
        ret = lexical_analysis.GetSym(symbol);
        if (ret != COMPILE_OK) {
            std::cerr << "lexical analysis error, please run TestLexicalAnalysis to check" << endl;
            goto ERROR2;
        }
        handle_symbol_queue->PushSymbol(symbol);
        SymbolName name = symbol.GetName();
        if (name == EOF_SYM)
            break;
    }
    cout << "lexical analysis OK" << endl;
    // gramma analysis
    if ((ret = program.Parse()) != COMPILE_OK) {
        std::cerr << "gramma analysis error" << endl;
        std::cerr << "ret:" << ret << endl;
        goto ERROR2;
    }
    cout << "gramma analysis OK" << endl;
    // symbol table and semantic check
    symbol_table_tree->CreateTable(string("global"), VOID, string("end"));
    symbol_table_tree->SetCurrentTableName(string("global"));
    handle_correct_queue = handle_symbol_queue;
    handle_correct_queue->Restart();
    if ((ret = program.Action()) != COMPILE_OK) {
        std::cerr << "semantic check error" << endl;
        std::cerr << "ret:" << ret << endl;
        goto ERROR2;
    }
    symbol_table_tree->PrintTree();
    cout << "symbol table and semantic check OK" << endl;
    // pcode generate
    handle_correct_queue->Restart();
    program.Generate();
    pcode_generator->PrintAllPcode();
    handle_func_table->PrintAllTerm();
    cout << "generate pcode OK" << endl;
    // mips generate
    pcode_generator->CopyPcode(pcode_copy);
    MipsGenerate(pcode_copy);
    cout << "generate mips OK\ncompile OK" << endl;
ERROR2:
    delete(handle_func_table);
    delete(pcode_generator);
    delete(symbol_table_tree);
    delete(handle_symbol_queue);
}

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Usage: ./compile_test /path_to_source_code" << endl;
    } else {
        //TestLexicalAnalysis(argv[1]);
        //TestGrammaAnalysis(argv[1]);
        //TestSemanticAnalysis(argv[1]);
        TestGenerate(argv[1]);
    }
    return 0;
}
