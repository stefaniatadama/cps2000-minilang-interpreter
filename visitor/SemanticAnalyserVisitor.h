#ifndef ASSIGNMENT_SEMANTICANALYSERVISITOR_H
#define ASSIGNMENT_SEMANTICANALYSERVISITOR_H

#include <stack>

#include "Visitor.h"
#include "../semantic_analysis/Scope.h"

using namespace std;

class SemanticAnalyserVisitor : public Visitor{

    public:
        //Stores all scopes in the input program
        stack<Scope*> scopes;
        TYPE lastType;
        //Holds the parameters of current functions being declared
        vector<pair<string, TYPE>> currentParams;
        stack<TYPE> functionTypes;

        SemanticAnalyserVisitor();
        SemanticAnalyserVisitor(Scope*);

        string getStringType(TYPE);
        Scope* getCurrentScope();
        //Recursive function which checks if a statement returns
        bool returns(ASTNode*);

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


#endif //ASSIGNMENT_SEMANTICANALYSERVISITOR_H
