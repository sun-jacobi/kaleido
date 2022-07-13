#include <memory>
#include <stdio.h>
#include "lexer.cpp"
#include "ast.hpp"


namespace  Kaleidoscope {

class Parser {
public:
    static int CurTok;

    static int getNextToken() {
        return gettok();
    }
    //---------------------------------------------------------
    static std::unique_ptr<ExprAST> LogError(const char *Str) {
        fprintf(stderr, "LogError: %s\n", Str);
        return nullptr;
    }
    static std::unique_ptr<PrototypeAST> LogErrorP(const char *Str) {
        LogError(Str);
        return nullptr;
    }
    //---------------------------------------------------------
    static std::unique_ptr<ExprAST> ParseExpr(); // TODO
    
    static std::unique_ptr<ExprAST> ParseNumberExpr() {
        auto Result = std::make_unique<NumExprAST>(NumVal);
        getNextToken();
        return std::move(Result);
    }
    

    static std::unique_ptr<ExprAST> ParseParenExpr() {
        getNextToken(); // ignore the '('  
        auto V = ParseExpr();
        if (!V) {
            return nullptr;
        }
        if (CurTok != ')') {
            return LogError("expected ')'");
        } 
        getNextToken();
        return V;
    }
    
    static std::unique_ptr<ExprAST> ParseIdentifierExpr() {
        std::string id = IdentifierStr;
        getNextToken();
        if (CurTok != '(') {
            return std::make_unique<VarExprAST>(id);
        }
        // TODO : implement the function call 
    }
};


} // namespace Kaleidoscope



