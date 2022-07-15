#include "parser.hpp"


namespace Kaleidoscope {
class Driver {
public:
    Parser parser;
    Driver();
    ~Driver() = default;
    void Run();
    void HandleDef();
    void HandleTop();
    void HandleExtern();
};
}