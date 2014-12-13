// Copyright 2014 Vlad Vinogradov

#include <stdio.h>
#include <string>

#include "include/leftistheap_application.h"

int main(int argc, const char** argv) {
    LeftistheapApplication app;
    std::string output = app(argc, argv);
    printf("%s\n", output.c_str());
    return 0;
}
