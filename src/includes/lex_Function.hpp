#ifndef LEX_FUNCTION_H
#define LEX_FUNCTION_H
#include <iostream>
#include <string>
#include <vector>


class Function {
    public:
        std::string name;
    
        Function();

        virtual std::string execute(std::vector<std::string> args) = 0;
};

#endif
