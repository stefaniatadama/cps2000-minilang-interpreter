//
// Created by stefaniatadama on 25/04/2018.
//

#include "ASTRealLiteralExpressionNode.h"

ASTRealLiteralExpressionNode::ASTRealLiteralExpressionNode(float val){
    value = val;
}

void ASTRealLiteralExpressionNode::accept(Visitor* v){
    v->visit(this);
}