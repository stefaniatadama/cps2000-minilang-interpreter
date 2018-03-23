//
// Created by stefa on 08/03/2018.
//

#ifndef ASSIGNMENT_LEXER_H
#define ASSIGNMENT_LEXER_H

#include <string>
#include "Token.h"

#define ERR 2
#define BAD -1

using namespace std;

enum Classifier{
    DIGIT = 0,
    OTHER = 1 //nehhi - biddel biex jigi tal-ahhar
};

class Lexer{

    private:
        int s0 = 0;
        int s1 = 1;
        int sErr = ERR;
        int sBad = BAD;

        //s0 is not final, s1 is final, ERR is not final
        bool isFinal[3] = {false, true, false};

        int transitionTable[2][2] = {
            {s1, s1},
            {sErr, sErr}
        };

    public:
        Token nextToken(string&);
        int delta(int, char);
};

#endif //ASSIGNMENT_LEXER_H