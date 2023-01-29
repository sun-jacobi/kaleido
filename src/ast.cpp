#include "ast.h"


namespace Kaleidoscope {

NumExprAST::NumExprAST(double Val) : Val(Val) {}


VarExprAST::VarExprAST(std::string &Name) : Name(Name) {}


BinExprAST:: BinExprAST(char Op, std::unique_ptr<ExprAST> LHS, 
    std::unique_ptr<ExprAST> RHS)
     : Op(Op), LHS(std::move(LHS)), RHS(std::move(RHS)) {}
     

CallExprAST::CallExprAST(const std::string &Callee, 
     std::vector<std::unique_ptr<ExprAST>> Args)
    : Callee(Callee), Args(std::move(Args)) {}

PrototypeAST::PrototypeAST(const std::string &name, std::vector<std::string> Arg)
    : Name(name), Args(std::move(Args)) {}

const std::string& PrototypeAST::getName() const {
    return Name;
}

FuncAST::FuncAST(std::unique_ptr<PrototypeAST> Prote,
    std::unique_ptr<ExprAST> Body)
    : Proto(std::move(Proto)), Body(std::move(Body)) {}
} // Kaleidoscope


  


