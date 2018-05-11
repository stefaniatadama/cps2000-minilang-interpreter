#include "ASTRealLiteralExpressionNode.h"

ASTRealLiteralExpressionNode::ASTRealLiteralExpressionNode(float val){
    value = val;
}

void ASTRealLiteralExpressionNode::accept(Visitor* v){
    v->visit(this);
}