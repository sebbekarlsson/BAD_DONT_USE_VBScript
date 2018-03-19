#ifndef ARGUMENT_H
#define ARGUMENT_H

#include <iostream>
#include <string>


class Argument {
    public:
        bool is_func;
        bool is_math_op;
        bool is_concat;
        bool is_numeric;
        std::string argument;

        Argument(std::string argument);
};

#endif
