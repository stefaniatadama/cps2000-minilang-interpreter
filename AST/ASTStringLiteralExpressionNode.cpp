//
// Created by stefaniatadama on 25/04/2018.
//

#include "ASTStringLiteralExpressionNode.h"

ASTStringLiteralExpressionNode::ASTStringLiteralExpressionNode(string val){
    value = val;
}

void ASTStringLiteralExpressionNode::accept(Visitor* v){
    v->visit(this);
}