#ifndef TOKEN_DIM_H
#define TOKEN_DIM_H
#include "lex_Token.hpp"


class token_Dim: public Token {
    public:
        token_Dim();

        std::string execute();
};

#endif
