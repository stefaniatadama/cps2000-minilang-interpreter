#include "ASTBoolLiteralExpressionNode.h"

ASTBoolLiteralExpressionNode::ASTBoolLiteralExpressionNode(bool val){
    value = val;
}

void ASTBoolLiteralExpressionNode::accept(Visitor* v){
    v->visit(this);
}