//
// Created by stefaniatadama on 26/04/2018.
//

#include "ASTAssignmentStatementNode.h"

ASTAssignmentStatementNode::ASTAssignmentStatementNode(ASTIdentifierExpressionNode* id, ASTExpressionNode* expr){
    identifier = id;
    assignmentExpression = expr;
}

//ASTAssignmentStatementNode::ASTAssignmentStatementNode(ASTExpressionNode* expr, string id){
//    assignmentExpression = expr;
//    identifier = id;
//}

void ASTAssignmentStatementNode::accept(Visitor* v){
    v->visit(this);
}