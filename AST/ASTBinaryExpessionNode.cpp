//
// Created by stefaniatadama on 22/04/2018.
//

#include "ASTBinaryExpessionNode.h"

ASTBinaryExpessionNode::ASTBinaryExpessionNode(string optr, ASTExpressionNode *leftChild, ASTExpressionNode *rightChild) {
    op = optr;
    left = leftChild;
    right = rightChild;
}