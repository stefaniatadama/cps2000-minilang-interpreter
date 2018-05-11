#include "ASTWhileStatementNode.h"

ASTWhileStatementNode::ASTWhileStatementNode(ASTExpressionNode * condition, ASTBlockStatementNode* whileBlock){
    conditionExpression = condition;
    whileBody = whileBlock;
}

void ASTWhileStatementNode::accept(Visitor* v){
    v->visit(this);
}