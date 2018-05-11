#ifndef ASSIGNMENT_ASTSTATEMENTNODE_H
#define ASSIGNMENT_ASTSTATEMENTNODE_H

#include "ASTNode.h"

class ASTStatementNode : public ASTNode{

    public:
        ASTStatementNode();
        void accept(Visitor* v) override = 0;

};


#endif //ASSIGNMENT_ASTSTATEMENTNODE_H
