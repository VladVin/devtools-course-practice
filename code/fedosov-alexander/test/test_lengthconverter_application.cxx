// Copyright 2014 Fedosov Alexander

#include <gtest/gtest.h>

#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <iterator>
#include <sstream>

#include "include/application.hpp"

using ::testing::internal::RE;
using std::vector;
using std::string;

class AppTest : public ::testing::Test {
 protected:
    virtual void SetUp() {
        args.clear();
    }
    // virtual void TearDown() {}

    void Act(vector<string> args_) {
        vector<const char*> starts;
        starts.push_back("appname");

        for (size_t i = 0; i < args_.size(); ++i) {
            starts.push_back(args_[i].c_str());
        }
        const char** argv = &starts.front();
        int argc = static_cast<int>(args_.size()) + 1;

        output_ = app_(argc, argv);
    }

    void WrongAction(vector<string> args_) {
        vector<const char*> starts;
        starts.push_back("appname");

        for (size_t i = 0; i < args_.size(); ++i) {
            starts.push_back(args_[i].c_str());
        }
        const char** argv = &starts.front();
        int argc = static_cast<int>(args_.size()) + 1;
        app_(argc, argv);
    }

    void Assert(std::string expected) {
        EXPECT_TRUE(RE::PartialMatch(output_, RE(expected)));
    }
    void AssertOutput(const char* pattern, double result) {
        double val = 0.0;
        char* end = NULL;
        string strDouble = "";
        if (strstr(output_.c_str(), pattern) == NULL) {
            throw std::string("Wrong input!\n");
        }
        int i = 0;
        std::stringstream ssin(output_);
        while (ssin.good() && i < 4) {
        ssin >> strDouble;
        ++i;
    }
        val = strtod(strDouble.c_str(), &end);
        if (!end[0]) {
            EXPECT_NEAR(val, result, 0.01);
        } else {
            throw std::string("Wrong input!\n");
        }
    }

    Application app_;
    string output_;
    vector<string> args;
    const char* outputPattern = "Conversion result is ";
};

TEST_F(AppTest, Do_Print_Help_Without_Arguments) {
    Act(args);

    Assert("This is a simple length converter app\\..*");
}

TEST_F(AppTest, Check_Args_Correctness) {
    args = {"1", "2", "3", "4", "5"};

    EXPECT_THROW(WrongAction(args), std::string);
}

TEST_F(AppTest, Can_Detect_Wrong_Input1) {
    args = {"-from", "notype", "10.0", "-to", "yards"};

    EXPECT_THROW(WrongAction(args), std::string);
}

TEST_F(AppTest, Can_Detect_Wrong_Input2) {
    args = {"-from", "meters", "10.0", "-to", "notype"};

    EXPECT_THROW(WrongAction(args), std::string);
}

TEST_F(AppTest, Can_Detect_Wrong_Number_Format) {
    args = {"-from", "meters", "abc", "-to", "yards"};

    Act(args);

    Assert("Wrong input!\n");
}

TEST_F(AppTest, Can_Convert_Meters_To_Meters) {
    args = {"-from", "meters", "10", "-to", "meters"};

    Act(args);

    AssertOutput(outputPattern, 10);
}

TEST_F(AppTest, Can_Convert_Inches_To_Inches) {
    args = {"-from", "inches", "10", "-to", "inches"};

    Act(args);

    AssertOutput(outputPattern, 10);
}

TEST_F(AppTest, Can_Convert_Feet_To_Feet) {
    args = {"-from", "feet", "10", "-to", "feet"};

    Act(args);

    AssertOutput(outputPattern, 10);
}

TEST_F(AppTest, Can_Convert_Yards_To_Yards) {
    args = {"-from", "yards", "10", "-to", "yards"};

    Act(args);

    AssertOutput(outputPattern, 10);
}
TEST_F(AppTest, Can_Convert_Miles_To_Miles) {
    args = {"-from", "miles", "10", "-to", "miles"};

    Act(args);

    AssertOutput(outputPattern, 10);
}
