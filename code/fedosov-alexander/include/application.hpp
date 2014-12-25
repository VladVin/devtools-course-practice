// Copyright 2014 Fedosov Alexander

#ifndef CODE_FEDOSOV_ALEXANDER_APPLICATION_APPLICATION_HPP_
#define CODE_FEDOSOV_ALEXANDER_APPLICATION_APPLICATION_HPP_
#include <string>
#include "lengthconverter.hpp"
class Application {
     public:
        Application();
        ~Application();
        std::string operator()(int argc, const char** argv);
    private:
        std::string message_;
        void help(const char* appname);
        void parseArgsAndConvert(int argc, const char** argv);
};
#endif
