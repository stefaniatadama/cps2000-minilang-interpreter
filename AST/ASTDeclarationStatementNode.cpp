
#include "ASTDeclarationStatementNode.h"

ASTDeclarationStatementNode::ASTDeclarationStatementNode(ASTIdentifierExpressionNode * id, ASTExpressionNode * expr){
    variableIdentifier = id;
    variableExpression = expr;
}

void ASTDeclarationStatementNode::accept(Visitor* v){
    v->visit(this);
}