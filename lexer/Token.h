#ifndef ASSIGNMENT_TOKEN_H
#define ASSIGNMENT_TOKEN_H

#include <string>
using namespace std;

enum TOKEN {
    TOK_IntLiteral, TOK_FloatLiteral, TOK_AdditiveOp, TOK_MultiplicativeOp,
    TOK_Equals, TOK_RelOp, TOK_LangType, TOK_If, TOK_Else, TOK_While,
    TOK_Def, TOK_Return, TOK_Set, TOK_Var, TOK_Print, TOK_And, TOK_Or, TOK_Not,
    TOK_Boolean, TOK_Identifier, TOK_EOF, TOK_String, TOK_OpenScope,
    TOK_CloseScope, TOK_OpenParenthesis, TOK_CloseParenthesis, TOK_Delimeter,
    TOK_Colon, TOK_Comma, TOK_Comment
};

class Token {

    public:

        //Used for testing
        /* string token_names[30] = {"TOK_IntLiteral", "TOK_FloatLiteral", "TOK_AdditiveOp", "TOK_MultiplicativeOp",
                              "TOK_Equals", "TOK_RelOp", "TOK_LangType", "TOK_If", "TOK_Else", "TOK_While",
                              "TOK_Def", "TOK_Return", "TOK_Set", "TOK_Var", "TOK_Print", "TOK_And", "TOK_Or",
                              "TOK_Not", "TOK_Boolean", "TOK_Identifier", "TOK_EOF", "TOK_String", "TOK_OpenScope",
                              "TOK_CloseScope", "TOK_OpenParenthesis", "TOK_CloseParenthesis", "TOK_Delimeter",
                              "TOK_Colon", "TOK_Comma", "TOK_Comment"}; */
        TOKEN tokenType;
        string stringTokenType; //Used for testing
        string lexeme;
        unsigned int lineNumber;

        Token(TOKEN, string, unsigned int);

    Token();
};


#endif //ASSIGNMENT_TOKEN_H
