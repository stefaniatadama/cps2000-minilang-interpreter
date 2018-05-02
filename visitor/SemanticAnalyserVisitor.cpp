//
// Created by stefaniatadama on 30/04/2018.
//

#include <iostream>
#include "SemanticAnalyserVisitor.h"
#include "../AST/ASTProgramNode.h"
#include "../AST/ASTDeclarationStatementNode.h"
#include "../AST/ASTFunctionDeclarationStatementNode.h"
#include "../AST/ASTAssignmentStatementNode.h"
#include "../AST/ASTReturnStatementNode.h"
#include "../AST/ASTBinaryExpressionNode.h"
#include "../AST/ASTIfStatementNode.h"
#include "../AST/ASTWhileStatementNode.h"
#include "../AST/ASTPrintStatementNode.h"
#include "../AST/ASTFunctionCallExpressionNode.h"

SemanticAnalyserVisitor::SemanticAnalyserVisitor(){
    scopes.push(globalScope);
}

string SemanticAnalyserVisitor::getStringType(TYPE type){
    if(type == REAL)
        return "real";
    else if(type == INT)
        return "int";
    else if(type == BOOL)
        return "bool";
    else if(type == STRING)
        return "string";
    else{
        throw runtime_error("Invalid type.");
    }
}

Scope* SemanticAnalyserVisitor::getCurrentScope(){
    return scopes.top();
}

bool SemanticAnalyserVisitor::returns(ASTNode* stmtNode){
    //If the current statement is a return, it returns
    if(dynamic_cast<ASTReturnStatementNode*>(stmtNode)){
        return true;
    }

    //If it's a block, check if any one of the statement returns, in which case it returns
    else if(ASTBlockStatementNode* newStmtNode = dynamic_cast<ASTBlockStatementNode*>(stmtNode)){
        for(int i=0; i<newStmtNode->statements.size(); i++){
            if(returns(newStmtNode->statements[i]))
                return true;
        }
    }

    //If it's an if statement, check if both if and else (if it exists) return, in which case it returns
    else if(ASTIfStatementNode* newStmtNode = dynamic_cast<ASTIfStatementNode*>(stmtNode)){
        if(newStmtNode->elseBody == nullptr)
            return(returns(newStmtNode->ifBody));
        else
            return(returns(newStmtNode->ifBody) && returns(newStmtNode->elseBody));
    }

    //Any other statements don't return
    else
        return false;
}

//DONE
void SemanticAnalyserVisitor::visit(ASTProgramNode* progNode){
    for(int i=0; i<progNode->programStatements.size(); i++)
        progNode->programStatements[i]->accept(this);
}

//DONE
void SemanticAnalyserVisitor::visit(ASTDeclarationStatementNode * declNode){
    //Get the innermost scope, which is the one at the top of the scope pointer stack
    Scope* currentScope = getCurrentScope();

    ASTIdentifierExpressionNode* idNode = declNode->variableIdentifier;

    //If identifier already exists and is a variable name
    if(currentScope->isVariable(idNode->identifierName)){
        throw runtime_error("Semantic error: redeclaration of variable '" + idNode->identifierName + "'.");
    }

    declNode->variableExpression->accept(this); //This call changes the value of global variable lastType

    if(lastType != idNode->identifierType){
        throw runtime_error("Semantic error: conflicting types - expected '" + getStringType(idNode->identifierType)
        + "' but expression is of type '" + getStringType(lastType) + "'.");
    }

    currentScope->addSymbol(declNode);
}

//DONE
void SemanticAnalyserVisitor::visit(ASTFunctionDeclarationStatementNode* funcDeclNode){
    /* When declaring a function, we need to check for the same signature in current scope and all scopes
     * below us in the stack */
    stack<Scope*> copyOfScopes = scopes;
    Scope* currentScope;

    //Pushing the function type
    functionTypes.push(funcDeclNode->functionReturnType);

    //Creating a vector with the signature of the function to be declared
    vector<TYPE> functionSignature;
    for(int i=0; i<funcDeclNode->formalParams.size(); i++){
        functionSignature.push_back(funcDeclNode->formalParams[i]->identifierType);
    }

    while(!copyOfScopes.empty()){
        currentScope = copyOfScopes.top();

        //If identifier exists and is a function name
        if(currentScope->isFunction(funcDeclNode->functionName)) {
            //If the function has the same signature
            if (currentScope->checkIfExists(funcDeclNode->functionName, functionSignature)) {
                throw runtime_error("Semantic error: redeclaration of function '" + funcDeclNode->functionName +
                                    "'.");
            }
        }
        copyOfScopes.pop();
    }

    //If we got to here, function signature does not exist so we can declare the given function.
    for(int i=0; i<funcDeclNode->formalParams.size(); i++){
        currentParams.push_back(pair<string, TYPE>(funcDeclNode->formalParams[i]->identifierName, functionSignature[i]));
    }

    if(!returns(funcDeclNode->functionBody))
        throw runtime_error("Semantic error: function '" + funcDeclNode->functionName + "' does not always return.");

    funcDeclNode->functionBody->accept(this);

    functionTypes.pop();


//    //Add parameters to the new scope
//    for(int i=0; i<funcDeclNode->formalParams.size(); i++){
//        Symbol* sym = new Symbol(funcDeclNode->formalParams[i]->identifierType, funcDeclNode->formalParams[i]);
//        getCurrentScope()->addSymbol(funcDeclNode->formalParams[i]->identifierName, sym);
//    }
//
//    for(int i=0; i<funcDeclNode->functionBody->statements.size(); i++){
//        //Find the return statement to check its type
//        if(ASTReturnStatementNode* r = dynamic_cast<ASTReturnStatementNode*>(funcDeclNode->functionBody->statements[i])){
//            r->expressionToReturn->accept(this);
//            if(lastType == funcDeclNode->functionReturnType){
//                currentScope->addSymbol(funcDeclNode);
//                return;
//            }
//
//            else
//                throw runtime_error("Semantic error: function's return type is '" + getStringType(funcDeclNode->
//                        functionReturnType)  + "' but it is returning a different type.");
//        }
//    }
}

//DONE
void SemanticAnalyserVisitor::visit(ASTBlockStatementNode* blockNode){
    //Create a new scope every time we meet a new block
    Scope* scope = new Scope();
    scopes.push(scope);

    ASTExpressionNode* idNode = nullptr;

    //If we are in a function block, we add to the current scope the formal parameters
    Symbol* sym;
    if(!currentParams.empty()){
        for(int i=0; i<currentParams.size(); i++){
            sym = new Symbol(currentParams[i].second, idNode);
            scope->addSymbol(currentParams[i].first, sym);
        }
    }

    currentParams.clear();

    //Visit every statement in block
    for(int i=0; i<blockNode->statements.size(); i++){
        blockNode->statements[i]->accept(this);
    }

    scopes.pop();
    delete sym;
    delete scope;
}

//DONE
void SemanticAnalyserVisitor::visit(ASTAssignmentStatementNode* asmtNode){
    //Going through all scopes in stack until we find the variable we are assigning to
    stack<Scope*> copyOfScopes = scopes;
    Scope* currentScope;

    string id = asmtNode->identifier->identifierName;

    bool exists = false;
    bool correctType = false;

    while(!copyOfScopes.empty()){
        currentScope = copyOfScopes.top();

        //If identifier we are assigning to exists in the current scope and is a variable name
        if(currentScope->isVariable(id)){
            exists = true;

            asmtNode->assignmentExpression->accept(this);
            if(lastType == currentScope->getType(id)){
                correctType = true;
                currentScope->editSymbol(id, lastType, asmtNode->assignmentExpression);
            }
        }
        copyOfScopes.pop();
    }

    if(!exists)
        throw runtime_error("Semantic error: identifier '" + id + "' has not been declared.");
    if(!correctType)
        throw runtime_error("Semantic error: conflicting types - expected '" + getStringType(currentScope->getType(id)) +
                            "' but expression is of type '" + getStringType(lastType) + "'.");
}

//DONE
void SemanticAnalyserVisitor::visit(ASTReturnStatementNode* retNode){
    //If we are in a function block
    if(!functionTypes.empty()){
        retNode->expressionToReturn->accept(this);
        if(lastType != functionTypes.top())
            throw runtime_error("Semantic error: function returns '" + getStringType(functionTypes.top()) + "' but return type is '"
                                + getStringType(lastType));
    }

    else {
        //Visits the expression to return, which in turn changes the lastType global variable
        retNode->expressionToReturn->accept(this);
    }
}

void SemanticAnalyserVisitor::visit(ASTRealLiteralExpressionNode* realNode){
    lastType = REAL;
}

void SemanticAnalyserVisitor::visit(ASTIntLiteralExpressionNode* intNode){
    lastType = INT;
}

void SemanticAnalyserVisitor::visit(ASTBoolLiteralExpressionNode* boolNode){
    lastType = BOOL;
}

void SemanticAnalyserVisitor::visit(ASTStringLiteralExpressionNode* stringNode){
    lastType = STRING;
}

void SemanticAnalyserVisitor::visit(ASTBinaryExpressionNode* binExpNode){
    //Checking types of left and right operands match
    binExpNode->left->accept(this);
    TYPE left_type = lastType;

    binExpNode->right->accept(this);

    if(lastType != left_type){
        throw runtime_error("Semantic error: binary expression where left node has type '" + getStringType(left_type)
                            + "' but right node has type '" + getStringType(lastType) + "'.");
    }

    //If both have the same type, lastType is now set to their same type
}

//DONE
void SemanticAnalyserVisitor::visit(ASTIdentifierExpressionNode* idNode){
    //Going through all scopes in stack until we find the variable
    stack<Scope*> copyOfScopes = scopes;
    Scope* currentScope;

    string id = idNode->identifierName;

    bool exists = false;

    while(!copyOfScopes.empty()){
        currentScope = copyOfScopes.top();

        if(currentScope->isVariable(id)){
            exists = true;
            break;
        }

        copyOfScopes.pop();
    }

    if(!exists)
        throw runtime_error("Semantic error: identifier '" + id + "' has not been declared.");

    lastType = getCurrentScope()->getType(idNode->identifierName);
}

//DONE
void SemanticAnalyserVisitor::visit(ASTIfStatementNode* ifNode){
    ifNode->conditionExpression->accept(this);

    if(lastType != BOOL){
        throw runtime_error("Semantic error: if condition is not of type 'bool'.");
    }
}

//DONE
void SemanticAnalyserVisitor::visit(ASTWhileStatementNode* whileNode){
    whileNode->conditionExpression->accept(this);

    if(lastType != BOOL){
        throw runtime_error("Semantic error: while condition is not of type 'bool'.");
    }
}

//DONE
void SemanticAnalyserVisitor::visit(ASTPrintStatementNode* printNode){
    printNode->expressionToPrint->accept(this);
}

void SemanticAnalyserVisitor::visit(ASTUnaryExpressionNode* unaryNode){

}

void SemanticAnalyserVisitor::visit(ASTFunctionCallExpressionNode* funcCallNode){
    stack<Scope*> copyOfScopes = scopes;
    Scope* currentScope;

    string funcName = funcCallNode->functionName;
    vector<ASTExpressionNode*> funcCallArgs = funcCallNode->argumentList;

    bool exists = false;
    bool validArgs = false;

    vector<TYPE> argsType;
    for(int i=0; i<funcCallNode->argumentList.size(); i++){
        funcCallNode->argumentList[i]->accept(this);
        argsType.push_back(lastType);
    }

    while(!copyOfScopes.empty()){
        currentScope = copyOfScopes.top();

        //If identifier exists and is a function name
        if(currentScope->isFunction(funcName)){
            exists = true;

            if(currentScope->checkIfExists(funcName, argsType)) {
                validArgs = true;
                //TODO fix signature
                lastType = currentScope->getReturnType(funcCallNode->functionName);
            }
        }
        copyOfScopes.pop();
    }

    if(!exists)
        throw runtime_error("Semantic error: function '" + funcName + "' does not exist.");
    if(!validArgs)
        throw runtime_error("Semantic error: function '" + funcName + "' has different parameters.");

}