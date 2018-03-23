//
// Created by stefaniatadama on 19/03/2018.
//

#ifndef ASSIGNMENT_TOKEN_H
#define ASSIGNMENT_TOKEN_H

#include <string>
using namespace std;

enum TOKEN {
    TOK_Number,
    TOK_ArithmeticOP,
    TOK_EOF
};

class Token {

    public:
        TOKEN type;
        string value;
        Token(TOKEN, string);
};


#endif //ASSIGNMENT_TOKEN_H
