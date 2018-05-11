#include <vector>
#include "XMLGeneratorVisitor.h"

#include "../AST/ASTNode.h"
#include "../AST/ASTAssignmentStatementNode.h"
#include "../AST/ASTBinaryExpressionNode.h"
#include "../AST/ASTBlockStatementNode.h"
#include "../AST/ASTBoolLiteralExpressionNode.h"
#include "../AST/ASTDeclarationStatementNode.h"
#include "../AST/ASTFunctionCallExpressionNode.h"
#include "../AST/ASTFunctionDeclarationStatementNode.h"
#include "../AST/ASTIfStatementNode.h"
#include "../AST/ASTIntLiteralExpressionNode.h"
#include "../AST/ASTPrintStatementNode.h"
#include "../AST/ASTProgramNode.h"
#include "../AST/ASTRealLiteralExpressionNode.h"
#include "../AST/ASTReturnStatementNode.h"
#include "../AST/ASTStringLiteralExpressionNode.h"
#include "../AST/ASTUnaryExpressionNode.h"
#include "../AST/ASTWhileStatementNode.h"


void XMLGeneratorVisitor::visit(ASTProgramNode* node){
    output.open("program_ast.xml");

    //Setting current indent to 0
    currentIndent = 0;

    string prefix = setIndent();
    output << prefix << "<Program>" << endl;
    currentIndent++;

    for(int i=0; i<node->programStatements.size(); i++){
        node->programStatements[i]->accept(this);
    }

    currentIndent--;
    prefix = setIndent();
    output << prefix << "</Program>" << endl;

    output.close();
}

void XMLGeneratorVisitor::visit(ASTAssignmentStatementNode* node){
    string prefix = setIndent();
    output << prefix << "<Assignment>" << endl;
    currentIndent++;

    prefix = setIndent();
    output << prefix << "<Identifier>" << node->identifier->identifierName << "</Identifier>" << endl;

    currentIndent++;
    node->assignmentExpression->accept(this);
    currentIndent--;

    currentIndent--;
    prefix = setIndent();
    output << prefix << "</Assignment>" << endl;
}

void XMLGeneratorVisitor::visit(ASTBinaryExpressionNode* node){
    string prefix = setIndent();
    output << prefix << "<BinaryExpressionNode Op=\"" << xml_op(node->op) << "\">"<< endl;
    currentIndent++;

    node->left->accept(this);
    node->right->accept(this);

    currentIndent--;
    prefix = setIndent();
    output << prefix << "</BinaryExpressionNode>" << endl;
}

void XMLGeneratorVisitor::visit(ASTBoolLiteralExpressionNode* node){
    string prefix = setIndent();
    output << prefix << "<Bool>" << (bool)node->value << "</Bool>" << endl;
}

void XMLGeneratorVisitor::visit(ASTRealLiteralExpressionNode* node){
    string prefix = setIndent();
    output << prefix << "<Real>" << node->value << "</Real>" << endl;
}

void XMLGeneratorVisitor::visit(ASTIntLiteralExpressionNode* node){
    string prefix = setIndent();
    output << prefix << "<Int>" << node->value << "</Int>" << endl;
}

void XMLGeneratorVisitor::visit(ASTStringLiteralExpressionNode* node){
    string prefix = setIndent();
    output << prefix << "<String>" << node->value << "</String>" << endl;
}

void XMLGeneratorVisitor::visit(ASTIdentifierExpressionNode* node){
    string prefix = setIndent();

    //If we know the identifier type
    if(node->identifierType >= 0 && node->identifierType <= 3){
        output << prefix << "<Identifier Type=\"" << types[node->identifierType] << "\">" << node->identifierName
               << "</Identifier>" << endl;
    }

    //If we don't
    else{
        output << prefix << "<Identifier>" << node->identifierName << "</Identifier>" << endl;
    }
}

void XMLGeneratorVisitor::visit(ASTFunctionCallExpressionNode* node){
    string prefix = setIndent();
    output << prefix << "<FunctionCall Identifier=\"" << node->functionName << "\">" << endl;
    currentIndent++;

    for(int i=0; i<node->argumentList.size(); i++){
        node->argumentList[i]->accept(this);
    }

    currentIndent--;
    prefix = setIndent();
    output << prefix << "</FunctionCall>" <<endl;
}

void XMLGeneratorVisitor::visit(ASTDeclarationStatementNode* node){
    string prefix = setIndent();
    output << prefix << "<Declaration>" << endl;
    currentIndent++;

    prefix = setIndent();
    node->variableIdentifier->accept(this);

    node->variableExpression->accept(this);

    currentIndent--;
    prefix = setIndent();
    output << prefix << "</Declaration>" << endl;
}

void XMLGeneratorVisitor::visit(ASTFunctionDeclarationStatementNode* node){
    string prefix = setIndent();
    output << prefix << "<FunctionDeclaration Identifier=\"" << node->functionName << "\">" << endl;
    currentIndent++;

    for(int i=0; i<node->formalParams.size(); i++){
        node->formalParams[i]->accept(this);
    }

    node->functionBody->accept(this);

    currentIndent--;
    prefix = setIndent();
    output << prefix << "</FunctionDeclaration>" << endl;
}

void XMLGeneratorVisitor::visit(ASTIfStatementNode* node){
    string prefix = setIndent();
    output << prefix << "<If>" << endl;
    currentIndent++;

    node->conditionExpression->accept(this);
    node->ifBody->accept(this);

    if(node->elseBody)
        node->elseBody->accept(this);

    currentIndent--;
    prefix = setIndent();
    output << prefix << "</If>" << endl;
}

void XMLGeneratorVisitor::visit(ASTPrintStatementNode* node){
    string prefix = setIndent();
    output << prefix << "<Print>" << endl;
    currentIndent++;

    node->expressionToPrint->accept(this);

    currentIndent--;
    prefix = setIndent();
    output << prefix << "</Print>" << endl;
}

void XMLGeneratorVisitor::visit(ASTReturnStatementNode* node){
    string prefix = setIndent();
    output << prefix << "<Return>" << endl;
    currentIndent++;

    node->expressionToReturn->accept(this);

    currentIndent--;
    prefix = setIndent();
    output << prefix << "</Return>" << endl;
}

void XMLGeneratorVisitor::visit(ASTWhileStatementNode* node){
    string prefix = setIndent();
    output << prefix << "<While>" << endl;
    currentIndent++;

    node->conditionExpression->accept(this);
    node->whileBody->accept(this);

    currentIndent--;
    prefix = setIndent();
    output << prefix << "</While>" << endl;
}

void XMLGeneratorVisitor::visit(ASTBlockStatementNode* node){
    string prefix = setIndent();
    output << prefix << "<Block>" << endl;
    currentIndent++;

    for(int i=0; i<node->statements.size(); i++){
        node->statements[i]->accept(this);
    }

    currentIndent--;
    prefix = setIndent();
    output << prefix << "</Block>" << endl;
}

void XMLGeneratorVisitor::visit(ASTUnaryExpressionNode* node){
    string prefix = setIndent();
    output << prefix << "<Unary Op=\"" + node->op + "\">";
    currentIndent++;

    node->expressionNode->accept(this);

    currentIndent--;
    prefix = setIndent();
    output << prefix << "</Unary>" << endl;
}

//Adds as many indents as the value of currentIndent
string XMLGeneratorVisitor::setIndent(){
    string indent = "";

    for(int i=0; i<currentIndent; i++){
        indent += "\t";
    }

    return indent;
}

//Since < and > are constructs in XML, we define a function to represent them differently
string XMLGeneratorVisitor::xml_op(string op){
    if(op == ">")
        return "&gt;";
    if(op == "<")
        return "&lt;";
    if(op == ">=")
        return "&gt;=";
    if(op == "<=")
        return "&lt;=";
    return op;
}