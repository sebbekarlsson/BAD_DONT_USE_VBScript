#include "includes/token_Dim.hpp"


token_Dim::token_Dim() : Token() {

};

std::string token_Dim::execute(std::vector<std::string> args) {
    std::string varname = args[0];

    return varname;
};
