#ifndef ASSIGNMENT_ASTFUNCTIONDECLARATIONSTATEMENTNODE_H
#define ASSIGNMENT_ASTFUNCTIONDECLARATIONSTATEMENTNODE_H

#include <string>
#include<vector>
#include "ASTStatementNode.h"
#include "ASTIdentifierExpressionNode.h"
#include "ASTBlockStatementNode.h"

using namespace std;

class ASTFunctionDeclarationStatementNode : public ASTStatementNode{

    public:
        string functionName;
        vector<ASTIdentifierExpressionNode*> formalParams;
        TYPE functionReturnType;
        ASTBlockStatementNode* functionBody;

        ASTFunctionDeclarationStatementNode(string, vector<ASTIdentifierExpressionNode*>, TYPE, ASTBlockStatementNode*);
        void accept(Visitor* v);
};


#endif //ASSIGNMENT_ASTFUNCTIONDECLARATIONSTATEMENTNODE_H
