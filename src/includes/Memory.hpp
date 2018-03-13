#ifndef MEMORY_H
#define MEMORY_H
#include <iostream>
#include <string>
#include <vector>
#include <map>


class Memory {
    public:
        std::map<std::string, std::string> variables;
        std::map<std::string, std::string> functions;

        Memory();

        void define_variable(std::string varname, std::string varvalue);
        
        std::string get_variable(std::string varname);
};

#endif
