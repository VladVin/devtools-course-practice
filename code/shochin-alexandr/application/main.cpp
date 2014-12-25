// Copyright 2014 Shochin Alexandr

#include <stdio.h>
#include <string>

#include "include/tconvApp.h"

int main(int argc, const char** argv) {
    TConvApplication app;
    std::string info = app(argc, argv);
    printf("%s\n", info.c_str());
    return 0;
}
