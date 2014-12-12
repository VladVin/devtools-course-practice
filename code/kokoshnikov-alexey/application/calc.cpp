// Copyright 2014 Alexey Kokoshnikov

#include <stdio.h>
#include <string>

#include "include/simplecalculator_application.h"

int main(int argc, const char** argv) {
    CalculatorApplication app;
    std::string output = app(argc, argv);
    printf("App with parameters: %d, %s\n Out: %s",
                                     argc, argv[0],
                                     output.c_str());
    return 0;
}
