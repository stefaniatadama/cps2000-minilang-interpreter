//
// Created by stefaniatadama on 30/04/2018.
//

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
    //pair<MAPIterator, MAPIterator> range;
    auto range = symbolTable.equal_range(key);

    for(auto i = range.first; i!= range.second; ++i){
        if(i->second->id == FUNCTION)
            return true;
    }

    return false;
}

bool Scope::checkIfExists(string funcName, vector<TYPE> paramsTypes){
    //pair<MAPIterator, MAPIterator> range;
    auto range = symbolTable.equal_range(funcName);

    vector<TYPE> foundParams;

    /* Creating a vector of types of signatures of the functions found in symbol table
     * and comparing them to those of the function being passed */
    for(auto it = range.first; it!= range.second; ++it){
        if(it->second->id == FUNCTION){

            for(int i=0; i<it->second->params.size(); i++){
                foundParams.push_back(it->second->params[i]->identifierType);
            }
        }

        if(paramsTypes == foundParams){
            return true;
        }
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