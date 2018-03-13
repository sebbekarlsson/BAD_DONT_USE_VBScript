#ifndef LEX_TOKEN_H
#define LEX_TOKEN_H
#include <iostream>
#include <string>
#include <vector>


class Token {
    public:
        std::string startname;
        std::string endname;
    
        Token();

        virtual std::string execute(std::vector<std::string> args) = 0;
};

#endif
