//
// Created by stefaniatadama on 25/04/2018.
//

#ifndef ASSIGNMENT_ASTINTLITERALEXPRESSIONNODE_H
#define ASSIGNMENT_ASTINTLITERALEXPRESSIONNODE_H

#include "ASTLiteralExpressionNode.h"

class ASTIntLiteralExpressionNode : public ASTLiteralExpressionNode{

    public:
        int value;

        ASTIntLiteralExpressionNode(int);

};


#endif //ASSIGNMENT_ASTINTLITERALEXPRESSIONNODE_H
