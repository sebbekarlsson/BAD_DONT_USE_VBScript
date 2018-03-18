#include "includes/function_Asc.hpp"
#include <sstream>
#include <iostream>


function_Asc::function_Asc() : Function() {
    this->name = "Dim";
};

std::string function_Asc::execute(std::vector<std::string> args) {
    if (args.size() < 1)
        return "";

    char ascii;
	int numeric;

    ascii = args[0].at(0);

	//cout << "Its ascii value is: " << (int) ascii << endl;
	//cout << "The ascii value of " << numeric << " is " << (char) numeric;
    
    return std::to_string((int) ascii);
};
