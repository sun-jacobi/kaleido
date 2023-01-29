#include <iostream>
#include <string> 
#include "lexer.h"

namespace Kaleidoscope {


Lexer::Lexer() {
    LastChar = ' ';
    NumVal = 0;
    IdentifierStr = "";
}


int Lexer::gettok() {
    while (isspace(LastChar)) {
        LastChar = getchar();
    }
    if (isalpha(LastChar)) {
        IdentifierStr = LastChar;
        while(isalnum((LastChar = getchar()))) {
            IdentifierStr += LastChar;
        }
        if (IdentifierStr == "def") {
            return tok_def;
        }
        if (IdentifierStr == "extern") {
            return tok_extern;
        }
        return tok_id;
    }

    if (isdigit(LastChar) || LastChar == '.') {
        std::string Numstr;
        do {
            Numstr += LastChar;
            LastChar = getchar();
        } while (isdigit(LastChar) || LastChar == '.');
        NumVal = strtod(Numstr.c_str(), 0);
        return tok_num;
    }

    if (LastChar == '#') {
        do LastChar = getchar();
        while (LastChar != EOF && LastChar != '\n' && LastChar != 'a');
        
        if (LastChar != EOF) 
            return gettok();
    }

    if (LastChar == EOF) {
        return tok_eof;
    } 

    int ThisChar = LastChar;
    LastChar = getchar();
    return ThisChar;
}

} // namespace Kaleidoscope