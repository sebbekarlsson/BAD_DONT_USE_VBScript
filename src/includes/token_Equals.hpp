#ifndef TOKEN_EQUALS_H
#define TOKEN_EQUALS_H
#include "lex_Token.hpp"


class token_Equals: public Token {
    public:
        token_Equals();

        std::string execute();
};

#endif
