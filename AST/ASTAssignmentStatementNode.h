#ifndef ASSIGNMENT_ASTASSIGNMENTSTATEMENTNODE_H
#define ASSIGNMENT_ASTASSIGNMENTSTATEMENTNODE_H

#include <string>
#include "ASTExpressionNode.h"
#include "ASTStatementNode.h"
#include "../visitor/Visitor.h"

using namespace std;

class ASTAssignmentStatementNode : public ASTStatementNode{

    public:
        ASTIdentifierExpressionNode* identifier;
        ASTExpressionNode* assignmentExpression;

        ASTAssignmentStatementNode(ASTIdentifierExpressionNode*, ASTExpressionNode*);
        void accept(Visitor* v);
};

#endif //ASSIGNMENT_ASTASSIGNMENTSTATEMENTNODE_H
