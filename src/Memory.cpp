#include "includes/Memory.hpp"


Memory::Memory() {};

void Memory::define_variable(std::string varname, std::string varvalue) {
    if (this->variables.find(varname) == variables.end()) {
        this->variables[varname] = varvalue;
    } else {
        this->variables[varname] = varvalue;
    }
};

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
