#include <iostream>
#include <string> 

enum Token {
    tok_eof = -1,

    tok_def = -2,
    tok_extern = -3,

    tok_id = -4,
    tok_num = -5,
};


static std::string IdentifierStr;

static double NumVal;

static int gettok() {
    static int LastChar = ' ';
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
        } while (isdigit(LastChar) || LastChar == ".");
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