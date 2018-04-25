#include <stack>
#include <stdexcept>
#include <iostream>
#include <vector>

#include "Lexer.h"

Lexer::Lexer(string &p){
    program = p;
    tokenise();
    currentPosition = 0;
}

Token Lexer::nextToken(string &program, int &position){

    int state = 0;
    string lexeme = "";
    int i = position;
    char currentChar;
    stack <int> stack;
    stack.push(BAD);

    //Handles whitespace and newline characters by incrementing i upon meeting one of them
    while(program.at(i) == ' ' || program.at(i) == '\n')
        i++;

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

    //We want to start again where we left off before we reached the error state
    i--;

    while(!isFinal[state] && state != BAD){
        state = stack.top();
        stack.pop();

        lexeme.pop_back();
    }

    if(isFinal[state]){
        //Setting position for the next time nextToken() is to be run
        position = i;

        switch(state){
            case 1:
                return Token(TOK_IntLiteral, lexeme);
            case 3:
                return Token(TOK_FloatLiteral, lexeme);
            case 4:
                return Token(TOK_AdditiveOp, lexeme);
            case 5:
                return Token(TOK_Equals, lexeme);
            case 6:
                return Token(TOK_RelOp, lexeme);
            case 8:
                return Token(TOK_MultiplicativeOp, lexeme);
            case 9:
                return Token(TOK_RelOp, lexeme);
            case 10:{
                if(lexeme == "real" || lexeme == "int" || lexeme == "bool" || lexeme == "string")
                    return Token(TOK_LangType, lexeme);

                else if(lexeme == "if")
                    return Token(TOK_If, lexeme);

                else if(lexeme == "else")
                    return Token(TOK_Else, lexeme);

                else if(lexeme == "while")
                    return Token(TOK_While, lexeme);

                else if(lexeme == "def")
                    return Token(TOK_Def, lexeme);

                else if(lexeme == "return")
                    return Token(TOK_Return, lexeme);

                else if(lexeme == "set")
                    return Token(TOK_Set, lexeme);

                else if(lexeme == "var")
                    return Token(TOK_Var, lexeme);

                else if(lexeme == "print")
                    return Token(TOK_Print, lexeme);

                else if(lexeme == "and")
                    return Token(TOK_And, lexeme);

                else if(lexeme == "or")
                    return Token(TOK_Or, lexeme);

                else if(lexeme == "not")
                    return Token(TOK_Not, lexeme);

                else if(lexeme == "true" || lexeme == "false")
                    return Token(TOK_Boolean, lexeme);

                //If none of the above, it must be a variable name
                else
                    return Token(TOK_Identifier, lexeme);
            }
            case 11:
                return Token(TOK_EOF, lexeme);
            case 13:{
                if(lexeme == "{")
                    return Token(TOK_OpenScope, lexeme);

                else if(lexeme == "}")
                    return Token(TOK_CloseScope, lexeme);

                else if(lexeme == "(")
                    return Token(TOK_OpenParenthesis, lexeme);

                else if(lexeme == ")")
                    return Token(TOK_CloseParenthesis, lexeme);
            }
            case 14:{
                if(lexeme == ";")
                    return Token(TOK_Delimeter, lexeme);

                else if(lexeme == ":")
                    return Token(TOK_Colon, lexeme);

                else if(lexeme == ",")
                    return Token(TOK_Comma, lexeme);
            }
            case 15:
                return Token(TOK_String, lexeme);
            case 16:
                return Token(TOK_MultiplicativeOp, lexeme);
            case 18:
                return Token(TOK_Comment, lexeme);
            case 21:
                return Token(TOK_Comment, lexeme);
        }
    }

    else{
        throw invalid_argument("Lexical error.");
    }
}

int Lexer::delta(int state, char c) {

    int classifier;

    switch(c){
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
        case '.':
            classifier = POINT;
            break;
        case '+':
        case '-':
            classifier = ADDITIVE;
            break;
        case '*':
            classifier = ASTERISK;
            break;
        case '=':
            classifier = EQUAL;
            break;
        case '<':
        case '>':
            classifier = LTGT;
            break;
        case '!':
            classifier = EXCLAMATION;
            break;
        case '_':
            classifier = UNDERSCORE;
            break;
        case '{':
        case '}':
        case '(':
        case ')':
            classifier = PARENTHESIS;
            break;
        case ':':
        case ';':
        case ',':
            classifier = PUNCTUATION;
            break;
        case '"':
            classifier = QUOTES;
            break;
        case '/':
            classifier = FORWARDSLASH;
            break;
        case '\n':
            classifier = NEWLINE;
            break;
        case EOF:
            classifier = ENDOFFILE;
            break;
        default:
            //If character is alphabetic
            if(isalpha(c)){
                classifier = LETTER;
            }
            //If character is between 20 and 126 (Hex 7E) in the ASCII table
            else if(c >= 20 && c <= 126){
                classifier = PRINTABLE;
            }
    }

    return transitionTable[classifier][state];
}

Token Lexer::getNextToken(){
    //Allows statements such as int /*hello*/ x = 3;
    while(program_tokens[currentPosition].tokenType == TOK_Comment)
        currentPosition++;

    cout << "Current token: " << program_tokens[currentPosition].stringTokenType << endl;
    return program_tokens[currentPosition++];
}

Token Lexer::getLookahead(){
    unsigned int temp = currentPosition;
    return program_tokens[++temp];
}

void Lexer::tokenise(){
    int position = 0;

    while(position < program.length()-1){
        program_tokens.push_back(nextToken(program, position));
    }

    //Manually adding EOF token
    string lexeme;
    lexeme = (char) EOF;
    program_tokens.push_back(Token(TOK_EOF, lexeme));
}