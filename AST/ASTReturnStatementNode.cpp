//
// Created by stefaniatadama on 26/04/2018.
//

#include "ASTReturnStatementNode.h"

ASTReturnStatementNode::ASTReturnStatementNode(ASTExpressionNode * toReturn){
    expressionToReturn = toReturn;
}

void ASTReturnStatementNode::accept(Visitor* v){
    v->visit(this);
}