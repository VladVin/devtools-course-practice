// Copyright 2014 Anatoliy Rozanov

#ifndef CODE_ROZANOV_ANATOLIY_INCLUDE_INTERPOLATIONSEARCH_APPLICATION_H_
#define CODE_ROZANOV_ANATOLIY_INCLUDE_INTERPOLATIONSEARCH_APPLICATION_H_

#include <string>

class SearchApplication {
 public:
    SearchApplication();

    std::string operator()(int argc, const char** argv);

 private:
    std::string message_;

    void help(const char* appname);
    bool parseArguments(int argc, const char** argv);
};

#endif  // CODE_ROZANOV_ANATOLIY_INCLUDE_INTERPOLATIONSEARCH_APPLICATION_H_
