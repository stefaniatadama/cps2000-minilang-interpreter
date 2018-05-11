#include "ASTReturnStatementNode.h"

ASTReturnStatementNode::ASTReturnStatementNode(ASTExpressionNode * toReturn){
    expressionToReturn = toReturn;
}

void ASTReturnStatementNode::accept(Visitor* v){
    v->visit(this);
}