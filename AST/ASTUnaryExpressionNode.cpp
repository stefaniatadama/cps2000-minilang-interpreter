#include "ASTUnaryExpressionNode.h"

ASTUnaryExpressionNode::ASTUnaryExpressionNode(string oprtr, ASTExpressionNode* exprNode){
    op = oprtr;
    expressionNode = exprNode;
}

void ASTUnaryExpressionNode::accept(Visitor* v){
    v->visit(this);
}