#ifndef ASSIGNMENT_VISITOR_H
#define ASSIGNMENT_VISITOR_H

class ASTNode;
class ASTAssignmentStatementNode;
class ASTBinaryExpressionNode;
class ASTBlockStatementNode;
class ASTBoolLiteralExpressionNode;
class ASTDeclarationStatementNode;
class ASTExpressionNode;
class ASTFunctionCallExpressionNode;
class ASTFunctionDeclarationStatementNode;
class ASTIdentifierExpressionNode;
class ASTIfStatementNode;
class ASTIntLiteralExpressionNode;
class ASTLiteralExpressionNode;
class ASTPrintStatementNode;
class ASTProgramNode;
class ASTRealLiteralExpressionNode;
class ASTReturnStatementNode;
class ASTStatementNode;
class ASTStringLiteralExpressionNode;
class ASTUnaryExpressionNode;
class ASTWhileStatementNode;

class Visitor {

    public:
        virtual void visit(ASTAssignmentStatementNode*) = 0;
        virtual void visit(ASTBinaryExpressionNode*) = 0;
        virtual void visit(ASTBlockStatementNode*) = 0;
        virtual void visit(ASTBoolLiteralExpressionNode*) = 0;
        virtual void visit(ASTDeclarationStatementNode*) = 0;
        virtual void visit(ASTFunctionCallExpressionNode*) = 0;
        virtual void visit(ASTFunctionDeclarationStatementNode*) = 0;
        virtual void visit(ASTIdentifierExpressionNode*) = 0;
        virtual void visit(ASTIfStatementNode*) = 0;
        virtual void visit(ASTIntLiteralExpressionNode*) = 0;
        virtual void visit(ASTPrintStatementNode*) = 0;
        virtual void visit(ASTProgramNode*) = 0;
        virtual void visit(ASTRealLiteralExpressionNode*) = 0;
        virtual void visit(ASTReturnStatementNode*) = 0;
        virtual void visit(ASTStringLiteralExpressionNode*) = 0;
        virtual void visit(ASTUnaryExpressionNode*) = 0;
        virtual void visit(ASTWhileStatementNode*) = 0;
};


#endif //ASSIGNMENT_VISITOR_H
