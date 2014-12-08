// Copyright 2014 Bykadorov Roman

#include <cstdio>
#include <string>

#include "include/currencyconverter_application.h"

int main(int argc, const char** argv) {
    ConverterApplication app;
    std::string output = app(argc, argv);
    printf("%s\n", output.c_str());
    return 0;
}

