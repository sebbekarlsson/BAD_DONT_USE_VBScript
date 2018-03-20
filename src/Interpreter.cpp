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

    while (std::getline(f, line)) {
        std::istringstream iss(line);
        std::string character;
        std::string next_character;
        std::string charbuffer = "";
        std::string prev_charbuffer = "";
        std::vector<std::string> args;
        bool end_of_token = false;
        int charcount = 0;
        
        for (
            std::string::iterator it = line.begin();
            it != line.end(); it++
        ) {
            character = *it;
            
            charbuffer += character;

            end_of_token = charcount == line.size() - 1 ||
                character == " " ||
                character == "=" ||
                character == "," ||
                character == "\n" ||
                character == "\r\n" ||
                character == "(";

            if (character == "(") {
                // collect arguments inside function
                std::string lineleft = line.substr(charcount, line.rfind(")"));
                lineleft.erase(0, 1);
                lineleft.erase(lineleft.size() - 1);
                std::cout << lineleft << std::endl;
                this->eval(lineleft);
                break;
            }

            if (end_of_token) {
                // remove ending statement character
                charbuffer = charbuffer.substr(0, charbuffer.size()-1);
                InterpreterTools::str_replace(charbuffer, ")", "");

                if (!charbuffer.empty() && charbuffer != " ") {
                    args.push_back(charbuffer);
                }

                prev_charbuffer = charbuffer;
                charbuffer = "";
                end_of_token = false;
            }

            charcount++;
        }
    }

    return contents;
};
