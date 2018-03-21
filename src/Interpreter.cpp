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

/**
 * Evaluates a piece of code
 *
 * @param std::string contents
 *
 * @return std::string
 */
std::string Interpreter::eval(std::string contents) {

    std::istringstream f(contents);

    std::string line;
    std::string last_output;
    std::vector<std::string> argsstack; // arguments to be used with operator
    std::vector<std::string> operatorstack; // operators to be used with args
    std::vector<int> argscountstack;
    
    // iterating through each line
    while (std::getline(f, line)) {
        std::istringstream iss(line);
        std::string character;
        std::string next_character;
        std::string charbuffer = "";
        std::string prev_charbuffer = "";

        bool end_of_token = false;
        bool end_of_line = false;
        int charcount = 0;
        
        // iterating through each character
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
            
            // add the character to the charbuffer until we reach the end of -
            // the token.
            if (!end_of_token)
                charbuffer += character;

            // check if current is `=`,
            // push precvious token to args.
            //
            // so for example
            //
            // x = 2
            //
            // will become:
            //
            // =(x, 2)
            //
            // `=` will be used as a function call.
            if (character == "=") {
                argsstack.erase(argsstack.end()-1);
                argscountstack[argscountstack.size()-1] -= 1;
                argsstack.push_back(prev_charbuffer);
            }

            // if we have reached the end of the token or the line
            // then cleanup the charbuffer.
            //
            // push charbuffer to operatorstack if operator
            // else push charbuffer to argsstack
            //
            // we are basically separating arguments and tokens here.
            if (end_of_token || end_of_line) {
                InterpreterTools::str_replace(charbuffer, "(", "");
                InterpreterTools::str_replace(charbuffer, ")", "");

                if (!charbuffer.empty() && charbuffer != " ") {
                    if (tokens.find(charbuffer) != tokens.end() || functions.find(charbuffer) != functions.end()) {
                        operatorstack.push_back(charbuffer);

                        // make sure the count of arguments for the
                        // current operator starts at 0.
                        argscountstack.push_back(0);
                    } else {
                        argsstack.push_back(charbuffer);

                        // we received another argument, so lets increase the
                        // count of arguments for the current operator by 1.
                        argscountstack[argscountstack.size()-1] += 1;
                    }
                }
                
                // cleanup
                prev_charbuffer = charbuffer;
                charbuffer = "";
                end_of_token = false;
            }

            charcount++;
        }
    }

    // debug output
    std::cout << "<argsstack>" << std::endl;
    for (std::vector<std::string>::iterator it = argsstack.begin(); it != argsstack.end(); it++) {
        std::cout << *it << std::endl;
    }
    std::cout << "</argsstack>" << std::endl;
    
    // debug output
    std::cout << "<operatorstack>" << std::endl;
    for (std::vector<std::string>::iterator it = operatorstack.begin(); it != operatorstack.end(); it++) {
        std::cout << *it << std::endl;
    }
    std::cout << "</operatorstack>" << std::endl;
    
    int c = 0;
    std::string debug = ""; // only used for debug output printing
    int argsendpointer = 0;
    int argspos = 0;
    bool assigning = false;
    bool defining = false;
    Token* token = nullptr;
    Function* func = nullptr;
    for (std::vector<std::string>::iterator it = operatorstack.begin(); it != operatorstack.end(); it++) {
        
        // check if the current operator exists as a token
        token = nullptr;
        if (tokens.find(*it) != tokens.end()) {
            token = tokens[*it];
            token->args.clear();
        }

        // check if the current operator exists as a function
        func = nullptr;
        if (functions.find(*it) != functions.end()) {
            func = functions[*it];
            func->args.clear();
        }
        
        // this points to the last argument in argsstack for
        // the current operator
        argsendpointer = argspos + argscountstack[c];

        if (argspos != 0 && c != operatorstack.size() - 2)
            argsendpointer += 1;

        if (*it == "Dim")
            defining = true; // we know a definition is about to be done

        if (*it == "=")
            assigning = true; // we know an assignment is about to be done

        // debug output
        std::string out = *it + " - < begins at = (" + std::to_string(argspos) + ") , end at = ("+ std::to_string(argsendpointer) +")>";
        debug = "";

        // so lets collect each argument that belongs to the current operator.
        // we start at `argspos` and end at `argsendpointer`
        //
        // argspos = where the arguments starts for the current operator
        // argsendpointer = where the arguments ends for the current operator.
        int tokenargscount = 0;
        for (std::vector<std::string>::iterator it2 = argsstack.begin() + argspos; it2 != argsstack.end(); it2++) {
            if (argspos < argsendpointer) {
                std::string arg = *it2;
                
                // collect the variable value if the argument is a variable
                if (InterpreterTools::is_variable(arg) && !defining) {
                    if (!(assigning && tokenargscount == 0)) {
                        arg = memory->get_variable(arg);
                    }
                }

                debug += "," + arg; // just for debuging.
                
                // push argument into current token
                if (token != nullptr)
                    token->args.push_back(arg);

                // push argument into current function
                if (func != nullptr)
                    func->args.push_back(arg);
                
                tokenargscount++;
                argspos++;
            }
        }
        
        // debug output
        out += " | will call args: (" + debug + ")";
        std::cout << out << std::endl;
        
        if (token != nullptr)
            last_output = token->execute();

        if (func != nullptr)
            last_output = func->execute();

        // reset & cleanup
        assigning = false;
        defining = false;
        
        c++;
    }

    return contents;
};
