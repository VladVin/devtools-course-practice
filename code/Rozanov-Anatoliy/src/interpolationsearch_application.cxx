// Copyright 2014 Anatoliy Rozanov

#include "include/interpolationsearch.h"
#include "include/interpolationsearch_application.h"

#include <string>
#include <sstream>

SearchApplication::SearchApplication() : message_("") {}

void SearchApplication::help(const char* appname) {
    message_ += std::string("This is a interpolation search application.\n\n")
             + "Please provide arguments in the following format:\n"
             + " $ " + appname + " <search_element> <argument1>..<argumentN>\n"
             + "Where <search_element> is the element we need to find "
             + "and <argument1>...<argumentN> are array elements.\n";
}

int64_t parseInteger(const char* arg);
int64_t parseInteger(const char* arg) {
    char* end;
    int64_t value = strtol(arg, &end, 10);

    if (end[0]) {
        throw std::string("ERROR: Wrong number format!");
    }

    return value;
}

bool SearchApplication::parseArguments(int argc, const char** argv) {
    if (argc == 1) {
        help(argv[0]);
        return false;
    } else if (argc == 2) {
        message_ = "ERROR: Should be more than 1 arguments.\n\n";
        help(argv[0]);
        return false;
    }
    return true;
}

std::string SearchApplication::operator()(int argc, const char** argv) {
    bool returnCode = parseArguments(argc, argv);
    if (returnCode != true)
        return message_;

    int k;
    int n = argc - 2;
    int *mas = new int[n];;
    try {
        k = static_cast<int>(parseInteger(argv[1]));
        mas[0] = static_cast<int>(parseInteger(argv[2]));
        for (int i = 1; i < n; i++) {
            mas[i] = static_cast<int>(parseInteger(argv[i + 2]));
            if (mas[i] < mas[i - 1])
                return std::string("ERROR: Array should be sorted");
        }
    }
    catch(std::string str) {
        return str;
    }

    InterpolationSearch search;

    std::ostringstream stream;
    stream << "Result = ";

    int result = search.run(mas, n, k);
    if (result == -1) {
        message_ = "Element not found";
    } else {
        stream << result;
        message_ = stream.str();
    }

    return message_;
}
