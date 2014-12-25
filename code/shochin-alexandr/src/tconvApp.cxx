// Copyright 2014 Shochin Alexandr

#include <stdio.h>
#include <string.h>
#include <string>
#include <sstream>

#include "include/tconv.h"
#include "include/tconvApp.h"

double parseDouble(const char* arg);
Unit parseUnit(const char* arg);

TConvApplication::TConvApplication() : message_("") {}

void TConvApplication::help(const char* appName, const char* message) {
    message_ =
             std::string(message) +
             std::string("This is a temperature convertor application.\n\n")
             + "Please provide arguments in the following format:\n\n"
             + " $ " + appName + " <argValue> <argFrom> <argIn>\n\n";
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
       throw std::string("Wrong unit format!");
     }
     return unit;
}

double parseDouble(const char* arg) {
    char* str;
    double value = strtod(arg, &str);
    if (!str[0]) {
    } else {
      throw std::string("Wrong number format!");
    }
    return value;
}

bool TConvApplication::Check(int argc, const char** argv) {
    if (argc == 1) {
        help(argv[0]);
        return false;
    } else if (argc != 4) {
        help(argv[0], "ERROR: Should be 3 arguments.\n\n");
        return false;
    }
    return true;
}

std::string TConvApplication::operator()(int argc, const char** argv) {
    Expression exp;
    std::ostringstream stream;
    if (Check(argc, argv) != 1) {
        return message_;
    }
    try {
         exp.argValue = static_cast<double>(parseDouble(argv[1]));
         exp.argFrom = static_cast<Unit>(parseUnit(argv[2]));
         exp.argIn = static_cast<Unit>(parseUnit(argv[3]));
    }
    catch(std::string str) {
         return str;
    }
    TemperatureConvertor temp;
    Temperature from, t;
    from.value = exp.argValue;
    from.unit = exp.argFrom;
    try {
        t.value = temp.Convert(from, exp.argIn);
        stream << "Result = ";
        stream << t.value;
    }
    catch(std::string str) {
        stream << str;
    }
    message_ = stream.str();
    return message_;
}
