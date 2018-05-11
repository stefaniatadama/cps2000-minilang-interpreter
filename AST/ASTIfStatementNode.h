#ifndef ASSIGNMENT_ASTIFSTATEMENTNODE_H
#define ASSIGNMENT_ASTIFSTATEMENTNODE_H

#include <vector>
#include "ASTStatementNode.h"
#include "ASTExpressionNode.h"
#include "ASTBlockStatementNode.h"

using namespace std;

class ASTIfStatementNode : public ASTStatementNode{

    public:
        ASTExpressionNode* conditionExpression;
        ASTBlockStatementNode* ifBody;
        ASTBlockStatementNode* elseBody = nullptr;

        ASTIfStatementNode(ASTExpressionNode*, ASTBlockStatementNode*, ASTBlockStatementNode*);
        void accept(Visitor* v);

};


#endif //ASSIGNMENT_ASTIFSTATEMENTNODE_H
