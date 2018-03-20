#include "includes/Argument.hpp"
#include "includes/tokens.hpp"
#include "includes/InterpreterTools.hpp"


Argument::Argument(std::string argument) {
    this->argument = argument;

    this->is_func = functions.find(argument) != functions.end();
    this->is_math_op = InterpreterTools::is_math_operator(argument);
    this->is_concat = argument == "&";
    this->is_numeric = isdigit(argument.at(0));
};
