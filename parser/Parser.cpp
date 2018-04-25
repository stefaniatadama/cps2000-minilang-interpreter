//
// Created by stefaniatadama on 22/04/2018.
//

#include <stdexcept>
#include "Parser.h"
#include "../AST/ASTRealLiteralExpressionNode.h"
#include "../AST/ASTIntLiteralExpressionNode.h"
#include "../AST/ASTBoolLiteralExpressionNode.h"
#include "../AST/ASTStringLiteralExpressionNode.h"
#include "../AST/ASTIdentifierExpressionNode.h"
#include "../AST/ASTBinaryExpessionNode.h"

//Sets Parser class lexer to l
Parser::Parser(Lexer& l) : lexer(l){
}

void Parser::parse(){
    parseStatement();
}

TYPE Parser::getType(string lexeme){
    if(lexeme == "real")
        return REAL;
    else if(lexeme == "int")
        return INT;
    else if(lexeme == "bool")
        return BOOL;
    else if(lexeme == "string")
        return STRING;
}

bool Parser::toBool(string str){
    return str == "true";
}

ASTNode* Parser::parseStatement(){
    currentToken = lexer.getNextToken();

    switch(currentToken.tokenType){
        case TOK_Var: {
            return parseVariableDeclaration();
        }
    }
}

ASTExpressionNode* Parser::parseUnaryExpression(){

}

ASTExpressionNode* Parser::parseBinaryExpression(){

}

ASTExpressionNode* Parser::parseExpression(){
    ASTExpressionNode * expressionNode = parseSimpleExpression();
    string op;

    if(lexer.getLookahead().tokenType == TOK_RelOp){
        currentToken = lexer.getNextToken();
        op = currentToken.lexeme;

        //Recursively parse the right expression
        return new ASTBinaryExpessionNode(op, expressionNode, parseExpression());
    }

    return expressionNode;
}

ASTExpressionNode* Parser::parseSimpleExpression(){
    ASTExpressionNode * expressionNode = parseTerm();
    string op;

    if(lexer.getLookahead().tokenType == TOK_AdditiveOp || lexer.getLookahead().tokenType == TOK_Or){
        currentToken = lexer.getNextToken();
        op = currentToken.lexeme;

        //Recursively parse the right expression
        return new ASTBinaryExpessionNode(op, expressionNode, parseSimpleExpression());
    }

    return expressionNode;
}

ASTExpressionNode* Parser::parseTerm(){
    ASTExpressionNode * expressionNode = parseFactor();
    string op;

    if(lexer.getLookahead().tokenType == TOK_MultiplicativeOp || lexer.getLookahead().tokenType == TOK_And){
        currentToken = lexer.getNextToken();
        op = currentToken.lexeme;

        //Recursively parse the right expression
        return new ASTBinaryExpessionNode(op, expressionNode, parseTerm());
    }

    return expressionNode;
}

ASTFunctionCallExpressionNode* Parser::parseFunctionCall(){
    string functionName = currentToken.lexeme;

    //Make currentToken '('
    currentToken = lexer.getNextToken();

    vector<ASTExpressionNode*> * expressionNode;

    //If next token is not ')', function is being passed some argument(s)
    if(lexer.getLookahead().tokenType != TOK_CloseParenthesis)
         expressionNode = parseActualParams();
    else
        lexer.getNextToken(); //Consume ')' in case there are no arguments

    return new ASTFunctionCallExpressionNode(expressionNode, functionName);
}

vector<ASTExpressionNode*>* Parser::parseActualParams(){
    //Storing arguments in a vector
    vector<ASTExpressionNode*> * arguments;

    ASTExpressionNode * expressionNode = parseExpression();
    arguments->push_back(expressionNode);

    //If ',' follows, more arguments were passed
    while(lexer.getLookahead().tokenType == TOK_Comma){
        //Consume ','
        currentToken = lexer.getNextToken();
        arguments->push_back(parseExpression());
    }

    currentToken = lexer.getNextToken();

    if(currentToken.tokenType != TOK_CloseParenthesis)
        throw runtime_error("Unexpected token: expected ')' after list of arguments in function call.");
    else
        return arguments;
}

ASTExpressionNode* Parser::parseFactor(){
    currentToken = lexer.getNextToken();

    switch(currentToken.tokenType){
        //Literal
        case(TOK_FloatLiteral):
        case(TOK_IntLiteral):
        case(TOK_Boolean):
        case(TOK_String): {
            ASTLiteralExpressionNode *literalNode = parseLiteral();
            return literalNode;
        }

        /*Identifier & FunctionCall
         * Upon meeting an identifier, we check if there is a parenthesis directly after it,
        in which case it would be a function call */
        case(TOK_Identifier): {
            if (lexer.getLookahead().tokenType == TOK_OpenParenthesis) {
                ASTFunctionCallExpressionNode *expressionNode = parseFunctionCall();
                return expressionNode;
            } else {
                return new ASTIdentifierExpressionNode(currentToken.lexeme);
            }
        }

        //SubExpression
        case(TOK_OpenParenthesis): {
            ASTExpressionNode *expressionNode = parseExpression();

            lexer.getNextToken();
            if (currentToken.tokenType != TOK_CloseParenthesis)
                throw runtime_error("Unexpected token: expected ')' after subexpression.");
            else
                return expressionNode;
        }

        //Unary
        case(TOK_AdditiveOp):
        case(TOK_Not):
            return parseExpression();
    }
}

ASTLiteralExpressionNode * Parser::parseLiteral(){
    switch(currentToken.tokenType){
        case(TOK_FloatLiteral):
            return new ASTRealLiteralExpressionNode(stof(currentToken.lexeme));
        case(TOK_IntLiteral):
            return new ASTIntLiteralExpressionNode(stoi(currentToken.lexeme));
        case(TOK_Boolean):
            return new ASTBoolLiteralExpressionNode(toBool(currentToken.lexeme));
        case(TOK_String):
            return new ASTStringLiteralExpressionNode(currentToken.lexeme);
        default:
            return nullptr;
    }
}

ASTDeclarationStatementNode* Parser::parseVariableDeclaration(){
    currentToken = lexer.getNextToken();

    if(currentToken.tokenType != TOK_Identifier){
        throw runtime_error("Unexpected token: expected identifier after var keyword.");
    }

    string identifier = currentToken.lexeme;
    currentToken = lexer.getNextToken();

    if(currentToken.tokenType != TOK_Colon){
        throw runtime_error("Unexpected token: expected ':' after identifier.");
    }

    currentToken = lexer.getNextToken();

    if(currentToken.tokenType != TOK_LangType){
        throw runtime_error("Unexpected token: expected variable type after ':'.");
    }

    TYPE type = getType(currentToken.lexeme);
    currentToken = lexer.getNextToken();

    if(currentToken.tokenType != TOK_Equals){
        throw runtime_error("Unexpected token: expected '=' after variable type.");
    }

    ASTExpressionNode * expressionNode = parseExpression();

    currentToken = lexer.getNextToken();

    if(currentToken.tokenType != TOK_Delimeter){
        throw runtime_error("Unexpected token: expected ';' at the end of statement.");
    }

    return new ASTDeclarationStatementNode(expressionNode, identifier, type);
}