//
// Created by stefaniatadama on 26/04/2018.
//

#include "ASTPrintStatementNode.h"

ASTPrintStatementNode::ASTPrintStatementNode(ASTExpressionNode * toPrint){
    expressionToPrint = toPrint;
}

void ASTPrintStatementNode::accept(Visitor* v){
    v->visit(this);
}