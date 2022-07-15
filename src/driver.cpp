#include "driver.hpp"

namespace Kaleidoscope {
    Driver::Driver() : parser() {}
    void Driver::Run() {
        while(true) {
            fprintf(stderr, "kaleido>");
            switch(parser.CurTok) {
                case tok_eof:
                    return;
                case ';':
                    parser.getNextToken();
                    break;
                case tok_def:
                    HandleDef();
                    break;
                case tok_extern:
                    HandleExtern();
                    break;
                default:
                    HandleTop();
                    break;
            }
        }
    }
    void Driver::HandleDef() {
        if (parser.ParseDef()) {
            fprintf(stderr, "A Function");
        } else {
            parser.getNextToken();
        }
    }
    void Driver::HandleExtern() {
        if (parser.ParseExtern()) {
            fprintf(stderr, "A Prototype");
        } else {
            parser.getNextToken();
        }  
    }
    void Driver::HandleTop() {
        if (parser.ParseTop()) {
            fprintf(stderr, "A Top Level Expr");
        } else {
            parser.getNextToken();
        }  
    }

} // namespace Kaleidoscope
