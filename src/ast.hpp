#include <string>
#include <vector>
#include <memory>

namespace Kaleidoscope{
class ExprAST {
public :
    ExprAST() = default;
    virtual ~ExprAST() = default;
};
class NumExprAST : public ExprAST {
    double Val;

public : 
    NumExprAST(double);
};

class VarExprAST : public ExprAST {
    std::string Name;
public:
    VarExprAST(std::string&);
};

class BinExprAST : public ExprAST {
    char Op;
    std::unique_ptr<ExprAST> LHS, RHS;
public: 
    BinExprAST(char,std::unique_ptr<ExprAST>,
    std::unique_ptr<ExprAST>);
};

class CallExprAST : public ExprAST {
    std::string Callee;
    std::vector<std::unique_ptr<ExprAST>> Args;
public :
    CallExprAST(const std::string&, 
     std::vector<std::unique_ptr<ExprAST>>);
};

class PrototypeAST {
    std::string Name;
    std::vector<std::string> Args;
public :
    PrototypeAST(const std::string&, std::vector<std::string>);    
    const std::string &getName() const;
};


class FuncAST {
    std::unique_ptr<PrototypeAST> Proto;
    std::unique_ptr<ExprAST> Body;
public:
    FuncAST(std::unique_ptr<PrototypeAST>,
    std::unique_ptr<ExprAST>);
};

} // namespace Kaleidoscope




