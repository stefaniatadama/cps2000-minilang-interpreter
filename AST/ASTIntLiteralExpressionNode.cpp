//
// Created by stefaniatadama on 25/04/2018.
//

#include "ASTIntLiteralExpressionNode.h"

ASTIntLiteralExpressionNode::ASTIntLiteralExpressionNode(int val){
    value = val;
}

void ASTIntLiteralExpressionNode::accept(Visitor* v){
    v->visit(this);
}
