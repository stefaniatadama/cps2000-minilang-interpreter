//
// Created by stefaniatadama on 23/04/2018.
//

#ifndef ASSIGNMENT_ASTDECLARATIONSTATEMENT_H
#define ASSIGNMENT_ASTDECLARATIONSTATEMENT_H

#include <string>
#include "ASTStatementNode.h"
#include "ASTExpressionNode.h"

using namespace std;

class Parser;

class ASTDeclarationStatementNode : public ASTStatementNode{

    public:
        string variableName;
        TYPE variableType;
        ASTExpressionNode * left;

        ASTDeclarationStatementNode(ASTExpressionNode *, string, TYPE);

};


#endif //ASSIGNMENT_ASTDECLARATIONSTATEMENT_H
