#ifndef ASSIGNMENT_ASTIDENTIFIEREXPRESSIONNODE_H
#define ASSIGNMENT_ASTIDENTIFIEREXPRESSIONNODE_H

#include <string>
#include "ASTExpressionNode.h"

using namespace std;

class ASTIdentifierExpressionNode : public ASTExpressionNode{

    public:
        string identifierName;
        TYPE identifierType;

        ASTIdentifierExpressionNode(string);
        ASTIdentifierExpressionNode(string, TYPE);
        void accept(Visitor* v);
};


#endif //ASSIGNMENT_ASTIDENTIFIEREXPRESSIONNODE_H
