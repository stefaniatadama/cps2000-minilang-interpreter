#include "Token.h"

Token::Token() {}

Token::Token(TOKEN tok, string val, unsigned int lineNo){
    tokenType = tok;
    //stringTokenType = token_names[tok];
    lexeme = val;
    lineNumber = lineNo;
}