#ifndef TOKENS_H
#define TOKENS_H
#include "token_Dim.hpp"
#include "token_Equals.hpp"
#include "token_Echo.hpp"
#include <iostream>
#include <vector>
#include <map>

static std::map<std::string, Token*> tokens = {
    {"Dim", new token_Dim()},
    {"=", new token_Equals()},
    {"Wscript.Echo", new token_Echo()}
};

#endif
