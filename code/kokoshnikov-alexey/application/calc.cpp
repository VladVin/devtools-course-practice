// Copyright 2014 Alexey Kokoshnikov

#include <stdio.h>
#include <string>

#include "include/simplecalculator_application.h"

int main(int argc, const char** argv) {
    CalculatorApplication app;
    std::string output = app(argc, argv);
    printf("Empty App with parameters: %d, %s", argc, argv[0]);
    return 0;
}
