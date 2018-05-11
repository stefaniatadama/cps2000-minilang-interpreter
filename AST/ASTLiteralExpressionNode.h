#ifndef ASSIGNMENT_ASTLITERALEXPRESSIONNODE_H
#define ASSIGNMENT_ASTLITERALEXPRESSIONNODE_H

#include "ASTExpressionNode.h"
#include "../lexer/Token.h"

using namespace std;

class ASTLiteralExpressionNode : public ASTExpressionNode{

    public:
        ASTLiteralExpressionNode();
        void accept(Visitor* v) override = 0;
};


#endif //ASSIGNMENT_ASTLITERALEXPRESSIONNODE_H
