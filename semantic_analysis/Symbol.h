#ifndef ASSIGNMENT_SYMBOL_H
#define ASSIGNMENT_SYMBOL_H

#include<vector>
#include "../lexer/Token.h"
#include "../AST/ASTIdentifierExpressionNode.h"
#include "../AST/ASTFunctionDeclarationStatementNode.h"

using namespace std;

enum IDENTIFIER{
    VARIABLE, FUNCTION
};

//Encodes one entry from the symbol table
class Symbol {

    public:
        //Attributes holding the type of the identifier and the value it holds
        TYPE type;
        ASTExpressionNode* value;
        //Holds whether identifier is a variable or function name
        IDENTIFIER id;
        //Holds the parameters in case identifier is a function name
        vector<ASTIdentifierExpressionNode*> params;

        //Constructor for variables
        Symbol(TYPE, ASTExpressionNode*);
        //Constructor for functions
        Symbol(TYPE, vector<ASTIdentifierExpressionNode*>);
};


#endif //ASSIGNMENT_SYMBOL_H
