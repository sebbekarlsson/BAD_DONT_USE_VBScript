#include "includes/token_Echo.hpp"
#include "includes/Memory.hpp"
#include <sstream>


extern Memory* memory;

token_Echo::token_Echo() : Token() {

};

std::string token_Echo::execute(std::vector<std::string> args) {
    if (args.size() < 1)
        return "";

    std::cout << args[0] << std::endl;

    return args[0];
};
