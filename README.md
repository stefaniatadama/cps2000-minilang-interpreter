# MiniLang Interpreter
[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)

This project involved writing a lexer, parser and interpreter in C++ for the programming language MiniLang, as part of the
requirements of the module [CPS2000: Compiler Theory and Practice](https://www.um.edu.mt/courses/studyunit/CPS2000). 

# MiniLang
MiniLang is an expression-based strongly-typed programming language. The language has C-style comments, that is, 
`//. . .` for line comments and `/*. . . */` for block comments. The language is case-sensitive
and each function is expected to return a value. MiniLang has 4 types: `real`, `int`, 
`bool` and `string`. Binary operators, such as ‘+’, require that the operands have matching types
and the language does not perform any implicit/automatic typecast.

The following is a syntactically and semantically correct MiniLang program:

    def funcSquare (x : real) : real {
      return x∗x;
    }

    def funcGreaterThan (x : real , y : real) : bool {
      var ans : bool = true;
      if (y > x) { set ans = false; }
      return ans;
    }

    var x : real = 2.4;
    var y : real = funcSquare(2.5);
    print y;                                            // 6.25
    print funcGreaterThan (x , 2.3) ;                   // true
    print funcGreaterThan (x , funcSquare(1.555)) ;     // false

MiniLang is defined by the following EBNF.

    <Letter>            ::= [A-Za-z]
    <Digit>             ::= [0-9]
    <Printable>         ::= [\x20-\x7E]
    <Type>              ::= ‘real’ | ‘int’ | ‘bool’ | ‘string’
    <BooleanLiteral>    ::= ‘true’ | ‘false’
    <IntegerLiteral>    ::= <Digit> { <Digit> }
    <RealLiteral>       ::= <Digit> { <Digit> } ‘.’ <Digit> { <Digit> }
    <StringLiteral>     ::= ‘"’ { <Printable> } ‘"’
    <Literal>           ::= <BooleanLiteral> 
                            | <IntegerLiteral> 
                            | <RealLiteral> 
                            | <StringLiteral>
    <Identifier>        ::= ( ‘ ’ | <Letter> ) { ‘ ’ | <Letter> | <Digit> }
    <MultiplicativeOp>  ::= ‘*’ | ‘/’ | ‘and’
    <AdditiveOp>        ::= ‘+’ | ‘-’ | ‘or’
    <RelationalOp>      ::= ‘<’ | ‘>’ | ‘==’ | ‘!=’ | ‘<=’ | ‘>=’
    <ActualParams>      ::= <Expression> { ‘,’ <Expression> }
    <FunctionCall>      ::= <Identifier> ‘(’ [ <ActualParams> ] ‘)’
    <SubExpression>     ::= ‘(’ <Expression> ‘)’
    <Unary>             ::= ( ‘-’ | ‘not’ ) <Expression>
    <Factor>            ::= <Literal> 
                            | <Identifier> 
                            | <FunctionCall> 
                            | <SubExpression> 
                            | <Unary>
    <Term>              ::= <Factor> { <MultiplicativeOp> <Factor> }
    <SimpleExpressioni  ::= <Term> { <AdditiveOp> <Term> }
    <Expression>        ::= <SimpleExpression> { <RelationalOp> <SimpleExpression> }
    <Assignment>        ::= ‘set’ <Identifier> ‘=’ <Expression>
    <VariableDecl>      ::= ‘var’ <Identifier> ‘:’ <Type> ‘=’ <Expression>
    <PrintStatement>    ::= ‘print’ <Expression>
    <ReturnStatement>   ::= ‘return’ <Expression>
    <IfStatement>       ::= ‘if’ ‘(’ <Expression> ‘)’ <Block> [ ‘else’ <Block> ]
    <WhileStatement>    ::= ‘while’ ‘(’ <Expression> ‘)’ <Block>
    <FormalParam>       ::= <Identifier> ‘:’ <Type>
    <FormalParams>      ::= <FormalParam> { ‘,’ <FormalParam> }
    <FunctionDecl>      ::= ‘def’ <Identifier> ‘(’ [ <FormalParams> ] ‘)’ ‘:’ <Type> <Block>
    <Statement>         ::= <VariableDecl> ‘;’ 
                            | <Assignment> ‘;’ 
                            | <PrintStatement> ‘;’ 
                            | <IfStatement> 
                            | <WhileStatement> 
                            | <ReturnStatement> ‘;’ 
                            | <FunctionDecl> ‘;’ 
                            | <Block>
    <Block>             ::= ‘{’ { <Statement> } ‘}’
    <Program>           ::= { <Statement> }



# Instructions
To use the MiniLang REPL, run the following commands in the root directory:

    cmake .
    make
    ./MiniLangI
