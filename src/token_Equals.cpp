#include "includes/token_Equals.hpp"
#include "includes/Memory.hpp"
#include <sstream>


extern Memory* memory;

token_Equals::token_Equals() : Token() {
    this->startname = "=";
};

std::string token_Equals::execute() {
    if (this->args.size() < 1)
        return "";
    
    memory->define_variable(args[0], args[1]);

    return args[0];
};
