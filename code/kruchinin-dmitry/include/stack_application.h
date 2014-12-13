// Copyright 2014 Dmitry Kruchinin

#ifndef CODE_KRUCHININ_DMITRY_INCLUDE_STACK_APPLICATION_H_
#define CODE_KRUCHININ_DMITRY_INCLUDE_STACK_APPLICATION_H_

#include <string>
#include "include/stack.h"

class StackApplication {
 public:
    StackApplication();
    std::string operator()(int argc, char *argv[]);
 private:
    void parseCommand(int argc, char *argv[]);
    void help();

    std::string message;
};

#endif  // CODE_KRUCHININ_DMITRY_INCLUDE_STACK_APPLICATION_H_
