#include "includes/Memory.hpp"


Memory::Memory() {};

/**
 * Define a variable and put it in the RAM memory
 *
 * @param std::string varname
 * @param std::string varvalue
 */
void Memory::define_variable(std::string varname, std::string varvalue) {
    if (this->variables.find(varname) == variables.end()) {
        this->variables[varname] = varvalue;
    } else {
        this->variables[varname] = varvalue;
    }
};

/**
 * Fetch a variable from the RAM memory
 *
 * - will throw an error if the variable is not defined.
 *
 * @param std::string varname
 *
 * @return std::string
 */
std::string Memory::get_variable(std::string varname) {
    if (this->variables.count(varname) == 0) {
        std::cerr <<
            "[ERROR]: Trying to assign undeclared variable: " << varname <<
            " - Please use 'Dim'"
            << std::endl;
        exit(1);
    }

    return this->variables[varname];
};
