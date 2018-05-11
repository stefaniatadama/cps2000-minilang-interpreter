#ifndef ASSIGNMENT_ASTINTLITERALEXPRESSIONNODE_H
#define ASSIGNMENT_ASTINTLITERALEXPRESSIONNODE_H

#include "ASTLiteralExpressionNode.h"

class ASTIntLiteralExpressionNode : public ASTLiteralExpressionNode{

    public:
        int value;

        ASTIntLiteralExpressionNode(int);
        void accept(Visitor* v);
};


#endif //ASSIGNMENT_ASTINTLITERALEXPRESSIONNODE_H
