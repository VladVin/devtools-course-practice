// Copyright 2014 Shochin Alexandr

#ifndef CODE_SHOCHIN_ALEXANDR_INCLUDE_TCONVAPP_H_
#define CODE_SHOCHIN_ALEXANDR_INCLUDE_TCONVAPP_H_

#include <string>

#include "include/tconv.h"


#pragma pack(push, 1)
typedef struct {
    double argValue;
    Unit argFrom;
    Unit argIn;
} Expression;
#pragma pack(pop)

class TConvApplication {
 public:
    TConvApplication();
    std::string operator()(int argc, const char** argv);
 private:
    std::string message_;
    void help(const char* appName, const char* message = "");
    bool Check(int argc, const char** argv);
};

#endif  // CODE_SHOCHIN_ALEXANDR_INCLUDE_TCONVAPP_H_
