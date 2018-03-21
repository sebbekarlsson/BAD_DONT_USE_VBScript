#include "includes/InterpreterTools.hpp"
#include "includes/Memory.hpp"


extern Memory* memory;

/**
 * Check if an argument is a variable
 *
 * @param std::string argument
 *
 * @return bool
 */
bool InterpreterTools::is_variable(std::string argument) {
    return argument.find("\"") == std::string::npos &&
        argument.find("=") == std::string::npos &&
        !isdigit(argument.at(0));
};

/**
 * Check if an argument is a mathematical operator
 *
 * @param std::string argument
 *
 * @return bool
 */
bool InterpreterTools::is_math_operator(std::string argument) {
    return argument == "+" ||
        argument == "-" ||
        argument == "*" ||
        argument == "/" ||
        argument == "%" ||
        argument == "^" ||
        argument == "Mod";
};

/**
 * Removes quotes from an argument
 *
 * @param std::string argument
 *
 * @return std::string
 */
std::string InterpreterTools::unquote(std::string argument) {
    argument.erase(
        std::remove(argument.begin(), argument.end(), '"'), argument.end()
    );

    return argument;
};

/**
 * Replace strings within another string
 *
 * @param std::string& subject
 * @param const std::string& search
 * @param const std::string& replace
 */
void InterpreterTools::str_replace(std::string& subject, const std::string& search, const std::string& replace) {
    size_t pos = 0;
    
    while((pos = subject.find(search, pos)) != std::string::npos) {
         subject.replace(pos, search.length(), replace);
         pos += replace.length();
    }
};
