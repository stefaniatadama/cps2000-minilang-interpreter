//
// Created by stefaniatadama on 04/05/2018.
//

#ifndef ASSIGNMENT_INTERPRETERSCOPE_H
#define ASSIGNMENT_INTERPRETERSCOPE_H

#include <map>
#include <vector>
#include "../AST/ASTNode.h"

using namespace std;

struct varValue{
    int i;
    float r;
    bool b;
    string s;
};

class InterpreterScope {

    public:
        //Map for variables
        map<string, pair<TYPE, varValue>> variables;
        //Multimap for functions
        multimap<string, pair<vector<TYPE>, ASTFunctionDeclarationStatementNode*>> functions;

        void setVariable(string, int);
        void setVariable(string, float);
        void setVariable(string, bool);
        void setVariable(string, string);

        void addFunction(string, vector<TYPE>, ASTFunctionDeclarationStatementNode*);

        ASTFunctionDeclarationStatementNode* getFunction(string, vector<TYPE>);
        bool findVariable(string);
        TYPE getVariableType(string);
        varValue getVariableValue(string);
};


#endif //ASSIGNMENT_INTERPRETERSCOPE_H
