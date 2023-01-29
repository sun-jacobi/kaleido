#include <map>
#include <memory>
#include "ast.h"
#include "lexer.h"



namespace Kaleidoscope {
class Parser {
public: 
    int CurTok;
    std::map<char, int> BinopPrec;
    std::unique_ptr<Lexer> lexer;
    Parser();
    ~Parser() = default;
    //---------------------------------------------------------
    int getNextToken();  
    //---------------------------------------------------------
    std::unique_ptr<ExprAST> LogError(const char *Str);
    std::unique_ptr<PrototypeAST> LogErrorP(const char *Str);
    //---------------------------------------------------------
    int GetTokPrec();
    void SetTokPrec();
    //---------------------------------------------------------
    std::unique_ptr<ExprAST> ParseExpr();
    std::unique_ptr<ExprAST> ParsePrimary();
    std::unique_ptr<ExprAST> ParseBinOpRHS(int, std::unique_ptr<ExprAST>);
    //---------------------------------------------------------
    std::unique_ptr<PrototypeAST> ParseProto();
    std::unique_ptr<FuncAST> ParseDef();
    std::unique_ptr<PrototypeAST> ParseExtern();
    std::unique_ptr<FuncAST> ParseTop();
    //---------------------------------------------------------
    std::unique_ptr<ExprAST> ParseNumberExpr();
    std::unique_ptr<ExprAST> ParseParenExpr();
    std::unique_ptr<ExprAST> ParseIdentifierExpr();
};

} // namespace Kaleidoscope


