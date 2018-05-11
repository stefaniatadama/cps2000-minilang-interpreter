#include "ASTAssignmentStatementNode.h"

ASTAssignmentStatementNode::ASTAssignmentStatementNode(ASTIdentifierExpressionNode* id, ASTExpressionNode* expr){
    identifier = id;
    assignmentExpression = expr;
}

void ASTAssignmentStatementNode::accept(Visitor* v){
    v->visit(this);
}