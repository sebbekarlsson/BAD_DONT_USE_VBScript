#include "includes/Interpreter.hpp"
#include "includes/tokens.hpp"
#include "includes/Memory.hpp"
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <math.h>


Interpreter::Interpreter() {};

Memory* memory = new Memory();

std::string Interpreter::eval(std::string contents) {

    std::istringstream f(contents);

    std::string line = "";
    std::string m_line = "";
    std::string last_output = "";

    std::vector<std::string> args;

    Token* token = nullptr;
    Token* next_token = nullptr;
    Function* func = nullptr;

    bool defining = false;
    bool assigning = false;

    int args_limit = 0;

    while (std::getline(f, line)) {
        m_line = line;

        InterpreterTools::str_replace(m_line, "(", " ");
        InterpreterTools::str_replace(m_line, ")", " ");

        std::vector<std::string> words;
        std::istringstream iss(m_line);
        std::string word;
        
        while(getline(iss, word, ' '))
            words.push_back(word);
        
        int args_count = 0;
        int word_count = 0;

        for (std::vector<std::string>::const_iterator it = words.begin(); it != words.end(); it++) {
            std::string word = *it;
            std::string prev_word = words[std::max(0, word_count-1)];
            std::string next_word = words[std::min((int)words.size()-1, word_count+1)];

            Argument* argument = new Argument(word);
            Argument* prev_argument = new Argument(prev_word);

            if (tokens.find(word) != tokens.end())
                token = tokens[word];

            if (tokens.find(next_word) != tokens.end())
                next_token = tokens[next_word];

            if (functions.find(word) != functions.end())
                func = functions[word];

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

                if (!defining && !argument->is_math_op && !argument->is_concat && !argument->is_func) {
                    if (InterpreterTools::is_variable(word) && countcheck) {
                        word = memory->get_variable(word);
                    } else {
                        word = InterpreterTools::unquote(word);
                    }
                }

                if (argument->is_func) {
                    std::vector<std::string> funcargs;
                    
                    for (int ii = word_count + 1; ii < words.size(); ii++) {
                        funcargs.push_back(InterpreterTools::unquote(words[ii]));
                    }

                    func = functions[word];
                    args[2] = func->execute(funcargs);
                }
                
                if (prev_argument->is_math_op || prev_argument->is_concat) {
                    int argsindex = 0;
                    
                    if (assigning) {
                        argsindex = 2;
                    } else if (!assigning && !defining) {
                        argsindex = 0;
                    }

                    float basevalue = 0.0f;
                    float currentvalue = 0.0f;

                    if (prev_argument->is_math_op) {
                        basevalue = std::stof(args[argsindex]);
                        currentvalue = std::stof(word);
                    }

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
                    } else if (prev_word == "/") {
                        std::string res = std::to_string(basevalue / currentvalue);
                        args[argsindex] = res;
                    } else if (prev_word == "^") {
                        std::string res = std::to_string(pow(basevalue, currentvalue));
                        args[argsindex] = res;
                    } else if (prev_word == "&") {
                        std::string res = args[argsindex] + word;
                        args[argsindex] = res;
                    }
                }

                args.push_back(word);
            }

            args_count++;
            word_count++;
            delete argument;
            delete prev_argument;
        }

        if (token != nullptr) {
            last_output = token->execute(args);
        }

        token = nullptr;
        next_token = nullptr;
        func = nullptr;
        args.clear();
        defining = false;
        assigning = false;
        args_limit = 0;
    }

    return last_output;
};
