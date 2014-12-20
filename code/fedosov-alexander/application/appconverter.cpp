// Copyright 2014 Fedosov Alexander

#include <stdio.h>
#include <string>

#include "include/application.hpp"

int main(int argc, const char** argv) {
    Application app;
    std::string output = app(argc, argv);
    printf("%s\n", output.c_str());
    return 0;
}
