//
// Created by stefaniatadama on 22/04/2018.
//

#ifndef ASSIGNMENT_PARSER_H
#define ASSIGNMENT_PARSER_H


#include "../AST/ASTExpressionNode.h"
#include "../lexer/Lexer.h"
#include "../AST/ASTDeclarationStatementNode.h"
#include "../AST/ASTLiteralExpressionNode.h"
#include "../AST/ASTFunctionCallExpressionNode.h"

class Parser {

    public:
        Parser(Lexer&);
        void parse();

    private:
        Lexer lexer;
        Token currentToken;

        TYPE getType(string);
        bool toBool(string);

        ASTNode * parseStatement();

        ASTExpressionNode * parseUnaryExpression();
        ASTExpressionNode * parseBinaryExpression();
        ASTExpressionNode * parseExpression();
        ASTExpressionNode * parseSimpleExpression();
        ASTExpressionNode * parseTerm();
        ASTExpressionNode * parseFactor();
        ASTLiteralExpressionNode * parseLiteral();
        ASTFunctionCallExpressionNode * parseFunctionCall();
        vector<ASTExpressionNode*> * parseActualParams();

        ASTDeclarationStatementNode * parseVariableDeclaration();
};


#endif //ASSIGNMENT_PARSER_H
