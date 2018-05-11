#include <iostream>
#include "Scope.h"
#include "../AST/ASTDeclarationStatementNode.h"
#include "../AST/ASTFunctionDeclarationStatementNode.h"

bool Scope::isVariable(string key){
    auto range = symbolTable.equal_range(key);

    for(auto i = range.first; i != range.second; ++i){
        if(i->second->id == VARIABLE)
            return true;
    }

    return false;
}

bool Scope::isFunction(string key){
    auto range = symbolTable.equal_range(key);

    for(auto i = range.first; i!= range.second; ++i){
        if(i->second->id == FUNCTION)
            return true;
    }

    return false;
}

bool Scope::checkIfExists(string funcName, vector<TYPE> paramsTypes){
    auto range = symbolTable.equal_range(funcName);

    vector<TYPE> foundParams;

    /* For every function found with the name funcName, place its types into a vector and
     * compare them to the arguments being passed to the function */
    for(auto it = range.first; it != range.second; ++it){

        if(it->second->id == FUNCTION){

            for(int i=0; i<it->second->params.size(); i++){
                foundParams.push_back(it->second->params[i]->identifierType);
            }
        }

        if(paramsTypes == foundParams){
            return true;
        }

        //Clearing foundParams vector for next use
        foundParams.clear();
    }

    return false;
}

TYPE Scope::getType(string key){
    //We can use find() here because only one variable can have the same name
    auto entry = symbolTable.find(key);
    return entry->second->type;
}

TYPE Scope::getReturnType(string funcName){
    auto entry = symbolTable.find(funcName);
    return entry->second->type;
}

void Scope::addSymbol(ASTDeclarationStatementNode* declarationNode){
    string key = declarationNode->variableIdentifier->identifierName;
    Symbol* sym = new Symbol(declarationNode->variableIdentifier->identifierType, declarationNode->variableExpression);

    symbolTable.insert(pair<string, Symbol*>(key, sym));
}

/* When declaring a function, we store its formal parameters with it to allow for
 * function overloading */
void Scope::addSymbol(ASTFunctionDeclarationStatementNode* functionDeclarationNode){
    string key = functionDeclarationNode->functionName;
    Symbol* sym = new Symbol(functionDeclarationNode->functionReturnType, functionDeclarationNode->formalParams);

    symbolTable.insert(pair<string, Symbol*>(key, sym));
}

void Scope::addSymbol(string key, Symbol* sym){
    symbolTable.insert(pair<string, Symbol*>(key, sym));
}


void Scope::editSymbol(string key, TYPE type, ASTExpressionNode* newSymbol){
    deleteSymbol(key);

    Symbol* sym = new Symbol(type, newSymbol);
    symbolTable.insert(pair<string, Symbol*>(key, sym));
}

void Scope::deleteSymbol(string key){
    symbolTable.erase(key);
}