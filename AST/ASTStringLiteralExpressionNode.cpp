#include "ASTStringLiteralExpressionNode.h"

ASTStringLiteralExpressionNode::ASTStringLiteralExpressionNode(string val){
    value = val;
}

void ASTStringLiteralExpressionNode::accept(Visitor* v){
    v->visit(this);
}