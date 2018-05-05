//
// Created by stefaniatadama on 04/05/2018.
//

#include <climits>
#include <cfloat>
#include <iostream>
#include "InterpreterVisitor.h"
#include "../AST/ASTProgramNode.h"
#include "../AST/ASTDeclarationStatementNode.h"
#include "../AST/ASTFunctionCallExpressionNode.h"
#include "../AST/ASTFunctionDeclarationStatementNode.h"
#include "../AST/ASTAssignmentStatementNode.h"
#include "../AST/ASTBinaryExpressionNode.h"
#include "../AST/ASTIntLiteralExpressionNode.h"
#include "../AST/ASTRealLiteralExpressionNode.h"
#include "../AST/ASTBoolLiteralExpressionNode.h"
#include "../AST/ASTStringLiteralExpressionNode.h"
#include "../AST/ASTUnaryExpressionNode.h"
#include "../AST/ASTIfStatementNode.h"
#include "../AST/ASTWhileStatementNode.h"
#include "../AST/ASTReturnStatementNode.h"
#include "../AST/ASTPrintStatementNode.h"

InterpreterVisitor::InterpreterVisitor(){
    InterpreterScope* globalScope = new InterpreterScope();
    scopes.push(globalScope);
}

InterpreterScope* InterpreterVisitor::getCurrentScope(){
    return scopes.top();
}

void InterpreterVisitor::visit(ASTProgramNode* progNode) {
    for(int i=0; i<progNode->programStatements.size(); i++){
        progNode->programStatements[i]->accept(this);
    }
}

void InterpreterVisitor::visit(ASTDeclarationStatementNode* declNode){
    InterpreterScope* currentScope = getCurrentScope();

    declNode->variableExpression->accept(this); //This will change global variable lastValue

    switch(declNode->variableIdentifier->identifierType){
        case(INT):
            currentScope->setVariable(declNode->variableIdentifier->identifierName, lastValue.i);

        case(REAL):
            currentScope->setVariable(declNode->variableIdentifier->identifierName, lastValue.r);

        case(BOOL):
            currentScope->setVariable(declNode->variableIdentifier->identifierName, lastValue.b);

        case(STRING):
            currentScope->setVariable(declNode->variableIdentifier->identifierName, lastValue.s);
    }
}

void InterpreterVisitor::visit(ASTFunctionDeclarationStatementNode* funcDeclNode){
    InterpreterScope* currentScope = getCurrentScope();

    vector<TYPE> signature;
    for(int i=0; i<funcDeclNode->formalParams.size(); i++){
        signature.push_back(funcDeclNode->formalParams[i]->identifierType);
        //currentFormalParams.push_back(tuple<string, TYPE>(funcDeclNode->formalParams[i]->identifierName,
                                                          //funcDeclNode->formalParams[i]->identifierType));
    }

    currentScope->addFunction(funcDeclNode->functionName, signature, funcDeclNode);

    //TODO le hux? funcDeclNode->functionBody->accept(this);
}

void InterpreterVisitor::visit(ASTFunctionCallExpressionNode* funcCallNode){
    stack<InterpreterScope*> copyOfScopes = scopes;
    InterpreterScope* currentScope;

    vector<TYPE> signature;

    for(int i=0; i<funcCallNode->argumentList.size(); i++){
        funcCallNode->argumentList[i]->accept(this); //This will change the value of lastType
        signature.push_back(lastType);
    }

    ASTFunctionDeclarationStatementNode* funcDeclNode;

    while(!copyOfScopes.empty()){
        currentScope = copyOfScopes.top();

        //If function is found
        if(currentScope->getFunction(funcCallNode->functionName, signature) != nullptr){
            funcDeclNode = currentScope->getFunction(funcCallNode->functionName, signature);

            for(int j=0; j<funcCallNode->argumentList.size(); j++){
                funcCallNode->argumentList[j]->accept(this); //This will change the value of lastValue

                currentParams.push_back(tuple<string, TYPE, varValue>(funcDeclNode->formalParams[j]->identifierName,
                                                                      funcDeclNode->formalParams[j]->identifierType,
                                                                      lastValue));
            }
        }
        copyOfScopes.pop();
    }

    //funcDeclNode will be instantiated otherwise the program wouldn't have passed through semantic analysis
    funcDeclNode->functionBody->accept(this);

    lastType = funcDeclNode->functionReturnType;
}

void InterpreterVisitor::visit(ASTBlockStatementNode* blockNode){
    InterpreterScope* newScope = new InterpreterScope();
    scopes.push(newScope);

    //If we're in a function call: add value of arguments passed in function call to current scope
    if(!currentParams.empty()){
        for(int i=0; i<currentParams.size(); i++){
            switch(get<1>(currentParams[i])){
                case(INT):
                    newScope->setVariable(get<0>(currentParams[i]), get<2>(currentParams[i]).i);
                    break;

                case(REAL):
                    newScope->setVariable(get<0>(currentParams[i]), get<2>(currentParams[i]).r);
                    break;

                case(BOOL):
                    newScope->setVariable(get<0>(currentParams[i]), get<2>(currentParams[i]).b);
                    break;

                case(STRING):
                    newScope->setVariable(get<0>(currentParams[i]), get<2>(currentParams[i]).s);
                    break;
            }
        }
        currentParams.clear();
    }

//    //If we're in a function declaration: add formal parameters and their types to current scope
//    if(!currentFormalParams.empty()){
//        for(int i=0; i<currentFormalParams.size(); i++){
//            switch(get<1>(currentFormalParams[i])){
//                case(INT):
//                    newScope->setVariable(get<0>(currentFormalParams[i]), INT_MAX);
//                    break;
//
//                case(REAL):
//                    newScope->setVariable(get<0>(currentFormalParams[i]), FLT_MAX);
//                    break;
//
//                case(BOOL):
//                    newScope->setVariable(get<0>(currentFormalParams[i]), false);
//                    break;
//
//                case(STRING):
//                    newScope->setVariable(get<0>(currentFormalParams[i]), "");
//                    break;
//            }
//        }
//        currentFormalParams.clear();
//    }

    for(int i=0; i<blockNode->statements.size(); i++){
        blockNode->statements[i]->accept(this);
    }

    scopes.pop();
    delete newScope;
}

void InterpreterVisitor::visit(ASTAssignmentStatementNode* stmtNode){
    stack<InterpreterScope*> copyOfScopes = scopes;
    InterpreterScope* currentScope;

    stmtNode->assignmentExpression->accept(this);

    while(!copyOfScopes.empty()){
        currentScope = copyOfScopes.top();

        if(currentScope->findVariable(stmtNode->identifier->identifierName)) {

            switch(currentScope->getVariableType(stmtNode->identifier->identifierName)) {
                case (INT):
                    currentScope->setVariable(stmtNode->identifier->identifierName, lastValue.i);

                case (REAL):
                    currentScope->setVariable(stmtNode->identifier->identifierName, lastValue.r);

                case (BOOL):
                    currentScope->setVariable(stmtNode->identifier->identifierName, lastValue.b);

                case (STRING):
                    currentScope->setVariable(stmtNode->identifier->identifierName, lastValue.s);
            }
        }

        copyOfScopes.pop();
    }
}

void InterpreterVisitor::visit(ASTBinaryExpressionNode* binExprNode){
    binExprNode->left->accept(this);
    TYPE opType = lastType;
    varValue leftVal = lastValue;

    binExprNode->right->accept(this);
    varValue rightVal = lastValue;

    if(binExprNode->op == "+"){
        if(opType == INT){
            lastValue.i = leftVal.i + rightVal.i;
            lastType = INT;
        }

        else if(opType == REAL){
            lastValue.r = leftVal.r + rightVal.r;
            lastType = REAL;
        }

        else if(opType == STRING){
            lastValue.s = leftVal.s + rightVal.s;
            lastType = STRING;
        }
    }

    else if(binExprNode->op == "-"){
        if(opType == INT){
            lastValue.i = leftVal.i - rightVal.i;
            lastType = INT;
        }

        else if(opType == REAL){
            lastValue.r = leftVal.r - rightVal.r;
            lastType = REAL;
        }
    }

    else if(binExprNode->op == "*"){
        if(opType == INT){
            lastValue.i = leftVal.i * rightVal.i;
            lastType = INT;
        }

        else if(opType == REAL){
            lastValue.r = leftVal.r * rightVal.r;
            lastType = REAL;
        }
    }

    else if(binExprNode->op == "/"){
        if(opType == INT){
            lastValue.i = (int)(leftVal.i / rightVal.i);
            lastType = INT;
        }

        else if(opType == REAL){
            lastValue.r = leftVal.r / rightVal.r;
            lastType = REAL;
        }
    }

    else if(binExprNode->op == "<"){
        if(opType == INT){
            lastValue.b = leftVal.i < rightVal.i;
            lastType = BOOL;
        }

        else if(opType == REAL){
            lastValue.r = leftVal.r < rightVal.r;
            lastType = BOOL;
        }
    }

    else if(binExprNode->op == ">"){
        if(opType == INT){
            lastValue.b = leftVal.i > rightVal.i;
            lastType = BOOL;
        }

        else if(opType == REAL){
            lastValue.r = leftVal.r > rightVal.r;
            lastType = BOOL;
        }
    }

    else if(binExprNode->op == "<="){
        if(opType == INT){
            lastValue.b = leftVal.i <= rightVal.i;
            lastType = BOOL;
        }

        else if(opType == REAL){
            lastValue.r = leftVal.r <= rightVal.r;
            lastType = BOOL;
        }
    }

    else if(binExprNode->op == ">="){
        if(opType == INT){
            lastValue.b = leftVal.i >= rightVal.i;
            lastType = BOOL;
        }

        else if(opType == REAL){
            lastValue.r = leftVal.r >= rightVal.r;
            lastType = BOOL;
        }
    }

    else if(binExprNode->op == "=="){
        if(opType == INT){
            lastValue.b = leftVal.i == rightVal.i;
            lastType = BOOL;
        }

        else if(opType == REAL){
            lastValue.b = leftVal.r == rightVal.r;
            lastType = BOOL;
        }

        else if(opType == BOOL){
            lastValue.b = leftVal.b == rightVal.b;
            lastType = BOOL;
        }

        else if(opType == STRING){
            lastValue.b = leftVal.s == rightVal.s;
            lastType = BOOL;
        }
    }

    else if(binExprNode->op == "!="){
        if(opType == INT){
            lastValue.b = leftVal.i != rightVal.i;
            lastType = BOOL;
        }

        else if(opType == REAL){
            lastValue.b = leftVal.r != rightVal.r;
            lastType = BOOL;
        }

        else if(opType == BOOL){
            lastValue.b = leftVal.b != rightVal.b;
            lastType = BOOL;
        }

        else if(opType == STRING){
            lastValue.b = leftVal.s != rightVal.s;
            lastType = BOOL;
        }
    }

    else if(binExprNode->op == "and"){
        lastValue.b = leftVal.b && rightVal.b;
        lastType = BOOL;
    }

    else if(binExprNode->op == "or"){
        lastValue.b = leftVal.b || rightVal.r;
        lastType = BOOL;
    }
}

void InterpreterVisitor::visit(ASTIntLiteralExpressionNode* intNode){
    lastValue.i = intNode->value;
    lastType = INT;
}

void InterpreterVisitor::visit(ASTRealLiteralExpressionNode* realNode){
    lastValue.r = realNode->value;
    lastType = REAL;
}

void InterpreterVisitor::visit(ASTBoolLiteralExpressionNode* boolNode){
    lastValue.b = boolNode->value;
    lastType = BOOL;
}

void InterpreterVisitor::visit(ASTStringLiteralExpressionNode* stringNode){
    lastValue.s = stringNode->value;
    lastType = STRING;
}

void InterpreterVisitor::visit(ASTIdentifierExpressionNode* idNode){
    stack<InterpreterScope*> copyOfScopes = scopes;
    InterpreterScope* currentScope;

    while(!copyOfScopes.empty()){
        currentScope = copyOfScopes.top();

        if(currentScope->findVariable(idNode->identifierName)) {
            lastValue = currentScope->getVariableValue(idNode->identifierName);
            lastType = currentScope->getVariableType(idNode->identifierName);
        }

        copyOfScopes.pop();
    }
}

void InterpreterVisitor::visit(ASTUnaryExpressionNode* exprNode){
    exprNode->accept(this);

    if(exprNode->op == "-"){
        if(lastType == REAL){
            exprNode->expressionNode->accept(this);
            lastValue.r = - lastValue.r;
            //lastType remains the same
        }

        else if(lastType == INT){
            exprNode->expressionNode->accept(this);
            lastValue.i = - lastValue.i;
        }
    }

    else if(exprNode->op == "not"){
        exprNode->expressionNode->accept(this);
        lastValue.b = !lastValue.b;
        lastType = BOOL;
    }
}

void InterpreterVisitor::visit(ASTIfStatementNode* ifNode){
    ifNode->conditionExpression->accept(this);

    if(lastValue.b){
        for(int i=0; i<ifNode->ifBody->statements.size(); i++)
            ifNode->ifBody->statements[i]->accept(this);
    }

    else if(ifNode->elseBody != nullptr){
        for(int i=0; i<ifNode->elseBody->statements.size(); i++)
            ifNode->elseBody->statements[i]->accept(this);
    }
}

void InterpreterVisitor::visit(ASTWhileStatementNode* whileNode){
    whileNode->conditionExpression->accept(this);

    while(lastValue.b){
        for(int i=0; i<whileNode->whileBody->statements.size(); i++)
            whileNode->whileBody->statements[i]->accept(this);

        whileNode->conditionExpression->accept(this);
    }
}

void InterpreterVisitor::visit(ASTReturnStatementNode* retNode){
    retNode->expressionToReturn->accept(this);
    //TODO actually return the value???
}

void InterpreterVisitor::visit(ASTPrintStatementNode* printNode){
    printNode->expressionToPrint->accept(this);

    switch(lastType){
        case (REAL): cout << lastValue.r << endl; break;
        case (INT): cout << lastValue.i << endl; break;
        case (BOOL): cout << lastValue.b << endl; break;
        case (STRING): cout << lastValue.s << endl; break;
    }
}