// Copyright 2014 Shochin Alexandr

#include <stdio.h>
#include <string.h>
#include <string>

#include "include/tconv.h"
#include "include/tconvApp.h"

double parseDouble(const char* arg);
Unit parseUnit(const char* arg);

TConvApplication::TConvApplication() {}

void TConvApplication::help(const char* appName) {
    printf("This is a temperature convertor application.\n\n");
    printf("Please provide arguments in the following format:\n\n");
    printf("$ %s <argumentValue> <argumentFrom> <argumentIn>\n\n", appName);
    printf("Where both arguments are double numbers\n\n");
}

Unit parseUnit(const char* arg) {
     Unit unit;
     if (strcmp(arg, "Celsius") == 0) {
       unit = Celsius;
     } else if (strcmp(arg, "Kelvin") == 0) {
       unit = Kelvin;
     } else if (strcmp(arg, "Fahrenheit") == 0) {
       unit = Fahrenheit;
     } else if (strcmp(arg, "Newton") == 0) {
       unit = Newton;
     } else {
       throw "ERROR!";
     }
     return unit;
}

double parseDouble(const char* arg) {
    char* str;
    double value = strtod(arg, &str);
    if (!str[0]) {
    } else {
      throw "ERROR";
    }
    return value;
}

int TConvApplication::parseArg(int argc, const char** argv, Expression* exp) {
    if (argc == 1) {
        help(argv[0]);
        return 0;
    } else if (argc != 4) {
        printf("Should be 3 arguments.\n\n");
        help(argv[0]);
        return 0;
    }
    try {
         exp->argValue = static_cast<double>(parseDouble(argv[1]));
         exp->argFrom = static_cast<Unit>(parseUnit(argv[2]));
         exp->argIn = static_cast<Unit>(parseUnit(argv[3]));
    }
    catch(...) {
         printf("ERROR!");
         return 0;
    }
    return 1;
}

std::string TConvApplication::operator()(int argc, const char** argv) {
    Expression exp;
    if (parseArg(argc, argv, &exp) != 1) {
        return "ERROR!";
    }
    TemperatureConvertor temp;
    Temperature from, t;
    from.value = exp.argValue;
    from.unit = exp.argFrom;
    try {
        t.value = temp.Convert(from, exp.argIn);
        printf("Result = %f", t.value);
        return "";
    }
    catch(...) {
        return "ERROR!";
    }
}
