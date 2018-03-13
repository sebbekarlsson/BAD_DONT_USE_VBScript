#include "includes/Interpreter.hpp"
#include "includes/tokens.hpp"
#include "includes/Memory.hpp"
#include <iostream>
#include <sstream>
#include <vector>
#include <string>


Interpreter::Interpreter() {};

Memory* memory = new Memory();

std::string Interpreter::eval(std::string contents) {

    std::istringstream f(contents);
    
    std::string line;
    std::string last_output;
    
    std::vector<std::string> args;
    
    Token* token;

    while (std::getline(f, line)) {
        std::istringstream iss(line);
        std::string word;
        int args_count = 0;

        while (getline(iss, word, ' ' )) {
            if (tokens.find(word) != tokens.end())
                token = tokens[word];

            if (args_count != 0)
                args.push_back(word);

            args_count++;
        }

        if (token != nullptr)
            last_output = token->execute(args);
        
        args.clear();
    }

    return contents;
};
