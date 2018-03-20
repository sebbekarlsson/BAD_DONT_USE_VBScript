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
            
            if (!end_of_token)
                charbuffer += character;
            
            if (end_of_token || charcount >= line.length() - 1) {
                InterpreterTools::str_replace(charbuffer, "(", "");
                InterpreterTools::str_replace(charbuffer, ")", "");

                if (!charbuffer.empty() && charbuffer != " ") {
                    if (tokens.find(charbuffer) != tokens.end()) {
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

    std::cout << "<operatorstack>" << std::endl;
    int c = 0;
    for (std::vector<std::string>::iterator it = operatorstack.begin(); it != operatorstack.end(); it++) {
        std::cout << *it << " <" << std::to_string(argscountstack[c]) << ">" << std::endl;
        c++;
    }

    return contents;
};
