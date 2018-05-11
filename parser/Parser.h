#ifndef ASSIGNMENT_PARSER_H
#define ASSIGNMENT_PARSER_H

#include "../AST/ASTExpressionNode.h"
#include "../lexer/Lexer.h"
#include "../AST/ASTDeclarationStatementNode.h"
#include "../AST/ASTLiteralExpressionNode.h"
#include "../AST/ASTFunctionCallExpressionNode.h"
#include "../AST/ASTAssignmentStatementNode.h"
#include "../AST/ASTIfStatementNode.h"
#include "../AST/ASTWhileStatementNode.h"
#include "../AST/ASTFunctionDeclarationStatementNode.h"
#include "../AST/ASTIdentifierExpressionNode.h"
#include "../AST/ASTBlockStatementNode.h"

class Parser {

    public:
        Parser(Lexer*);
        ASTProgramNode* parse();
        ASTExpressionNode * parseExpression();

    private:
        Lexer* lexer;
        Token currentToken;

        TYPE getType(string);
        bool toBool(string);

        ASTNode * parseStatement();

        ASTExpressionNode * parseSimpleExpression();
        ASTExpressionNode * parseTerm();
        ASTExpressionNode * parseFactor();
        ASTLiteralExpressionNode * parseLiteral();
        ASTFunctionCallExpressionNode * parseFunctionCall();
        vector<ASTExpressionNode*> * parseActualParams();
        ASTBlockStatementNode * parseBlock();
        vector<ASTIdentifierExpressionNode*> * parseFormalParams();
        ASTIdentifierExpressionNode* parseFormalParam();

        ASTDeclarationStatementNode * parseVariableDeclaration();
        ASTAssignmentStatementNode * parseAssignment();
        ASTIfStatementNode * parseIfStatement();
        ASTWhileStatementNode * parseWhileStatement();
        ASTFunctionDeclarationStatementNode * parseFunctionDeclaration();
};


#endif //ASSIGNMENT_PARSER_H
