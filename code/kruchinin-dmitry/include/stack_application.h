// Copyright 2013 Dmitry Kruchinin

#ifndef CODE_KRUCHININ_DMITRY_INCLUDE_STACK_APPLICATION_H_
#define CODE_KRUCHININ_DMITRY_INCLUDE_STACK_APPLICATION_H_

#include <string>
#include "include/stack.h"

class StackApplication {
 public:
    StackApplication();
    void run();

 private:
    void help();
    bool parseCommand(Stack<int> *stack);
    bool get_int(const std::string &str,
                const char *exc_type, const char *exc_size,
                int &number);
};

#endif  // CODE_KRUCHININ_DMITRY_INCLUDE_STACK_APPLICATION_H_
