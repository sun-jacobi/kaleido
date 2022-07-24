#include <cstdio>
#include <vector>
#include "parser.hpp"

namespace  Kaleidoscope {

    Parser::Parser():CurTok(0),BinopPrec() {
        lexer = std::make_unique<Lexer>();
        SetTokPrec();
    }
    //---------------------------------------------------------
    int Parser::getNextToken()  {
        return CurTok = lexer->gettok();
    }
    //---------------------------------------------------------
    std::unique_ptr<ExprAST> Parser::LogError(const char *Str) {
        fprintf(stderr, "LogError: %s\n", Str);
        return nullptr;
    }
    std::unique_ptr<PrototypeAST> Parser::LogErrorP(const char *Str) {
        LogError(Str);
        return nullptr;
    }
    //---------------------------------------------------------
    int Parser::GetTokPrec() {
        if (!isascii(CurTok)) {
            return -1;
        }
        int TokPrec = BinopPrec[CurTok];
        if (TokPrec <= 0) {
            return -1;
        }
        return TokPrec;
    }
    void Parser::SetTokPrec() {
        BinopPrec['<'] = 10;
        BinopPrec['+'] = 20;
        BinopPrec['-'] = 20;
        BinopPrec['*'] = 40;
        BinopPrec['%'] = 40;
        BinopPrec['/'] = 40; 
    }

    //---------------------------------------------------------
    std::unique_ptr<ExprAST> Parser::ParseExpr() {
        auto LHS = ParsePrimary();
        if (!LHS) {
            return nullptr;
        }
        return ParseBinOpRHS(0, std::move(LHS));
    }
    
    std::unique_ptr<ExprAST> Parser::ParsePrimary() {
        switch (CurTok) {
            case tok_id: 
                return ParseIdentifierExpr();
            case tok_num:
                return ParseNumberExpr();
            case '(': 
                return ParseParenExpr();
            default:
                fprintf(stderr, "%d\n", CurTok);
                return LogError("Error:unknown token when expecting an expression");
        }
    }
    std::unique_ptr<ExprAST> Parser::ParseBinOpRHS(int ExprPrec, 
                            std::unique_ptr<ExprAST> LHS) {
        while(1) {
            int TokPrec = GetTokPrec();
            if (TokPrec < ExprPrec) {
                return LHS;
            }
            int BinOp = CurTok;
            getNextToken();
            auto RHS = ParsePrimary();
            if (!RHS) {
                return nullptr;
            }
            int NextPrec = GetTokPrec();
            if (TokPrec < NextPrec) {
                RHS = ParseBinOpRHS(TokPrec + 1, std::move(RHS));
                if (!RHS) {
                    return nullptr;
                }
            } 
            LHS = std::make_unique<BinExprAST>(BinOp, std::move(LHS), std::move(RHS));
        }    
    }

    //---------------------------------------------------------

    std::unique_ptr<PrototypeAST>  Parser::ParseProto() {
        if (CurTok != tok_id) {
            return LogErrorP("Expected function name in prototype");
        }
        std::string FnName = lexer->IdentifierStr;
        getNextToken();
        if (CurTok != '(') {
            return LogErrorP("Expected '(' in prototype");
        }
        std::vector<std::string> Args;
        while(getNextToken() == tok_id) {
            Args.push_back(lexer->IdentifierStr);
        }
        if (CurTok != ')') {
            return LogErrorP("Expected ')' in prototype");
        }
        getNextToken();
        return std::make_unique<PrototypeAST>(FnName, std::move(Args));
        
    }
    
    std::unique_ptr<FuncAST> Parser::ParseDef() {
        getNextToken();
        auto Proto = ParseProto();
        if (!Proto) {
            return nullptr;
        }
        if (auto E = ParseExpr()) {
            return std::make_unique<FuncAST>(std::move(Proto), std::move(E));
        }
        return nullptr;
    }


    std::unique_ptr<PrototypeAST> Parser::ParseExtern() {
        getNextToken();
        return ParseProto();
    } 


    std::unique_ptr<FuncAST> Parser::ParseTop() {
        if (auto E = ParseExpr()) {
            auto Proto = std::make_unique<PrototypeAST>("", std::vector<std::string>());
            return std::make_unique<FuncAST>(std::move(Proto), std::move(E));
        }
        return nullptr;
    }

    //---------------------------------------------------------

    std::unique_ptr<ExprAST> Parser::ParseNumberExpr() {
        auto Result = std::make_unique<NumExprAST>(lexer->NumVal);
        getNextToken();
        return std::move(Result);
    }
    
    std::unique_ptr<ExprAST> Parser::ParseParenExpr() {
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

    std::unique_ptr<ExprAST> Parser::ParseIdentifierExpr() {
        std::string id = lexer->IdentifierStr;
        getNextToken();
        if (CurTok != '(') {
            return std::make_unique<VarExprAST>(id);
        }
        // Call 
        getNextToken();
        std::vector<std::unique_ptr<ExprAST>> Args;
        if (CurTok != ')') {
            while(1) {
                if (auto Arg = ParseExpr()) {
                    Args.push_back(std::move(Arg));
                } else {
                    return nullptr;
                }
                if (CurTok == ')') {
                    break;
                } 
                if (CurTok != ',') {
                    return LogError("Expected ')' or ',' in args list");
                }
                getNextToken();
            }      
        }
        getNextToken();
        return std::make_unique<CallExprAST>(id,std::move(Args));
    }

} // namespace Kaleidoscope



