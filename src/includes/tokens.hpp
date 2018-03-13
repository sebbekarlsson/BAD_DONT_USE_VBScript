#ifndef TOKENS_H
#define TOKENS_H
#include "token_Dim.hpp"
#include <iostream>
#include <vector>
#include <map>

static std::map<std::string, Token*> tokens = {
    {"Dim", new token_Dim()}
};

#endif
