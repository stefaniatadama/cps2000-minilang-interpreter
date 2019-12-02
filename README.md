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



# Instructions
To run the MiniLang REPL, run the following commands in the root directory:

    cmake .
    make
    ./MiniLangI
