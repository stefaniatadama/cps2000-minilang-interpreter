//
// Created by stefaniatadama on 04/05/2018.
//

#include "InterpreterScope.h"
#include "../AST/ASTDeclarationStatementNode.h"

void InterpreterScope::setVariable(string name, int val){
    varValue var;
    var.i = val;

    variables[name] = pair<TYPE, varValue>(INT, var);
}

void InterpreterScope::setVariable(string name, float val){
    varValue var;
    var.r = val;

    variables[name] = pair<TYPE, varValue>(REAL, var);
}

void InterpreterScope::setVariable(string name, bool val){
    varValue var;
    var.b = val;

    variables[name] = pair<TYPE, varValue>(BOOL, var);
}

void InterpreterScope::setVariable(string name, string val){
    varValue var;
    var.s = val;

    variables[name] = pair<TYPE, varValue>(STRING, var);
}

void InterpreterScope::addFunction(string name, vector<TYPE> signature, ASTFunctionDeclarationStatementNode* funcDeclNode){
    functions.insert(make_pair(name, make_pair(signature, funcDeclNode)));
}

ASTFunctionDeclarationStatementNode* InterpreterScope::getFunction(string name, vector<TYPE> passedParams){
    auto range = functions.equal_range(name);

    vector<TYPE> foundParams;

    /* For every function found with the name funcName, place its types into a vector and
     * compare them to the arguments being passed to the function */
    for(auto it = range.first; it != range.second; ++it){

        for(int i=0; i<it->second.first.size(); i++){
            foundParams.push_back(it->second.first[i]);
        }

        if(passedParams == foundParams){
            return it->second.second;
        }

        //Clearing foundParams vector for next use
        foundParams.clear();
    }

    //If function not found
    return nullptr;
}

bool InterpreterScope::findVariable(string name){
    return(variables.find(name) != variables.end());
}

TYPE InterpreterScope::getVariableType(string name){
    return variables.find(name)->second.first;
}

varValue InterpreterScope::getVariableValue(string name){
    return(variables.find(name)->second.second);
}