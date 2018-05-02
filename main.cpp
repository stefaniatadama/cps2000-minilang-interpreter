#include <iostream>
#include <fstream>
#include <iomanip>

#include "lexer/Lexer.h"
#include "parser/Parser.h"
#include "visitor/XMLGeneratorVisitor.h"
#include "visitor/SemanticAnalyserVisitor.h"

using namespace std;

int main() {

    ifstream inFile;
    inFile.open("../Program.txt");

    if (!inFile) {
        cerr << "Unable to open file Program.txt";
        exit(1);
    }

    string line, program;
    while(getline(inFile,line)){
        program.append(line + "\n");
    }

    cout << program << endl;

    Lexer lexer = Lexer(program);

    int i=0;
    while(i < lexer.program_tokens.size()){
        cout << "Lexeme: " << left << setw(10) << lexer.program_tokens[i].lexeme << " Token type: " << lexer.program_tokens[i].stringTokenType << endl;
        i++;
    }

    Parser parser = Parser(&lexer);
    ASTProgramNode* prog = parser.parse();

    XMLGeneratorVisitor xmlgen = XMLGeneratorVisitor();
    xmlgen.visit(prog);

//    SemanticAnalyserVisitor analyser = SemanticAnalyserVisitor();
//    analyser.visit(prog);

    inFile.close();

    return 0;
}