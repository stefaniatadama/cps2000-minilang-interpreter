//
// Created by stefaniatadama on 23/04/2018.
//

#include "ASTDeclarationStatementNode.h"

ASTDeclarationStatementNode::ASTDeclarationStatementNode(ASTExpressionNode * leftChild, string varName, TYPE varType){
    left = leftChild;
    variableName = varName;
    variableType = varType;
}
