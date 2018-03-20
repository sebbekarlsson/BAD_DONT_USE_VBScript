
#ifndef LEX_FUNCTION_H
#define LEX_FUNCTION_H
#include <iostream>
#include <string>
#include <vector>


class Function {
    public:
        std::string name;
        std::vector<std::string> args;
    
        Function();

        virtual std::string execute() = 0;
};

#endif
