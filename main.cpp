#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>

#include "lexer/Lexer.h"
#include "parser/Parser.h"
#include "visitor/XMLGeneratorVisitor.h"
#include "visitor/SemanticAnalyserVisitor.h"
#include "visitor/InterpreterVisitor.h"

using namespace std;

void executeProgram(string program){
    try {
        Lexer lexer = Lexer(program);

        Parser parser = Parser(&lexer);
        ASTProgramNode *prog = parser.parse();

        SemanticAnalyserVisitor analyser = SemanticAnalyserVisitor();
        analyser.visit(prog);

        cout << endl;
        InterpreterVisitor interpreter = InterpreterVisitor();
        interpreter.visit(prog);
        cout << endl;
    }catch(const exception &e){
        cerr << e.what();
    }
}

int main() {

/*    ifstream inFile;
    inFile.open("../Program.txt");

    if (!inFile) {
        cerr << "Unable to open file Program.txt.";
        exit(1);
    }

    string line, program;
    while(getline(inFile,line)){
        program.append(line + "\n");
    }

//    cout << program << endl;

    try {
        Lexer lexer = Lexer(program);

        //    int i=0;
        //    while(i < lexer.program_tokens.size()){
        //        cout << "Lexeme: " << left << setw(10) << lexer.program_tokens[i].lexeme << " Token type: " << lexer.program_tokens[i].stringTokenType << endl;
        //        i++;
        //    }

        Parser parser = Parser(&lexer);
        ASTProgramNode *prog = parser.parse();

        XMLGeneratorVisitor xmlgen = XMLGeneratorVisitor();
        xmlgen.visit(prog);

        SemanticAnalyserVisitor analyser = SemanticAnalyserVisitor();
        analyser.visit(prog);

        cout << endl;
        InterpreterVisitor interpreter = InterpreterVisitor();
        interpreter.visit(prog);
    }catch(const exception &e){
        cerr << e.what();
    }

    inFile.close();
*/

    cout << "-------------" << endl;
    cout << "MiniLangI 1.0" << endl;
    cout << "Type #execute to run a MiniLang program, #help for more information or #quit to exit." << endl;
    cout << endl;

    string input;
    Scope* globalScope = new Scope();
    InterpreterScope* interpreterGlobalScope = new InterpreterScope();

    while(true){
        cout << "MLi> ";
        getline(cin, input);

        if(input == "#help"){
            cout << endl;
            cout << "--- Help ----" << endl;
            cout << "#load \"filename\"      Type #load followed by the name of your file to load variables\n"
                    "                      and functions declared in the file to memory." << endl;
            cout << endl;

        }

        else if(input.substr(0, 6) == "#load "){
            string filename = input.substr(6);
            filename.erase(filename.size()-1, filename.size());
            filename.erase(0, 1);

            ifstream inFile;
            string toOpen = "../" + filename;
            inFile.open(toOpen);

            if (!inFile) {
                cerr << "Unable to open file '" + filename + "'.";
                exit(1);
            }

            string line, program;
            while(getline(inFile,line)){
                program.append(line + "\n");
            }

            executeProgram(program);
            inFile.close();
        }

        else if(input.substr(0, 4) == "#st "){

        }

        else if(input == "#quit")
            break;

        else{
            string program = input;

            int openScopes = count(input.begin(), input.end(), '{');
            int closeScopes = count(input.begin(), input.end(), '}');

            while(openScopes > closeScopes){
                cout << "...  " ;
                getline(cin, input);

                openScopes += count(input.begin(), input.end(), '{');
                closeScopes += count(input.begin(), input.end(), '}');
                program += "\n";
                program += input;
            }

            program += "\n";

            try {
                Lexer lexer = Lexer(program);
                Parser parser = Parser(&lexer);
                ASTProgramNode *prog = parser.parse();

                SemanticAnalyserVisitor analyser = SemanticAnalyserVisitor(globalScope);
                analyser.visit(prog);

                cout << endl;
                InterpreterVisitor interpreter = InterpreterVisitor(interpreterGlobalScope);
                interpreter.visit(prog);
                cout << endl;
            }catch(const exception &e){
                cerr << e.what();
            }

            cout << endl;
        }
    }

    return 0;
}