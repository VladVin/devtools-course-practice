// Copyright 2014 Anatoliy Rozanov

#include <stdio.h>
#include <string>

#include "include/interpolationsearch_application.h"

int main(int argc, const char** argv) {
    SearchApplication app;
    std::string output = app(argc, argv);
    printf("%s\n", output.c_str());
    return 0;
}
