#include <map>
#include <memory>
#include "ast.hpp"

namespace Kaleidoscope {
class Parser {
    static int CurTok;
    static std::map<char, int> BinopPrec;
    static int getNextToken();
    //---------------------------------------------------------
    static std::unique_ptr<ExprAST> LogError(const char *Str);
    static std::unique_ptr<PrototypeAST> LogErrorP(const char *Str);
    //---------------------------------------------------------
    static int GetTokPrec();
    static void SetTokPrec();
    //---------------------------------------------------------
    static std::unique_ptr<ExprAST> ParseExpr();
    static std::unique_ptr<ExprAST> ParsePrimary();
    static std::unique_ptr<ExprAST> ParseBinOpRHS(int, std::unique_ptr<ExprAST>);
    //---------------------------------------------------------
    static std::unique_ptr<ExprAST> ParseNumberExpr();
    static std::unique_ptr<ExprAST> ParseParenExpr();
    static std::unique_ptr<ExprAST> ParseIdentifierExpr();
};

} // namespace Kaleidoscope