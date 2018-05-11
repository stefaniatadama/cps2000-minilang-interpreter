#ifndef ASSIGNMENT_ASTPRINTSTATEMENTNODE_H
#define ASSIGNMENT_ASTPRINTSTATEMENTNODE_H

#include "ASTStatementNode.h"
#include "ASTExpressionNode.h"

class ASTPrintStatementNode : public ASTStatementNode{

    public:
        ASTExpressionNode* expressionToPrint;

        ASTPrintStatementNode(ASTExpressionNode*);
        void accept(Visitor* v);
};


#endif //ASSIGNMENT_ASTPRINTSTATEMENTNODE_H
