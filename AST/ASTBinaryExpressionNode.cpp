//
// Created by stefaniatadama on 22/04/2018.
//

#include "ASTBinaryExpressionNode.h"

ASTBinaryExpressionNode::ASTBinaryExpressionNode(string optr, ASTExpressionNode *leftChild, ASTExpressionNode *rightChild) {
    op = optr;
    left = leftChild;
    right = rightChild;
}

void ASTBinaryExpressionNode::accept(Visitor* v){
    v->visit(this);
}