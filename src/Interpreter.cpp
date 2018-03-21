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

    std::string line;
    std::string last_output;
    std::vector<std::string> argsstack; // arguments to be used with operator
    std::vector<std::string> operatorstack; // operators to be used with args
    std::vector<int> argscountstack;

    while (std::getline(f, line)) {
        std::istringstream iss(line);
        std::string character;
        std::string next_character;
        std::string charbuffer = "";
        std::string prev_charbuffer = "";

        bool end_of_token = false;
        bool end_of_line = false;
        int charcount = 0;
        
        for (
            std::string::iterator it = line.begin();
            it != line.end(); it++
        ) {
            character = *it;
            
            end_of_token = 
                character == " " ||
                character == "," ||
                character == "(";

            end_of_line = charcount >= line.length() - 1;
            
            if (!end_of_token)
                charbuffer += character;

            // note to self:
            // check if current is `=`,
            // push precvious token to args instead
            if (character == "=") {
                argsstack.erase(argsstack.end()-1);
                argscountstack[argscountstack.size()-1] -= 1;
                argsstack.push_back(prev_charbuffer);
            }

            if (end_of_token || end_of_line) {
                InterpreterTools::str_replace(charbuffer, "(", "");
                InterpreterTools::str_replace(charbuffer, ")", "");

                if (!charbuffer.empty() && charbuffer != " ") {
                    if (tokens.find(charbuffer) != tokens.end() || functions.find(charbuffer) != functions.end()) {
                        operatorstack.push_back(charbuffer);
                        argscountstack.push_back(0);
                    } else {
                        argsstack.push_back(charbuffer);
                        argscountstack[argscountstack.size()-1] += 1;
                    }
                }

                prev_charbuffer = charbuffer;
                charbuffer = "";
                end_of_token = false;
            }

            charcount++;
        }
    }

    std::cout << "<argsstack>" << std::endl;
    for (std::vector<std::string>::iterator it = argsstack.begin(); it != argsstack.end(); it++) {
        std::cout << *it << std::endl;
    }
    std::cout << "</argsstack>" << std::endl;
    
    std::cout << "<operatorstack>" << std::endl;
    for (std::vector<std::string>::iterator it = operatorstack.begin(); it != operatorstack.end(); it++) {
        std::cout << *it << std::endl;
    }
    std::cout << "</operatorstack>" << std::endl;
    
    int c = 0;
    std::string debug = "";
    int argsendpointer = 0;
    int argspos = 0;
    bool assigning = false;
    bool defining = false;
    Token* token = nullptr;
    Function* func = nullptr;
    for (std::vector<std::string>::iterator it = operatorstack.begin(); it != operatorstack.end(); it++) {
        
        token = nullptr; 
        if (tokens.find(*it) != tokens.end()) {
            token = tokens[*it];
            token->args.clear();
        }

        func = nullptr;
        if (functions.find(*it) != functions.end()) {
            func = functions[*it];
            func->args.clear();
        }
        
        argsendpointer = argspos + argscountstack[c];

        if (argspos != 0 && c != operatorstack.size() - 2)
            argsendpointer += 1;

        if (*it == "Dim")
            defining = true;
        if (*it == "=")
            assigning = true;

        std::string out = *it + " - < begins at = (" + std::to_string(argspos) + ") , end at = ("+ std::to_string(argsendpointer) +")>";

        debug = "";

        int tokenargscount = 0;
        for (std::vector<std::string>::iterator it2 = argsstack.begin() + argspos; it2 != argsstack.end(); it2++) {
            if (argspos < argsendpointer) {
                std::string arg = *it2;
                
                if (InterpreterTools::is_variable(arg) && !defining) {
                    if (!(assigning && tokenargscount == 0)) {
                        arg = memory->get_variable(arg);
                    }
                }

                debug += "," + arg;
                
                if (token != nullptr)
                    token->args.push_back(arg);

                if (func != nullptr)
                    func->args.push_back(arg);
                
                tokenargscount++;
                argspos++;
            }
        }

        out += " | will call args: (" + debug + ")";
        std::cout << out << std::endl;
        
        if (token != nullptr)
            last_output = token->execute();

        if (func != nullptr)
            last_output = func->execute();

        assigning = false;
        defining = false;
        
        c++;
    }

    return contents;
};
