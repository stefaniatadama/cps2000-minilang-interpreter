//
// Created by stefaniatadama on 23/04/2018.
//

#include "ASTDeclarationStatementNode.h"

//ASTDeclarationStatementNode::ASTDeclarationStatementNode(ASTExpressionNode * expr, string varName, TYPE varType){
//    varExpression = expr;
//    variableName = varName;
//    variableType = varType;
//}

ASTDeclarationStatementNode::ASTDeclarationStatementNode(ASTIdentifierExpressionNode * id, ASTExpressionNode * expr){
    variableIdentifier = id;
    variableExpression = expr;
}

void ASTDeclarationStatementNode::accept(Visitor* v){
    v->visit(this);
}