//
// Created by stefaniatadama on 23/04/2018.
//

#ifndef ASSIGNMENT_ASTDECLARATIONSTATEMENT_H
#define ASSIGNMENT_ASTDECLARATIONSTATEMENT_H

#include <string>
#include "ASTStatementNode.h"
#include "ASTExpressionNode.h"
#include "ASTIdentifierExpressionNode.h"

using namespace std;

class Parser;

class ASTDeclarationStatementNode : public ASTStatementNode{

    public:
        ASTIdentifierExpressionNode * variableIdentifier;
//        string variableName;
//        TYPE variableType;
        ASTExpressionNode * variableExpression;

//        ASTDeclarationStatementNode(ASTExpressionNode *, string, TYPE);
        ASTDeclarationStatementNode(ASTIdentifierExpressionNode*, ASTExpressionNode*);

        void accept(Visitor* v);
};


#endif //ASSIGNMENT_ASTDECLARATIONSTATEMENT_H
