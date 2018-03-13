#include "includes/InterpreterTools.hpp"
#include "includes/Memory.hpp"


extern Memory* memory;

bool InterpreterTools::is_variable(std::string argument) {
    return argument.find("\"") == std::string::npos &&
        argument.find("=") == std::string::npos &&
        !isdigit(argument.at(0));
};

std::string InterpreterTools::unquote(std::string argument) {
    argument.erase(
        std::remove(argument.begin(), argument.end(), '"'), argument.end()
    );

    return argument;
};
