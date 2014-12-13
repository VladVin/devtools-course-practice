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
    std::string parseArgumentsAndTranslate(int argc, const char** argv);
    std::string Translate(std::string num_in,
                          std::string sys_in,
                          std::string sys_out);
    std::string message_;
};

#endif  // CODE_KOKOSHNIKOV_ALEXEY_INCLUDE_SIMPLECALCULATOR_APPLICATION_H_
