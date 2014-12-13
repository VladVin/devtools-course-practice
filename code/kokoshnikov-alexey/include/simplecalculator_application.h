// Copyright 2014 Alexey Kokoshnikov

#ifndef CODE_KOKOSHNIKOV_ALEXEY_INCLUDE_SIMPLECALCULATOR_APPLICATION_H_
#define CODE_KOKOSHNIKOV_ALEXEY_INCLUDE_SIMPLECALCULATOR_APPLICATION_H_

#include "include/simplecalculator.h"

#include <stdint.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <string>
#include <cstdlib>


class CalculatorApplication {
 public:
    CalculatorApplication();

    std::string operator()(int argc, const char** argv);
 private:
    void help(const char* appname);
    std::string parseArguments(int argc, const char** argv);
    std::string Translate(std::string num1, std::string sys1, std::string sys2);
    std::string message_;
};

#endif  // CODE_KOKOSHNIKOV_ALEXEY_INCLUDE_SIMPLECALCULATOR_APPLICATION_H_
