//
// Created by stefaniatadama on 22/04/2018.
//

#ifndef ASSIGNMENT_ASTBINARYEXPRNODE_H
#define ASSIGNMENT_ASTBINARYEXPRNODE_H

#include<string>
#include "ASTExpressionNode.h"

using namespace std;

class ASTBinaryExpessionNode : public ASTExpressionNode{

    public:
        string op;
        ASTExpressionNode * left;
        ASTExpressionNode * right;

        ASTBinaryExpessionNode(string, ASTExpressionNode *, ASTExpressionNode *);
};


#endif //ASSIGNMENT_ASTBINARYEXPRNODE_H
