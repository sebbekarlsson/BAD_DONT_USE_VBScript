#include "includes/function_Asc.hpp"
#include <sstream>
#include <iostream>


function_Asc::function_Asc() : Function() {
    this->name = "Asc";
};

std::string function_Asc::execute(std::vector<std::string> args) {
    if (args.size() < 1)
        return "";


    std::cout << "Asc received: " << args[0] << std::endl;

    if (isdigit(args[0].at(0))) {
        int numeric;
        numeric = std::stoi(args[0]);
        return std::to_string((char) numeric);
    } else {
        char ascii;
        ascii = args[0].at(0);
        return std::to_string((int) ascii);
    }
};
