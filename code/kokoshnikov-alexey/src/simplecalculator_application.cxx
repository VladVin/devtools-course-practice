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
    message_ = std::string("This is a simple calculator application.\n\n")
             + "Please provide arguments in the following format:\n\n"
             + "  $ " + appname + " < in number> <system1> <system2>\n\n"
             + "systems: 2, 8, 16."
             + "\n";
}

std::string CalculatorApplication::Translate(std::string num_in,
                                             std::string sys_in,
                                             std::string sys_out) {
    if ((sys_in != "2") && (sys_in != "8") && (sys_in != "16")) {
       return "Wrong system!";
    }
    if ((sys_out != "2") && (sys_out != "8") && (sys_out != "16")) {
       return "Wrong system!";
    }
    if (sys_in == sys_out) {
       return num_in;
    }
    SimpleCalculator calc;
    if (sys_in == "2") {
       if (sys_out == "8") {
           return calc.BinToOct(num_in);
       } else {
           return calc.BinToHex(num_in);
       }
    }
    if (sys_out == "2") {
       if (sys_in == "8") {
           return calc.OctToBin(num_in);
       } else {
           return calc.HexToBin(num_in);
       }
    }
    std::string tmp;
    if (sys_in == "8") {
       tmp = calc.OctToBin(num_in);
    } else {
       tmp = calc.HexToBin(num_in);
    }
    if (sys_out == "8") {
       return calc.BinToOct(tmp);
    } else {
       return calc.BinToHex(tmp);
    }
}

std::string CalculatorApplication::parseArgumentsAndTranslate(int argc,
                                                    const char** argv) {
    if (argc == 1) {
        help(argv[0]);
        return "NULL";
    } else if (argc != 4) {
        help(argv[0]);
        return "NULL";
    }

    try {
        std::string num_in = argv[1];
        std::string sys_in = argv[2];
        std::string sys_out = argv[3];
        return Translate(num_in, sys_in, sys_out);
    }
    catch(...) {
        message_ = "Wrong number format!\n";

        return "Wrong number format!\n";
    }
}


std::string CalculatorApplication::operator()(int argc, const char** argv) {
    std::string returnCode = parseArgumentsAndTranslate(argc, argv);
    if (returnCode == "NULL")
        return message_;

    return returnCode;
}
