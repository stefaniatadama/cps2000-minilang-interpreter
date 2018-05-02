//
// Created by stefaniatadama on 28/04/2018.
//

#include "ASTProgramNode.h"

ASTProgramNode::ASTProgramNode(vector<ASTNode*> statements){
    programStatements = statements;
}

void ASTProgramNode::accept(Visitor* v){
    v->visit(this);
}