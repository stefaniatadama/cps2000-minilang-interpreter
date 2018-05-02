//
// Created by stefaniatadama on 26/04/2018.
//

#include "ASTIfStatementNode.h"

ASTIfStatementNode::ASTIfStatementNode(ASTExpressionNode * condition, ASTBlockStatementNode* ifBlock, ASTBlockStatementNode* elseBlock){
    conditionExpression = condition;
    ifBody = ifBlock;
    elseBody = elseBlock;
}

void ASTIfStatementNode::accept(Visitor* v){
    v->visit(this);
}