#ifndef INTERPRETER_TOOLS_H
#define INTERPRETER_TOOLS_H
#include <iostream>
#include <algorithm>
#include <ctype.h>


namespace InterpreterTools {
    bool is_variable(std::string argument);
    bool is_math_operator(std::string argument);
    void str_replace(std::string& subject, const std::string& search, const std::string& replace);

    std::string unquote(std::string argument);
};

#endif
