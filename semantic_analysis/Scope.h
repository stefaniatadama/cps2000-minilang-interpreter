//
// Created by stefaniatadama on 30/04/2018.
//

#ifndef ASSIGNMENT_SCOPE_H
#define ASSIGNMENT_SCOPE_H

#include <map>
#include "Symbol.h"

using namespace std;

class Scope {

    public:
        //Symbol table with key string and value Symbol pointer
        multimap<string, Symbol*> symbolTable;
//        //Defining a new name for an iterator of the multimap
//        typedef multimap<string, Symbol*> MAPIterator;
        //Checks if there is a variable with the given name in symbol table
        bool isVariable(string);
        //Checks if there is a function with the given name in symbol table
        bool isFunction(string);
        //Check if function signature exists in symbol table
        bool checkIfExists(string, vector<TYPE>);



//        //Check if given string is a variable or a function
//        IDENTIFIER getIfVarOrFunc(string);


        //vector<ASTIdentifierExpressionNode*> getFunctionParams(string);
        //Get type of variable
        TYPE getType(string);
        //Get return type of function
        TYPE getReturnType(string);
        void addSymbol(ASTDeclarationStatementNode*);
        void addSymbol(ASTFunctionDeclarationStatementNode*);
        void addSymbol(string, Symbol*);
        //Change value of some variable
        void editSymbol(string, TYPE, ASTExpressionNode*);
        void deleteSymbol(string);


};


#endif //ASSIGNMENT_SCOPE_H
