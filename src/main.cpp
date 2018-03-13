#include <iostream>
#include <ResourceManager.h>
#include "includes/Interpreter.hpp"


int main (int argv, char** args) {
    ResourceManager::load(args[1]);

    Interpreter* interpreter = new Interpreter();
    interpreter->eval(ResourceManager::get(args[1]));

    return EXIT_SUCCESS;
}
