#ifndef ASSIGNMENT_ASTBLOCKSTATEMENTNODE_H
#define ASSIGNMENT_ASTBLOCKSTATEMENTNODE_H

#include <vector>
#include "ASTStatementNode.h"

using namespace std;

class ASTBlockStatementNode : public ASTStatementNode{

    public:
        vector<ASTNode*> statements;

        ASTBlockStatementNode(vector<ASTNode*>);
        void accept(Visitor* v);
};


#endif //ASSIGNMENT_ASTBLOCKSTATEMENTNODE_H
