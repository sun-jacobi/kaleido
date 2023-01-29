
#include <string>

namespace Kaleidoscope {

enum Token {
    tok_eof = -1,
    tok_def = -2,
    tok_extern = -3,
    tok_id = -4,
    tok_num = -5,
}; 

class Lexer {
public:
    std::string IdentifierStr;  
    double NumVal;
    int LastChar;
    int gettok(); 
    Lexer();
    ~Lexer() = default;
};

} // namespace Kaleidoscope
