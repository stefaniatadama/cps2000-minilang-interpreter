//
// Created by stefaniatadama on 27/04/2018.
//

#include "ASTFunctionDeclarationStatementNode.h"

ASTFunctionDeclarationStatementNode::ASTFunctionDeclarationStatementNode(string funcName,
                                                                         vector<ASTIdentifierExpressionNode *> params,
                                                                         TYPE type,
                                                                         ASTBlockStatementNode* funcBody){
    functionName = funcName;
    formalParams = params;
    functionReturnType = type;
    functionBody = funcBody;
}

void ASTFunctionDeclarationStatementNode::accept(Visitor* v){
    v->visit(this);
}