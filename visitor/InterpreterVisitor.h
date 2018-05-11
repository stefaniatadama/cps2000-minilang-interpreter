#ifndef ASSIGNMENT_INTERPRETERVISITOR_H
#define ASSIGNMENT_INTERPRETERVISITOR_H

#include <stack>
#include "Visitor.h"
#include "../interpreter/InterpreterScope.h"

using namespace std;

class InterpreterVisitor : public Visitor{

    public:
        stack<InterpreterScope*> scopes;
        VarValue lastValue;
        TYPE lastType;
        //Vector holding a list of variable names, their types and their values assigned in a function call
        vector<tuple<string, TYPE, VarValue>> currentParams;

        InterpreterVisitor();
        InterpreterVisitor(InterpreterScope*);

        InterpreterScope* getCurrentScope();

        void visit(ASTProgramNode*);
        void visit(ASTAssignmentStatementNode*);
        void visit(ASTBinaryExpressionNode*);
        void visit(ASTBlockStatementNode*);
        void visit(ASTBoolLiteralExpressionNode*);
        void visit(ASTDeclarationStatementNode*);
        void visit(ASTFunctionCallExpressionNode*);
        void visit(ASTFunctionDeclarationStatementNode*);
        void visit(ASTIdentifierExpressionNode*);
        void visit(ASTIfStatementNode*);
        void visit(ASTIntLiteralExpressionNode*);
        void visit(ASTPrintStatementNode*);
        void visit(ASTRealLiteralExpressionNode*);
        void visit(ASTReturnStatementNode*);
        void visit(ASTStringLiteralExpressionNode*);
        void visit(ASTUnaryExpressionNode*);
        void visit(ASTWhileStatementNode*);
};

#endif //ASSIGNMENT_INTERPRETERVISITOR_H