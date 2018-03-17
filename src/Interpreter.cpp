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
        std::vector<std::string> words;
        std::istringstream iss(line);
        std::string word;
        
        while(getline(iss, word, ' '))
            words.push_back(word);
        
        int args_count = 0;
        int word_count = 0;
        float math_value = 0.0f;
        bool math = false;

        for (std::vector<std::string>::const_iterator it = words.begin(); it != words.end(); it++) {
            std::string word = *it;
            std::string prev_word = words[std::max(0, word_count-1)];
            std::string next_word = words[std::min((int)words.size()-1, word_count+1)];

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

                bool is_math_op = InterpreterTools::is_math_operator(word);
                bool is_numeric = isdigit(word.at(0));
                bool is_prev_math_op = InterpreterTools::is_math_operator(prev_word);
                bool is_prev_numeric = isdigit(prev_word.at(0));

                if (!defining && !is_math_op) {
                    if (InterpreterTools::is_variable(word) && countcheck) {
                        word = memory->get_variable(word);
                    } else {
                        word = InterpreterTools::unquote(word);
                    }
                }
                
                if (is_prev_math_op) {
                    int argsindex = 0;
                    
                    if (assigning) {
                        argsindex = 2;
                    } else if (!assigning && !defining) {
                        argsindex = 0;
                    }

                    float basevalue = std::stof(args[argsindex]);
                    float currentvalue = std::stof(word);

                    if (prev_word == "+") {
                        std::string res = std::to_string(basevalue + currentvalue);
                        args[argsindex] = res;
                    } else if (prev_word == "-") {
                        std::string res = std::to_string(basevalue + currentvalue);
                        args[argsindex] = res;
                    } else if (prev_word == "*") {
                        std::string res = std::to_string(basevalue * currentvalue);
                        args[argsindex] = res;
                    } else if (prev_word == "Mod" || prev_word == "%") {
                        std::string res = std::to_string((int)basevalue % (int)currentvalue);
                        args[argsindex] = res;
                    }
                }

                args.push_back(word);
            }

            args_count++;
            word_count++;
        }

        if (token != nullptr) {
            last_output = token->execute(args);
        }

        token = nullptr;
        next_token = nullptr;
        args.clear();
        defining = false;
        assigning = false;
        args_limit = 0;
    }

    return contents;
};
