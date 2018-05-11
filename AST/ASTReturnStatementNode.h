#ifndef ASSIGNMENT_ASTRETURNSTATEMENTNODE_H
#define ASSIGNMENT_ASTRETURNSTATEMENTNODE_H

#include "ASTExpressionNode.h"
#include "ASTStatementNode.h"

class ASTReturnStatementNode : public ASTStatementNode{

    public:
        ASTExpressionNode* expressionToReturn;

        ASTReturnStatementNode(ASTExpressionNode*);
        void accept(Visitor* v);
};


#endif //ASSIGNMENT_ASTRETURNSTATEMENTNODE_H
