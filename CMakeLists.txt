cmake_minimum_required(VERSION 3.9)
project(Assignment)

set(CMAKE_CXX_STANDARD 11)

add_executable(Assignment main.cpp lexer/Lexer.h lexer/Lexer.cpp lexer/Token.cpp lexer/Token.h parser/Parser.cpp parser/Parser.h AST/ASTNode.cpp AST/ASTNode.h AST/ASTExpressionNode.cpp AST/ASTExpressionNode.h AST/ASTStatementNode.cpp AST/ASTStatementNode.h AST/ASTBinaryExpessionNode.cpp AST/ASTBinaryExpessionNode.h AST/ASTDeclarationStatementNode.cpp AST/ASTDeclarationStatementNode.h AST/ASTLiteralExpressionNode.cpp AST/ASTLiteralExpressionNode.h AST/ASTRealLiteralExpressionNode.cpp AST/ASTRealLiteralExpressionNode.h AST/ASTIntLiteralExpressionNode.cpp AST/ASTIntLiteralExpressionNode.h AST/ASTBoolLiteralExpressionNode.cpp AST/ASTBoolLiteralExpressionNode.h AST/ASTStringLiteralExpressionNode.cpp AST/ASTStringLiteralExpressionNode.h AST/ASTFunctionCallExpressionNode.cpp AST/ASTFunctionCallExpressionNode.h AST/ASTIdentifierExpressionNode.cpp AST/ASTIdentifierExpressionNode.h)