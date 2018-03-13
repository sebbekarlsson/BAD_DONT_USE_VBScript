#ifndef TOKEN_ECHO_H
#define TOKEN_ECHO_H
#include "lex_Token.hpp"


class token_Echo: public Token {
    public:
        token_Echo();

        std::string execute(std::vector<std::string> args);
};

#endif
