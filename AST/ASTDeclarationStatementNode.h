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
        ASTExpressionNode * variableExpression;

        ASTDeclarationStatementNode(ASTIdentifierExpressionNode*, ASTExpressionNode*);

        void accept(Visitor* v);
};


#endif //ASSIGNMENT_ASTDECLARATIONSTATEMENT_H
