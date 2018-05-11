#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <cstring>

#include "lexer/Lexer.h"
#include "parser/Parser.h"
#include "visitor/XMLGeneratorVisitor.h"
#include "visitor/SemanticAnalyserVisitor.h"
#include "visitor/InterpreterVisitor.h"
#include "AST/ASTProgramNode.h"

using namespace std;

string getStringType(TYPE t){
    if(t == REAL)
        return "real";
    else if(t == INT)
        return "int";
    else if(t == BOOL)
        return "bool";
    else if(t == STRING)
        return "string";
}

void printVarValue(TYPE t, VarValue v){
    if(t == REAL)
        cout << v.r << endl;
    else if(t == INT)
        cout << v.i << endl;
    else if(t == BOOL)
        cout << (v.b ? "true" : "false") << endl;
    else if(t == STRING)
        cout << v.s << endl;
    else
        cout << "Error.";
}

int main() {
    cout << "-------------" << endl;
    cout << "MiniLangI 1.0" << endl;
    cout << "Type #load to load a program in MiniLang, #help for more information or #quit\n"
            "to exit." << endl;
    cout << endl;

    string input;
    Scope* globalScope = new Scope();
    InterpreterScope* interpreterGlobalScope = new InterpreterScope();

    while(true){
        cout << "MLi> ";
        getline(cin, input);

        if(input == "#help"){
            cout << "\n----Help-----\n" << endl;
            cout << "#load \"filename\"      Type #load followed by the name of your file to load\n"
                    "                      variables and functions declared in it to memory.\n" << endl;
            cout << "#st                   Displays functions and variables that have been\n"
                    "                      already declared that are stored in the symbol table.\n" << endl;
            cout << "#quit                 Exits MiniLangI.\n" << endl;
            cout << "You can also type any valid statement or expression in MiniLang to have it\n"
                    "evaluated.\n" << endl;
        }

        else if(input.substr(0, 6) == "#load "){
            string filename = input.substr(6);
            filename.erase(filename.size()-1, filename.size());
            filename.erase(0, 1);

            ifstream inFile;
            string toOpen = filename;
            inFile.open(toOpen);

            if(!inFile) {
                cerr << "Unable to open file '" + filename + "'." << endl;
            }

            string line, program;
            while(getline(inFile,line)){
                program.append(line + "\n");
            }

            /* We use temporary global scopes so that if the program is invalid, no variables or
             * functions from it are put into the global scopes */
            bool correctProg = true;
            Scope tempGlobalScope;
            tempGlobalScope = *globalScope;

            try{
                Lexer lexer = Lexer(program);

                Parser parser = Parser(&lexer);
                ASTProgramNode* prog = parser.parse();

                XMLGeneratorVisitor xmlgen = XMLGeneratorVisitor();
                xmlgen.visit(prog);

                SemanticAnalyserVisitor analyser = SemanticAnalyserVisitor(&tempGlobalScope);
                analyser.visit(prog);
            }catch(const exception &e){
                correctProg = false;
                cerr << e.what() << endl;
            }

            if(correctProg){
                Lexer lexer = Lexer(program);

                Parser parser = Parser(&lexer);
                ASTProgramNode* prog = parser.parse();

                SemanticAnalyserVisitor analyser = SemanticAnalyserVisitor(globalScope);
                analyser.visit(prog);

                InterpreterVisitor interpreter = InterpreterVisitor(interpreterGlobalScope);
                interpreter.visit(prog);
            }

            inFile.close();
        }

        else if(input == "#st"){
            cout << "The functions and variables shown below are currently stored in the symbol\ntable." << endl;
            cout << endl;

            cout << "--Variables--" << endl;
            //Print variables from global scope
            for(auto it = interpreterGlobalScope->variables.begin(); it != interpreterGlobalScope->variables.end(); ++it){
                cout << getStringType(it->second.first) << " " << it->first << " = ";
                TYPE t = it->second.first;
                printVarValue(t, it->second.second);
            }
            cout << endl;

            cout << "--Functions--" << endl;
            //Print functions from globalScope
            for(auto it = globalScope->symbolTable.begin(); it != globalScope->symbolTable.end(); ++it){
                if(globalScope->isFunction(it->first)) {
                    cout << it->first << "(";

                    for (int i = 0; i < it->second->params.size(); i++) {
                        cout << getStringType(it->second->params[i]->identifierType);

                        if (i + 1 < it->second->params.size())
                            cout << ",";
                    }

                    cout << ")" << endl;
                }
            }

            cout << endl;
        }

        else if(input == "#quit")
            break;

        else if(input.substr(0,1) == " "){
            cout << "Indentation error: unexpected indent." << endl;
        }

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

            //Catches any errors by the lexer, parser or visitors
            try {
                Lexer lexer = Lexer(program);

                Parser parser = Parser(&lexer);

                ASTProgramNode* prog;

                bool expression = false;

                //If the parser throws an error, check whether we can parse it as an expression
                try{
                    prog = parser.parse();
                }catch(const exception &e){

                    //If it's not an expression, throw initial error thrown by parser
                    try {
                        expression = true;

                        /* If it's an expression like 1+1; we remove the delimeter ; and try to parse it
                         * as an expression */
                        if (input[input.size() - 1] == ';')
                            input.erase(input.size() - 1, input.size());

                        input += "\n";

                        Lexer l = Lexer(input);
                        Parser p = Parser(&l);

                        vector<ASTNode *> v;
                        v.push_back(p.parseExpression());

                        prog = new ASTProgramNode(v);
                    }catch(const exception &expressionErr){
                        throw runtime_error(e.what());
                    }
                }

                Scope tempGlobalScope;
                tempGlobalScope = *globalScope;
                bool correctProg = true;

                try {
                    SemanticAnalyserVisitor analyser = SemanticAnalyserVisitor(&tempGlobalScope);
                    analyser.visit(prog);
                }catch(const exception &e){
                    correctProg = false;
                    cerr << e.what() << endl;
                }

                if(correctProg){
                    SemanticAnalyserVisitor analyser = SemanticAnalyserVisitor(globalScope);
                    analyser.visit(prog);

                    InterpreterVisitor interpreter = InterpreterVisitor(interpreterGlobalScope);
                    interpreter.visit(prog);

                    if(expression){
                        TYPE last = interpreter.lastType;
                        printVarValue(last, interpreter.lastValue);
                    }
                }

            }catch(const exception &e){
                cerr << e.what() << endl;
            }
        }
    }

    return 0;
}