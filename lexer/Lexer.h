#ifndef ASSIGNMENT_LEXER_H
#define ASSIGNMENT_LEXER_H

#include <string>
#include <vector>
#include "Token.h"

#define ERR 22 //nehhi - biddel biex jigi tal-ahhar
#define BAD -1

using namespace std;

enum Classifier{
    DIGIT = 0,
    POINT = 1,
    ADDITIVE = 2,
    ASTERISK = 3,
    EQUAL = 4,
    LTGT = 5,
    EXCLAMATION = 6,
    UNDERSCORE = 7,
    PARENTHESIS = 8,
    PUNCTUATION = 9,
    QUOTES = 10,
    FORWARDSLASH = 11,
    NEWLINE = 12,
    ENDOFFILE = 13,
    LETTER = 14,
    PRINTABLE = 15
};

class Lexer{

    private:
        unsigned int currentPosition;
        string program;

        //Last entry is ERR
        bool isFinal[23] = {false, true, false, true, true, true, true, false, true, true, true, true, false,
                            true, true, true, true, false, true, false, false, true, false};
        int transitionTable[16][23] = {
            {1, 1, 3, 3, ERR, ERR, ERR, ERR, ERR, ERR, 10, ERR, 12, ERR, ERR, ERR, ERR, 17, ERR, 19, 19, ERR, ERR},
            {2, 3, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, 12, ERR, ERR, ERR, ERR, 17, ERR, 19, 19, ERR, ERR},
            {4, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, 12, ERR, ERR, ERR, ERR, 17, ERR, 19, 19, ERR, ERR},
            {8, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, 12, ERR, ERR, ERR, 19, 17, ERR, 20, 20, ERR, ERR},
            {5, ERR, ERR, ERR, ERR, 9, 9, 9, ERR, ERR, ERR, ERR, 12, ERR, ERR, ERR, ERR, 17, ERR, 19, 19, ERR, ERR},
            {6, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, 12, ERR, ERR, ERR, ERR, 17, ERR, 19, 19, ERR, ERR},
            {7, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, 12, ERR, ERR, ERR, ERR, 17, ERR, 19, 19, ERR, ERR},
            {10, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, 10, ERR, 12, ERR, ERR, ERR, ERR, 17, ERR, 19, 19, ERR, ERR},
            {13, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, 12, ERR, ERR, ERR, ERR, 17, ERR, 19, 19, ERR, ERR},
            {14, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, 12, ERR, ERR, ERR, ERR, 17, ERR, 19, 19, ERR, ERR},
            {12, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, 15, ERR, ERR, ERR, ERR, 17, ERR, 19, 19, ERR, ERR},
            {16, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, 12, ERR, ERR, ERR, 17, 17, ERR, 19, 21, ERR, ERR},
            {ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, 18, ERR, 19, 19, ERR, ERR},
            {11, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR},
            {10, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, 10, ERR, 12, ERR, ERR, ERR, ERR, 17, ERR, 19, 19, ERR, ERR},
            {ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, 12, ERR, ERR, ERR, ERR, 17, ERR, 19, 19, ERR, ERR}
        };

        unsigned int getLineNumber(int);
        Token nextToken(string&, int&);
        int delta(int, char);
        void tokenise();

    public:
        std::vector<Token> program_tokens;

        Lexer(string&);
        Token getNextToken();
        Token getLookahead();
};

#endif //ASSIGNMENT_LEXER_H