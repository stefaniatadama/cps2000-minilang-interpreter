//
// Created by stefaniatadama on 22/04/2018.
//

#ifndef ASSIGNMENT_ASTEXPRESSIONNODE_H
#define ASSIGNMENT_ASTEXPRESSIONNODE_H

#include "ASTNode.h"

class ASTExpressionNode : public ASTNode{

    public:
        ASTExpressionNode();

        void accept(Visitor* v) override = 0;
};


#endif //ASSIGNMENT_ASTEXPRESSIONNODE_H
