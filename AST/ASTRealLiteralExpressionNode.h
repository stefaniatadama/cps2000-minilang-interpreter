#ifndef ASSIGNMENT_ASTREALLITERALEXPRESSIONNODE_H
#define ASSIGNMENT_ASTREALLITERALEXPRESSIONNODE_H


#include "ASTLiteralExpressionNode.h"

class ASTRealLiteralExpressionNode : public ASTLiteralExpressionNode {

    public:
        float value;

        ASTRealLiteralExpressionNode(float);
        void accept(Visitor* v);
};


#endif //ASSIGNMENT_ASTREALLITERALEXPRESSIONNODE_H
