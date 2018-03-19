#ifndef INTERPRETER_H
#define INTERPRETER_H
#include <iostream>
#include <vector>
#include <string>
#include "InterpreterTools.hpp"
#include "Argument.hpp"


class Interpreter {
    public:
        Interpreter();

        std::string eval(std::string contents);
};

#endif
