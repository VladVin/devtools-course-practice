// Copyright 2014 Vlad Vinogradov

#include "include/leftistheap.h"
#include "include/leftistheap_application.h"

#include <cstdlib>
#include <string>
#include <vector>
#include <sstream>

LeftistheapApplication::LeftistheapApplication() : message_("") {}

void LeftistheapApplication::help(const std::string appName) {
    message_ += std::string("This is a leftistheap application sample.\n")
             + "usage: " + appName + " <number1>...\n"
             "Where numberI is integer number\n";
}

int64_t parseInteger(const char* arg);
int64_t parseInteger(const char* arg) {
    char* endptr;
    int64_t value = strtol(arg, &endptr, 10);

    if (endptr[0]) {
        throw "Parameters aren't valid values";
    }

    return value;
}

bool LeftistheapApplication::parseAgruments(const int argc,
    const char** argv, std::vector<int>& numbers) {
    if (argc == 1) {
        help(std::string(argv[0]));
        return false;
    }

    numbers.clear();
    try {
        for (int i = 1; i < argc; ++i) {
            numbers.push_back(static_cast<int>(parseInteger(argv[i])));
        }
    }
    catch(std::string str) {
        message_ = str;
        return false;
    }

    return true;
}

std::string LeftistheapApplication::operator()(const int argc,
    const char** argv) {
    std::vector<int> numbers;
    bool errCode = parseAgruments(argc, argv, numbers);
    if (errCode == false) {
        return message_;
    }

    LeftistHeap heap;
    for (unsigned int i = 0; i < numbers.size(); ++i) {
        heap.insert(numbers[i]);
    }

    std::ostringstream stream;
    stream << "Min value = ";
    stream << heap.findMin();

    message_ = stream.str();

    return message_;
}
