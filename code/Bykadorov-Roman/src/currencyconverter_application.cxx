// Copyright 2014 Bykadorov Roman

#include "include/currencyconverter.h"
#include "include/currencyconverter_application.h"

#include <stdio.h>
#include <string.h>
#include <string>
#include <sstream>

ConverterApplication::ConverterApplication() : message_("") {}

void ConverterApplication::help(const char* appname) {
    message_ += std::string("This is a simple currency converter.\n\n")
             + "Please provide arguments in the following format:\n\n"
             + "  $ " + appname + " <from> <to> <value>\n\n"
             + "Where both <from> and <to> are one of dollar = 1, "
             + "euro = 2, ruble = 3, pound of sterling = 4, "
             + "japan yen = 5, norwegian krone = 6\n"
             + "<value> is double number.\n";
}

int64_t parseInteger(const char* arg);
int64_t parseInteger(const char* arg) {
    char* end;
    int64_t value = strtol(arg, &end, 10);

    if (!end[0]) {
    } else {
        throw "Wrong value format";
    }
    return value;
}

double parseDouble(const char* arg);
double parseDouble(const char* arg) {
    char* end;
    double value = strtod(arg, &end);

    if (!end[0]) {
    } else {
        throw "Wrong value format";
    }
    return value;
}

bool ConverterApplication::parseArguments(int argc, const char** argv,
    Expression* expression) {
    if (argc == 1) {
        help(argv[0]);
        return false;
    } else if (argc != 4) {
        message_ = "ERROR: Should be 3 arguments.\n\n";
        help(argv[0]);
        return false;
    }

    try {
        expression->from = static_cast<int>(parseInteger(argv[1]));
        expression->to = static_cast<int>(parseInteger(argv[2]));
    }
    catch(...) {
        message_ = "Wrong currency format!\n";
        return false;
    }
    try {
    expression->value = static_cast<double>(parseDouble(argv[3]));
    }
    catch(...) {
        message_ = "Wrong value format!\n";
        return false;
    }
    return true;
}

std::string ConverterApplication::operator()(int argc, const char** argv) {
    Expression expr;
    bool returnCode = parseArguments(argc, argv, &expr);
    if (returnCode != true)
        return message_;

    std::ostringstream stream;
    stream << "Result = ";
    stream << static_cast<double>(CurrencyConverter::convert(
        static_cast<CurrencyConverter::Currency>
            (expr.from),
        static_cast<CurrencyConverter::Currency>
            (expr.to),
        expr.value));

    message_ = stream.str();

    return message_;
}

