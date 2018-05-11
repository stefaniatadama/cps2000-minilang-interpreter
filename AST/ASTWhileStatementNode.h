#ifndef ASSIGNMENT_ASTWHILESTATEMENTNODE_H
#define ASSIGNMENT_ASTWHILESTATEMENTNODE_H

#include <vector>
#include "ASTExpressionNode.h"
#include "ASTStatementNode.h"
#include "ASTBlockStatementNode.h"

using namespace std;

class ASTWhileStatementNode : public ASTStatementNode{

    public:
        ASTExpressionNode* conditionExpression;
        ASTBlockStatementNode* whileBody;

        ASTWhileStatementNode(ASTExpressionNode*, ASTBlockStatementNode*);
        void accept(Visitor* v);
};


#endif //ASSIGNMENT_ASTWHILESTATEMENTNODE_H
