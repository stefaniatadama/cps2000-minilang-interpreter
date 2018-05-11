#include "ASTBlockStatementNode.h"

ASTBlockStatementNode::ASTBlockStatementNode(vector<ASTNode*> stats){
    statements = stats;
}

void ASTBlockStatementNode::accept(Visitor* v){
    v->visit(this);
}