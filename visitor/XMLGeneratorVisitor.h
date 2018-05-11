#ifndef ASSIGNMENT_XMLGENERATORVISITOR_H
#define ASSIGNMENT_XMLGENERATORVISITOR_H

#include <fstream>
#include "Visitor.h"

using namespace std;

class XMLGeneratorVisitor : public Visitor{

    public:
        //To print enum as their corresponding string value
        string types[4] = {"real", "int", "bool", "string"};

        //New output stream
        ofstream output;

        unsigned int currentIndent;

        string setIndent();
        string xml_op(string);

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


#endif //ASSIGNMENT_XMLGENERATORVISITOR_H
