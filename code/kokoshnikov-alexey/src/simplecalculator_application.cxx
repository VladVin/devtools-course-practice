// Copyright 2014 Alexey Kokoshnikov

#include "include/simplecalculator.h"
#include "include/simplecalculator_application.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <string>
#include <sstream>

CalculatorApplication::CalculatorApplication() : message_("") {}

void CalculatorApplication::help(const char* appname) {
    message_ += std::string("This is a simple calculator application.\n\n")
             + "Please provide arguments in the following format:\n\n"
             + "  $ " + appname + " < in number> <system1> <system2>\n\n"
             + "systems: 2, 8, 16."
             + "\n";
}

std::string CalculatorApplication::Translate(std::string num1,
                                             std::string sys1,
                                             std::string sys2) {
    if ((sys1 != "2") && (sys1 != "8") && (sys1 != "16")) {
       return "Wrong system!";
    }
    if ((sys2 != "2") && (sys2 != "8") && (sys2 != "16")) {
       return "Wrong system!";
    }
    if (sys1 == sys2) {
       return num1;
    }
    SimpleCalculator calc;
    if (sys1 == "2") {
       if (sys2 == "8") {
           return calc.BinToOct(num1);
       } else {
           return calc.BinToHex(num1);
       }
    }
    if (sys2 == "2") {
       if (sys1 == "8") {
           return calc.OctToBin(num1);
       } else {
           return calc.HexToBin(num1);
       }
    }
    std::string tmp;
    if (sys1 == "8") {
       tmp = calc.OctToBin(num1);
    } else {
       tmp = calc.HexToBin(num1);
    }
    if (sys2 == "8") {
       return calc.BinToOct(tmp);
    } else {
       return calc.BinToHex(tmp);
    }
}

std::string CalculatorApplication::parseArguments(int argc, const char** argv) {
    if (argc == 1) {
        help(argv[0]);
        return "NULL";
    } else if (argc != 4) {
        message_ = "ERROR: Should be 3 arguments.\n\n";
        help(argv[0]);
        return "NULL";
    }

    try {
        std::string num1 = argv[1];
        std::string sys1 = argv[2];
        std::string sys2 = argv[3];
        return Translate(num1, sys1, sys2);
    }
    catch(...) {
        message_ = "Wrong number format!\n";
        return "NULL";
    }
}


std::string CalculatorApplication::operator()(int argc, const char** argv) {
    std::string returnCode = parseArguments(argc, argv);
    if (returnCode == "NULL")
        return message_;

    std::ostringstream stream;
    stream << "Result = ";

    return returnCode;
}
