#ifndef TOKENS_H
#define TOKENS_H
#include "lex_Token.hpp"
#include "token_Dim.hpp"
#include "token_Equals.hpp"
#include "token_Echo.hpp"
#include "lex_Function.hpp"
#include "function_Asc.hpp"
#include <iostream>
#include <vector>
#include <map>

/**
 * Tokens that the interpreter is aware of
 */
static std::map<std::string, Token*> tokens = {
    {"Dim", new token_Dim()},
    {"=", new token_Equals()},
    {"Wscript.Echo", new token_Echo()}
};

/**
 * Functions that the interpreter is aware of
 */
static std::map<std::string, Function*> functions {
    {"Asc", new function_Asc()}
};

#endif
