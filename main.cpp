#include <iostream>
#include <fstream>

#include "lexer/Lexer.h"
using namespace std;

int main() {

    ifstream inFile;
    inFile.open("../Program.txt");

    if (!inFile) {
        cerr << "Unable to open file Program.txt";
        exit(1);
    }

    std::cout << "Hello, World!" << std::endl; //nehhi

    string line, program;
    while(getline(inFile,line)){
        program.append(line + "\n");
    }

    cout << program << endl;

    Lexer lexer;
    cout << lexer.nextToken(program).value << endl;

    inFile.close();
    return 0;
}