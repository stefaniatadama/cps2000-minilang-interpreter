//
// Created by stefaniatadama on 25/04/2018.
//

#include "ASTFunctionCallExpressionNode.h"

ASTFunctionCallExpressionNode::ASTFunctionCallExpressionNode(vector<ASTExpressionNode *> args, string funcName){
    argumentList = args;
    functionName = funcName;
}

void ASTFunctionCallExpressionNode::accept(Visitor* v){
    v->visit(this);
}