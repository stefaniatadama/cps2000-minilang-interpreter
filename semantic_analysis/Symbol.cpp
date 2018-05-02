//
// Created by stefaniatadama on 30/04/2018.
//

#include "Symbol.h"

Symbol::Symbol(TYPE t, ASTExpressionNode* expr){
    type = t;
    value = expr;
    id = VARIABLE;
}

Symbol::Symbol(TYPE t, vector<ASTIdentifierExpressionNode*> p){
    type = t;
    params = p;
    id = FUNCTION;
}
