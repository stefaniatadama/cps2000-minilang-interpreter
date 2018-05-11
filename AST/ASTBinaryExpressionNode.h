#ifndef ASSIGNMENT_ASTBINARYEXPRESSIONNODE_H
#define ASSIGNMENT_ASTBINARYEXPRESSIONNODE_H

#include <string>
#include "ASTExpressionNode.h"

using namespace std;

class ASTBinaryExpressionNode : public ASTExpressionNode{

    public:
        string op;
        ASTExpressionNode * left;
        ASTExpressionNode * right;

        ASTBinaryExpressionNode(string, ASTExpressionNode *, ASTExpressionNode *);
        void accept(Visitor* v);

};


#endif //ASSIGNMENT_ASTBINARYEXPRESSIONNODE_H
