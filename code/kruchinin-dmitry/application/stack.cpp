// Copyright 2014 Dmitry Kruchinin

#include <string>
#include "include/stack_application.h"

int main(int argc, char *argv[]) {
    StackApplication app;
    std::string message = app(argc, argv);
    printf("%s\n", message.c_str());
    return 0;
}
