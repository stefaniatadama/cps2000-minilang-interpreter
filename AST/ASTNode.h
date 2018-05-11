#ifndef ASSIGNMENT_ASTNODE_H
#define ASSIGNMENT_ASTNODE_H

#include "../visitor/Visitor.h"

enum TYPE{
    REAL, INT, BOOL, STRING
};

class ASTNode{

    public:
        ASTNode();

        virtual void accept(Visitor* v) = 0;

};


#endif //ASSIGNMENT_ASTNODE_H
