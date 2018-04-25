#include "Token.h"

Token::Token() {}

Token::Token(TOKEN tok, string val){
    tokenType = tok;
    stringTokenType =  tokens[tok];
    lexeme = val;
}