//
// Created by stefaniatadama on 02/05/2018.
//

#include "ASTUnaryExpressionNode.h"

ASTUnaryExpressionNode::ASTUnaryExpressionNode(string oprtr, ASTExpressionNode* exprNode){
    op = oprtr;
    expressionNode = exprNode;
}

void ASTUnaryExpressionNode::accept(Visitor* v){
    v->visit(this);
}