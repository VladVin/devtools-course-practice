// Copyright 2014 Vlad Vinogradov

#ifndef CODE_VINOGRADOV_VLAD_INCLUDE_LEFTISTHEAP_APPLICATION_H_
#define CODE_VINOGRADOV_VLAD_INCLUDE_LEFTISTHEAP_APPLICATION_H_

#include <string>
#include <vector>

class LeftistheapApplication {
 public:
    LeftistheapApplication();

    std::string operator()(const int argc, const char** argv);

 private:
    std::string message_;

    void help(const std::string appName);
    bool parseAgruments(const int argc, const char** argv,
        std::vector<int>& numbers);
};

#endif  // CODE_VINOGRADOV_VLAD_INCLUDE_LEFTISTHEAP_APPLICATION_H_
