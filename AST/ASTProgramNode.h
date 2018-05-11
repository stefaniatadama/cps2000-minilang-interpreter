#ifndef ASSIGNMENT_ASTPROGRAMNODE_H
#define ASSIGNMENT_ASTPROGRAMNODE_H

#include <vector>
#include "ASTNode.h"
#include "../visitor/Visitor.h"

using namespace std;

class ASTProgramNode : public ASTNode{

    public:
        vector<ASTNode*> programStatements;

        ASTProgramNode(vector<ASTNode*>);
        void accept(Visitor* v);
};


#endif //ASSIGNMENT_ASTPROGRAMNODE_H
