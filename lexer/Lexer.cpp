//
// Created by stefa on 08/03/2018.
//

#include <stack>
#include <stdexcept>

#include "Lexer.h"

Token Lexer::nextToken(string &program){

    int state = s0;
    string lexeme = "";
    unsigned int i = 0;
    char currentChar;
    stack <int> stack;
    stack.push(sBad);

    while(state != ERR){
        currentChar = program.at(i);
        lexeme += currentChar;

        if(isFinal[state]){
            while(!stack.empty()){
                stack.pop();
            }
        }

        stack.push(state);
        state = delta(state, currentChar);

        i++;
    }

    while(!isFinal[state] && state != BAD){
        state = stack.top();
        stack.pop();

        lexeme.pop_back();
    }

    if(isFinal[state]){
        return Token(TOK_Number, lexeme);
    }

    else{
        throw invalid_argument("Syntax error.");
    }
}

int Lexer::delta(int state, char c) {

    int classifier;

    switch(c) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            classifier = DIGIT; //nehhi - refer to Lexer.h enum
            break;
        default:
            classifier = OTHER;
    }

    return transitionTable[classifier][state];
}
