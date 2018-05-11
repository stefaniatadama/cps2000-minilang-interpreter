#ifndef ASSIGNMENT_ASTSTRINGLITERALEXPRESSIONNODE_H
#define ASSIGNMENT_ASTSTRINGLITERALEXPRESSIONNODE_H


#include "ASTLiteralExpressionNode.h"

class ASTStringLiteralExpressionNode : public ASTLiteralExpressionNode{

    public:
        string value;

        ASTStringLiteralExpressionNode(string);
        void accept(Visitor* v);

};


#endif //ASSIGNMENT_ASTSTRINGLITERALEXPRESSIONNODE_H
