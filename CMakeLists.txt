cmake_minimum_required(VERSION 3.9)
project(Assignment)

set(CMAKE_CXX_STANDARD 11)

add_executable(Assignment main.cpp lexer/Lexer.h lexer/Lexer.cpp lexer/Token.cpp lexer/Token.h)