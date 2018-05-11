#ifndef ASSIGNMENT_ASTBOOLLITERALEXPRESSIONNODE_H
#define ASSIGNMENT_ASTBOOLLITERALEXPRESSIONNODE_H


#include "ASTLiteralExpressionNode.h"

class ASTBoolLiteralExpressionNode : public ASTLiteralExpressionNode{

    public:
        bool value;

        ASTBoolLiteralExpressionNode(bool);
        void accept(Visitor* v);

};


#endif //ASSIGNMENT_ASTBOOLLITERALEXPRESSIONNODE_H
