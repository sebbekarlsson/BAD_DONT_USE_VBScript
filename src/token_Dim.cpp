#include "includes/token_Dim.hpp"
#include "includes/Memory.hpp"


extern Memory* memory;

token_Dim::token_Dim() : Token() {

};

std::string token_Dim::execute(std::vector<std::string> args) {
    if (args.size() < 1)
        return "";
    
    std::string varname = args[0];

    memory->define_variable(varname, "");

    return varname;
};
