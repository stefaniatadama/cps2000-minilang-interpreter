#include <iostream>
#include "ASTIdentifierExpressionNode.h"

ASTIdentifierExpressionNode::ASTIdentifierExpressionNode(string idName){
    identifierName = idName;
}

ASTIdentifierExpressionNode::ASTIdentifierExpressionNode(string idName, TYPE idType){
    identifierName = idName;
    identifierType = idType;
}

void ASTIdentifierExpressionNode::accept(Visitor* v){
    v->visit(this);
}