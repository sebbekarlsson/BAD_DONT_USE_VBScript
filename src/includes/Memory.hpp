#ifndef MEMORY_H
#define MEMORY_H
#include <iostream>
#include <string>
#include <vector>
#include <map>


class Memory {
    public:
        /**
         * holds a map of variables <varname> <varvalue>
         */
        std::map<std::string, std::string> variables;

        /**
         * holds a map of functions <functionname> <functioncode>
         */
        std::map<std::string, std::string> functions;

        /**
         * holds a map of objects <objectname> <object-json>
         */
        std::map<std::string, std::string> objects;

        Memory();

        void define_variable(std::string varname, std::string varvalue);
        
        std::string get_variable(std::string varname);
};

#endif
