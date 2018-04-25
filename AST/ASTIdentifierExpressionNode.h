//
// Created by stefaniatadama on 25/04/2018.
//

#ifndef ASSIGNMENT_ASTIDENTIFIEREXPRESSIONNODE_H
#define ASSIGNMENT_ASTIDENTIFIEREXPRESSIONNODE_H

#include <string>
#include "ASTExpressionNode.h"

using namespace std;

class ASTIdentifierExpressionNode : public ASTExpressionNode{

    public:
        string identifierName;

        ASTIdentifierExpressionNode(string);
};


#endif //ASSIGNMENT_ASTIDENTIFIEREXPRESSIONNODE_H
