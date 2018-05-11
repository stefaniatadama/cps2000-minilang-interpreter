#include "ASTPrintStatementNode.h"

ASTPrintStatementNode::ASTPrintStatementNode(ASTExpressionNode * toPrint){
    expressionToPrint = toPrint;
}

void ASTPrintStatementNode::accept(Visitor* v){
    v->visit(this);
}