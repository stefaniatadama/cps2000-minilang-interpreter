#include <stdexcept>
#include <vector>
#include <iostream>
#include "Parser.h"
#include "../AST/ASTProgramNode.h"
#include "../AST/ASTRealLiteralExpressionNode.h"
#include "../AST/ASTIntLiteralExpressionNode.h"
#include "../AST/ASTBoolLiteralExpressionNode.h"
#include "../AST/ASTStringLiteralExpressionNode.h"
#include "../AST/ASTIdentifierExpressionNode.h"
#include "../AST/ASTBinaryExpressionNode.h"
#include "../AST/ASTAssignmentStatementNode.h"
#include "../AST/ASTPrintStatementNode.h"
#include "../AST/ASTReturnStatementNode.h"
#include "../AST/ASTUnaryExpressionNode.h"

//Sets Parser class lexer to l
Parser::Parser(Lexer* l) : lexer(l){
}

ASTProgramNode* Parser::parse(){
    auto statements = new vector<ASTNode*>;

    while(lexer->getLookahead().tokenType != TOK_EOF)
        statements->push_back(parseStatement());

    return new ASTProgramNode(*statements);
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
    switch(lexer->getLookahead().tokenType){
        case(TOK_Var):{
            currentToken = lexer->getNextToken();
            return parseVariableDeclaration();
        }

        case(TOK_Set):{
            currentToken = lexer->getNextToken();
            return parseAssignment();
        }

        case(TOK_Print):{
            currentToken = lexer->getNextToken();
            ASTExpressionNode * expressionNode = parseExpression();

            currentToken = lexer->getNextToken();

            if(currentToken.tokenType != TOK_Delimeter){
                throw runtime_error("Unexpected token on line " + to_string(currentToken.lineNumber) + ": expected ';' at the end of statement.");
            }

            return new ASTPrintStatementNode(expressionNode);
        }

        case(TOK_If):{
            currentToken = lexer->getNextToken();
            return parseIfStatement();
        }

        case(TOK_While):{
            currentToken = lexer->getNextToken();
            return parseWhileStatement();
        }

        case(TOK_Return):{
            currentToken = lexer->getNextToken();
            ASTExpressionNode * expressionNode = parseExpression();

            currentToken = lexer->getNextToken();

            if(currentToken.tokenType != TOK_Delimeter){
                throw runtime_error("Unexpected token on line " + to_string(currentToken.lineNumber) + ": expected ';' at the end of statement.");
            }

            return new ASTReturnStatementNode(expressionNode);
        }

        case(TOK_Def):{
            currentToken = lexer->getNextToken();
            return parseFunctionDeclaration();
        }

        case(TOK_OpenScope):{
            return parseBlock();
        }

        default:
            throw runtime_error("Error on line " + to_string(lexer->getLookahead().lineNumber) + ".");
    }
}

ASTExpressionNode* Parser::parseExpression(){
    ASTExpressionNode * expressionNode = parseSimpleExpression();
    string op;

    if(lexer->getLookahead().tokenType == TOK_RelOp){
        currentToken = lexer->getNextToken();
        op = currentToken.lexeme;

        //Recursively parse the right expression
        return new ASTBinaryExpressionNode(op, expressionNode, parseExpression());
    }

    return expressionNode;
}

ASTExpressionNode* Parser::parseSimpleExpression(){
    ASTExpressionNode * expressionNode = parseTerm();
    string op;

    if(lexer->getLookahead().tokenType == TOK_AdditiveOp || lexer->getLookahead().tokenType == TOK_Or){
        currentToken = lexer->getNextToken();
        op = currentToken.lexeme;

        //Recursively parse the right expression
        return new ASTBinaryExpressionNode(op, expressionNode, parseSimpleExpression());
    }

    return expressionNode;
}

ASTExpressionNode* Parser::parseTerm(){
    ASTExpressionNode * expressionNode = parseFactor();
    string op;

    if(lexer->getLookahead().tokenType == TOK_MultiplicativeOp || lexer->getLookahead().tokenType == TOK_And){
        currentToken = lexer->getNextToken();
        op = currentToken.lexeme;

        //Recursively parse the right expression
        return new ASTBinaryExpressionNode(op, expressionNode, parseTerm());
    }

    return expressionNode;
}

ASTFunctionCallExpressionNode* Parser::parseFunctionCall(){
    string functionName = currentToken.lexeme;

    //Make currentToken '('
    currentToken = lexer->getNextToken();

    auto expressionNode = new vector<ASTExpressionNode*>;

    //If next token is not ')', function is being passed some argument(s)
    if(lexer->getLookahead().tokenType != TOK_CloseParenthesis)
         expressionNode = parseActualParams();
    else
        lexer->getNextToken(); //Consume ')' in case there are no arguments

    return new ASTFunctionCallExpressionNode(*expressionNode, functionName);
}

vector<ASTExpressionNode*>* Parser::parseActualParams(){
    //Storing arguments in a vector
    auto arguments = new vector<ASTExpressionNode*>;
    arguments->push_back(parseExpression());

    //If ',' follows, more arguments were passed
    while(lexer->getLookahead().tokenType == TOK_Comma){
        //Consume ','
        currentToken = lexer->getNextToken();
        arguments->push_back(parseExpression());
    }

    currentToken = lexer->getNextToken();

    if(currentToken.tokenType != TOK_CloseParenthesis)
        throw runtime_error("Unexpected token on line " + to_string(currentToken.lineNumber) + ": expected ')' after list of arguments in function call.");

    return arguments;
}

ASTExpressionNode* Parser::parseFactor(){
    currentToken = lexer->getNextToken();

    switch(currentToken.tokenType){
        //Literal
        case(TOK_FloatLiteral):
        case(TOK_IntLiteral):
        case(TOK_Boolean):
        case(TOK_String):{
            ASTLiteralExpressionNode* literalNode = parseLiteral();
            return literalNode;
        }

        /* Identifier & FunctionCall
         * Upon meeting an identifier, we check if there is a parenthesis directly after it,
         * in which case it would be a function call */
        case(TOK_Identifier):{
            if (lexer->getLookahead().tokenType == TOK_OpenParenthesis) {
                ASTFunctionCallExpressionNode *expressionNode = parseFunctionCall();
                return expressionNode;
            } else {
                return new ASTIdentifierExpressionNode(currentToken.lexeme);
            }
        }

        //SubExpression
        case(TOK_OpenParenthesis):{
            ASTExpressionNode *expressionNode = parseExpression();

            currentToken = lexer->getNextToken();
            if (currentToken.tokenType != TOK_CloseParenthesis)
                throw runtime_error("Unexpected token on line " + to_string(currentToken.lineNumber) + ": expected ')' after subexpression." + currentToken.lexeme);

            return expressionNode;
        }

        //Unary
        case(TOK_AdditiveOp):
        case(TOK_Not): {
            return new ASTUnaryExpressionNode(currentToken.lexeme, parseExpression());
        }

        default:
            throw runtime_error("Unexpected token on line " + to_string(currentToken.lineNumber) + ": invalid expression.");
    }
}

ASTLiteralExpressionNode* Parser::parseLiteral(){
    switch(currentToken.tokenType){
        case(TOK_FloatLiteral):
            return new ASTRealLiteralExpressionNode(stof(currentToken.lexeme));
        case(TOK_IntLiteral):
            return new ASTIntLiteralExpressionNode(stoi(currentToken.lexeme));
        case(TOK_Boolean):
            return new ASTBoolLiteralExpressionNode(toBool(currentToken.lexeme));
        case(TOK_String):
            return new ASTStringLiteralExpressionNode(currentToken.lexeme.substr(1, currentToken.lexeme.size() - 2));
        default:
            return nullptr;
    }
}

ASTDeclarationStatementNode* Parser::parseVariableDeclaration(){
    currentToken = lexer->getNextToken();

    if(currentToken.tokenType != TOK_Identifier){
        throw runtime_error("Unexpected token on line " + to_string(currentToken.lineNumber) + " : expected identifier after var keyword.");
    }

    string identifier = currentToken.lexeme;
    currentToken = lexer->getNextToken();

    if(currentToken.tokenType != TOK_Colon){
        throw runtime_error("Unexpected token on line " + to_string(currentToken.lineNumber) + ": expected ':' after identifier.");
    }

    currentToken = lexer->getNextToken();

    if(currentToken.tokenType != TOK_LangType){
        throw runtime_error("Unexpected token on line " + to_string(currentToken.lineNumber) + ": expected variable type after ':'.");
    }

    TYPE type = getType(currentToken.lexeme);
    ASTIdentifierExpressionNode* identifierExpressionNode = new ASTIdentifierExpressionNode(identifier, type);

    currentToken = lexer->getNextToken();

    if(currentToken.tokenType != TOK_Equals){
        throw runtime_error("Unexpected token on line " + to_string(currentToken.lineNumber) + ": expected '=' after variable type.");
    }

    ASTExpressionNode * expressionNode = parseExpression();

    currentToken = lexer->getNextToken();

    if(currentToken.tokenType != TOK_Delimeter){
        throw runtime_error("Unexpected token on line " + to_string(currentToken.lineNumber) + ": expected ';' at the end of statement.");
    }

    return new ASTDeclarationStatementNode(identifierExpressionNode, expressionNode);
}

ASTAssignmentStatementNode* Parser::parseAssignment(){
    currentToken = lexer->getNextToken();

    if(currentToken.tokenType != TOK_Identifier){
        throw runtime_error("Unexpected token on line " + to_string(currentToken.lineNumber) + ": expected identifier after set keyword.");
    }

    string identifier = currentToken.lexeme;
    currentToken = lexer->getNextToken();

    ASTIdentifierExpressionNode* identifierExpressionNode = new ASTIdentifierExpressionNode(identifier);

    if(currentToken.tokenType != TOK_Equals){
        throw runtime_error("Unexpected token on line " + to_string(currentToken.lineNumber) + ": expected '=' after identifier.");
    }

    ASTExpressionNode * expressionNode = parseExpression();

    currentToken = lexer->getNextToken();

    if(currentToken.tokenType != TOK_Delimeter){
        throw runtime_error("Unexpected token on line " + to_string(currentToken.lineNumber) + ": expected ';' at the end of statement.");
    }

    return new ASTAssignmentStatementNode(identifierExpressionNode, expressionNode);
}

ASTIfStatementNode* Parser::parseIfStatement(){
    currentToken = lexer->getNextToken();

    if(currentToken.tokenType != TOK_OpenParenthesis){
        throw runtime_error("Unexpected token on line " + to_string(currentToken.lineNumber) + ": expected '(' after if keyword.");
    }

    ASTExpressionNode * ifConditionExpressionNode = parseExpression();
    currentToken = lexer->getNextToken();

    if(currentToken.tokenType != TOK_CloseParenthesis){
        throw runtime_error("Unexpected token on line " + to_string(currentToken.lineNumber) + ": expected ')' after expression.");
    }

    ASTBlockStatementNode* ifBody = parseBlock();
    ASTBlockStatementNode* elseBody = nullptr;

    if(lexer->getLookahead().tokenType == TOK_Else){
        //Make current token 'else'
        currentToken = lexer->getNextToken();

        elseBody = parseBlock();
    }

    return new ASTIfStatementNode(ifConditionExpressionNode, ifBody, elseBody);
}

ASTBlockStatementNode* Parser::parseBlock(){
    currentToken = lexer->getNextToken();

    if(currentToken.tokenType != TOK_OpenScope){
        throw runtime_error("Unexpected token on line " + to_string(currentToken.lineNumber) + ": expected '{' at the beginning of a block.");
    }

    auto statements = new vector<ASTNode*>;

    while(lexer->getLookahead().tokenType != TOK_CloseScope){
        statements->push_back(parseStatement());
    }

    currentToken = lexer->getNextToken();

    if(currentToken.tokenType != TOK_CloseScope){
        throw runtime_error("Unexpected token on line " + to_string(currentToken.lineNumber) + ": expected '}' at the end of a block.");
    }

    return new ASTBlockStatementNode(*statements);
}

ASTWhileStatementNode* Parser::parseWhileStatement(){
    currentToken = lexer->getNextToken();

    if(currentToken.tokenType != TOK_OpenParenthesis){
        throw runtime_error("Unexpected token on line " + to_string(currentToken.lineNumber) + ": expected '(' after while keyword.");
    }

    ASTExpressionNode * whileConditionExpressionNode = parseExpression();
    currentToken = lexer->getNextToken();

    if(currentToken.tokenType != TOK_CloseParenthesis){
        throw runtime_error("Unexpected token on line " + to_string(currentToken.lineNumber) + ": expected ')' after expression.");
    }

    ASTBlockStatementNode* whileBody = parseBlock();

    return new ASTWhileStatementNode(whileConditionExpressionNode, whileBody);
}

ASTFunctionDeclarationStatementNode* Parser::parseFunctionDeclaration(){
    currentToken = lexer->getNextToken();

    if(currentToken.tokenType != TOK_Identifier){
        throw runtime_error("Unexpected token on line " + to_string(currentToken.lineNumber) + ": expected identifier after def keyword.");
    }

    string identifier = currentToken.lexeme;
    currentToken = lexer->getNextToken();

    if(currentToken.tokenType != TOK_OpenParenthesis){
        throw runtime_error("Unexpected token on line " + to_string(currentToken.lineNumber) + ": expected '(' after identifier.");
    }

    currentToken = lexer->getNextToken();

    auto params = new vector<ASTIdentifierExpressionNode*>;

    if(currentToken.tokenType != TOK_CloseParenthesis) {
        params = parseFormalParams();
    }

    currentToken = lexer->getNextToken();

    if(currentToken.tokenType != TOK_Colon){
        throw runtime_error("Unexpected token on line " + to_string(currentToken.lineNumber) + ": expected ':' after ')'.");
    }

    currentToken = lexer->getNextToken();

    if(currentToken.tokenType != TOK_LangType){
        throw runtime_error("Unexpected token on line " + to_string(currentToken.lineNumber) + ": expected variable type after ':'.");
    }

    TYPE type = getType(currentToken.lexeme);

    ASTBlockStatementNode* functionBody = parseBlock();

    return new ASTFunctionDeclarationStatementNode(identifier, *params, type, functionBody);
}

vector<ASTIdentifierExpressionNode*>* Parser::parseFormalParams(){
    auto params = new vector<ASTIdentifierExpressionNode*>;
    params->push_back(parseFormalParam());

    //If ',' follows, more parameters were passed
    while(lexer->getLookahead().tokenType == TOK_Comma){
        //Consume ','
        currentToken = lexer->getNextToken();
        //Get token identifier
        currentToken = lexer->getNextToken();
        params->push_back(parseFormalParam());
    }

    currentToken = lexer->getNextToken();

    if(currentToken.tokenType != TOK_CloseParenthesis){
        throw runtime_error("Unexpected token on line " + to_string(currentToken.lineNumber) + ": expected ')' after parameter list.");
    }

    return params;
}

ASTIdentifierExpressionNode* Parser::parseFormalParam(){
    if(currentToken.tokenType != TOK_Identifier){
        throw runtime_error("Unexpected token on line " + to_string(currentToken.lineNumber) + ": expected identifier.");
    }

    string identifier = currentToken.lexeme;
    currentToken = lexer->getNextToken();

    if(currentToken.tokenType != TOK_Colon){
        throw runtime_error("Unexpected token on line " + to_string(currentToken.lineNumber) + ": expected ':' after identifier.");
    }

    currentToken = lexer->getNextToken();

    if(currentToken.tokenType != TOK_LangType){
        throw runtime_error("Unexpected token on line " + to_string(currentToken.lineNumber) + ": expected variable type after ':'.");
    }

    TYPE type = getType(currentToken.lexeme);

    return new ASTIdentifierExpressionNode(identifier, type);
}