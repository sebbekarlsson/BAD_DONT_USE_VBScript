#include "includes/InterpreterTools.hpp"
#include "includes/Memory.hpp"


extern Memory* memory;

bool InterpreterTools::is_variable(std::string argument) {
    return argument.find("\"") == std::string::npos &&
        argument.find("=") == std::string::npos &&
        !isdigit(argument.at(0));
};

bool InterpreterTools::is_math_operator(std::string argument) {
    return argument == "+" ||
        argument == "-" ||
        argument == "*" ||
        argument == "/" ||
        argument == "%" ||
        argument == "^" ||
        argument == "Mod";
};

std::string InterpreterTools::unquote(std::string argument) {
    argument.erase(
        std::remove(argument.begin(), argument.end(), '"'), argument.end()
    );

    return argument;
};
