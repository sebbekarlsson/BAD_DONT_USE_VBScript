#include "includes/Interpreter.hpp"
#include "includes/tokens.hpp"
#include "includes/Memory.hpp"
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>


Interpreter::Interpreter() {};

Memory* memory = new Memory();

std::string Interpreter::eval(std::string contents) {

    std::istringstream f(contents);

    std::string line;
    std::string last_output;

    std::vector<std::string> args;

    Token* token;
    Token* next_token;

    bool defining = false;
    bool assigning = false;

    int args_limit = 0;

    while (std::getline(f, line)) {
        std::istringstream iss(line);
        std::string word;
        int args_count = 0;
        std::vector<std::string> words;

        while(getline(iss, word, ' '))
            words.push_back(word);

        for (std::vector<std::string>::const_iterator it = words.begin(); it != words.end(); it++) {
            std::string word = *it;
            std::string next_word = words[std::min((int)words.size()-1, 1)];

            if (tokens.find(word) != tokens.end())
                token = tokens[word];

            if (tokens.find(next_word) != tokens.end())
                next_token = tokens[next_word];

            if (token != nullptr)
                if (token->startname == "Dim")
                    defining = true;

            if (next_token != nullptr)
                if (next_token->startname == "=") {
                    assigning = true;
                    args_limit = -1;
                }

            if (args_count != args_limit) {
                bool countcheck = true;

                if (assigning)
                    countcheck = args_count != args_limit + 1;

                if (!defining) {
                    if (InterpreterTools::is_variable(word) && countcheck) {
                        word = memory->get_variable(word);
                    } else {
                        word = InterpreterTools::unquote(word);
                    }
                }

                args.push_back(word);
            }

            args_count++;
        }

        if (token != nullptr)
            last_output = token->execute(args);

        token = nullptr;
        next_token = nullptr;
        args.clear();
        defining = false;
        assigning = false;
        args_limit = 0;
    }

    return contents;
};
