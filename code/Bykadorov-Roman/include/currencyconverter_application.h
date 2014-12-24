// Copyright 2014 Bykadorov Roman

#ifndef CODE_BYKADOROV_ROMAN_INCLUDE_CURRENCYCONVERTER_APPLICATION_H_
#define CODE_BYKADOROV_ROMAN_INCLUDE_CURRENCYCONVERTER_APPLICATION_H_

#include <string>

#pragma pack(push, 1)
typedef struct {
    int from;
    int to;
    double value;
} Expression;
#pragma pack(pop)

class ConverterApplication {
 public:
    ConverterApplication();
    std::string operator()(int argc, const char** argv);
 private:
    std::string message_;
    void help(const char* appname);
    bool parseArguments(int argc, const char** argv, Expression* expr);
};
#endif  // CODE_BYKADOROV_ROMAN_INCLUDE_CURRENCYCONVERTER_APPLICATION_H_

