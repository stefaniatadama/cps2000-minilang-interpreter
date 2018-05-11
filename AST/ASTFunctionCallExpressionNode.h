#ifndef ASSIGNMENT_ASTFUNCTIONCALLEXPRESSIONNODE_H
#define ASSIGNMENT_ASTFUNCTIONCALLEXPRESSIONNODE_H

#include <string>
#include <vector>
#include "ASTExpressionNode.h"

using namespace std;

class ASTFunctionCallExpressionNode : public ASTExpressionNode{

    public:
        string functionName;
        vector<ASTExpressionNode*> argumentList;

        ASTFunctionCallExpressionNode(vector<ASTExpressionNode*>, string);
        void accept(Visitor* v);
};


#endif //ASSIGNMENT_ASTFUNCTIONCALLEXPRESSIONNODE_H
