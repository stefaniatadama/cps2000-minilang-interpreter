//
// Created by stefaniatadama on 27/04/2018.
//

#include "ASTBlockStatementNode.h"

ASTBlockStatementNode::ASTBlockStatementNode(vector<ASTNode*> stats){
    statements = stats;
}

void ASTBlockStatementNode::accept(Visitor* v){
    v->visit(this);
}