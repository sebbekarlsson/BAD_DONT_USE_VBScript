#include "includes/token_Dim.hpp"
#include "includes/Memory.hpp"
#include <sstream>


extern Memory* memory;

token_Dim::token_Dim() : Token() {

};

std::string token_Dim::execute(std::vector<std::string> args) {
    if (args.size() < 1)
        return "";

    std::string varname = "[";

    std::vector<std::string> realargs;

    for(std::vector<std::string>::const_iterator it = args.begin(); it != args.end(); ++it) {
        std::string a = *it;

        if (a.empty())
            continue;

        if (a.find(",") != std::string::npos) {
            std::istringstream iss(a);
            std::string word;

            while (getline(iss, word, ',')) {
                if (word.empty())
                    continue;

                realargs.push_back(word);
            }
        } else {
            realargs.push_back(a);
        }
    }

    for (std::vector<std::string>::const_iterator it = realargs.begin(); it != realargs.end();  ++it) {
        varname += *it + ",";
        memory->define_variable(*it, "");
    }

    return varname + "]";
};
