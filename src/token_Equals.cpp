#include "includes/token_Equals.hpp"
#include "includes/Memory.hpp"
#include <sstream>


extern Memory* memory;

token_Equals::token_Equals() : Token() {
    this->startname = "=";
};

std::string token_Equals::execute(std::vector<std::string> args) {
    if (args.size() < 1)
        return "";
    
    std::cout << "eq rec: " << args[0] << " = " << args[2] << std::endl;

    memory->define_variable(args[0], args[2]);

    return args[0];
};
