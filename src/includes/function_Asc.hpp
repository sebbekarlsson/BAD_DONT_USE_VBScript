#ifndef FUNCTION_ASC_H
#define FUNCTION_ASC_H
#include "lex_Function.hpp"


class function_Asc: public Function {
    public:
        function_Asc();

        std::string execute(std::vector<std::string> args);
}; 

#endif
