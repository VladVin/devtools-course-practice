// Copyright 2014 Shochin Alexandr

#include <gtest/gtest.h>

#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <iterator>

#include "include/tconvApp.h"

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
        starts.push_back("appName");

        for (size_t i = 0; i < args_.size(); ++i) {
            starts.push_back(args_[i].c_str());
        }
        const char** argv = &starts.front();
        int argc = static_cast<int>(args_.size()) + 1;

        output_ = app_(argc, argv);
    }

    void Assert(std::string expected) {
        EXPECT_TRUE(RE::PartialMatch(output_, RE(expected)));
    }

    TConvApplication app_;
    string output_;
    vector<string> args;
};

TEST_F(AppTest, Do_Print_Help_Without_Arguments) {
    Act(args);

    Assert("This is a temperature convertor application\\..*");
}

TEST_F(AppTest, Is_Checking_Number_Of_Arguments) {
    args = {"appName", "20", "Celsius"};

    Act(args);

    Assert("ERROR: Should be 3 arguments\\..*");
}

TEST_F(AppTest, Detect_Wrong_Value_Format_for_Celsius) {
    args = {"appName", "-300", "Celsius", "Newton"};

    Act(args);

    Assert("ERROR!");
}

TEST_F(AppTest, Detect_Wrong_Value_Format_for_Kelvin) {
    args = {"appName", "-3", "Kelvin", "Newton"};

    Act(args);

    Assert("ERROR!");
}

TEST_F(AppTest, Detect_Wrong_Value_Format_for_Newton) {
    args = {"appName", "-100", "Newton", "Kelvin"};

    Act(args);

    Assert("ERROR!");
}

TEST_F(AppTest, Detect_Wrong_Value_Format_for_Fahrenheit) {
    args = {"appName", "-500", "Fahrenheit", "Newton"};

    Act(args);

    Assert("ERROR!");
}

TEST_F(AppTest, Detect_Wrong_oldUnit_Format) {
    args = {"appName", "50", "Unit", "Kelvin"};

    Act(args);

    Assert("ERROR!\\..*");
}

TEST_F(AppTest, Detect_Wrong_newUnit_Format) {
    args = {"appName", "50", "Celsius", "Unit"};

    Act(args);

    Assert("ERROR!\\..*");
}

TEST_F(AppTest, Convert_Correct_Value_Celsius_to_Kelvin) {
    args = {"appName", "50", "Celsius", "Kelvin"};

    Act(args);

    Assert("Result = 323.15");
}

TEST_F(AppTest, Convert_Correct_Value_Celsius_to_Fahrenheit) {
    args = {"appName", "50", "Celsius", "Fahrenheit"};

    Act(args);

    Assert("Result = 122.00");
}

TEST_F(AppTest, Convert_Correct_Value_Celsius_to_Newton) {
    args = {"appName", "50", "Celsius", "Newton"};

    Act(args);

    Assert("Result = 16.50");
}

TEST_F(AppTest, Convert_Correct_Value_Kelvin_to_Celsius) {
    args = {"appName", "50", "Kelvin", "Celsius"};

    Act(args);

    Assert("Result = -223.15");
}

TEST_F(AppTest, Convert_Correct_Value_Fahrenheit_to_Celsius) {
    args = {"appName", "50", "Fahrenheit", "Celsius"};

    Act(args);

    Assert("Result = 10.00");
}

TEST_F(AppTest, Convert_Correct_Value_Newton_to_Celsius) {
    args = {"appName", "50", "Newton", "Celsius"};

    Act(args);

    Assert("Result = 151.52");
}
