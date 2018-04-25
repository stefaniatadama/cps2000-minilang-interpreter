//
// Created by stefaniatadama on 25/04/2018.
//

#ifndef ASSIGNMENT_ASTSTRINGLITERALEXPRESSIONNODE_H
#define ASSIGNMENT_ASTSTRINGLITERALEXPRESSIONNODE_H


#include "ASTLiteralExpressionNode.h"

class ASTStringLiteralExpressionNode : public ASTLiteralExpressionNode{

    public:
        string value;

        ASTStringLiteralExpressionNode(string);

};


#endif //ASSIGNMENT_ASTSTRINGLITERALEXPRESSIONNODE_H
