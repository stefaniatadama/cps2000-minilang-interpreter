#ifndef ASSIGNMENT_ASTUNARYEXPRESSIONNODE_H
#define ASSIGNMENT_ASTUNARYEXPRESSIONNODE_H

#include <string>
#include "ASTExpressionNode.h"

using namespace std;

class ASTUnaryExpressionNode : public ASTExpressionNode{

    public:
        string op;
        ASTExpressionNode* expressionNode;

        ASTUnaryExpressionNode(string, ASTExpressionNode*);
        void accept(Visitor *v);
};


#endif //ASSIGNMENT_ASTUNARYEXPRESSIONNODE_H
