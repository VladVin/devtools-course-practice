// Copyright 2014 Shochin Alexandr

#include <gtest/gtest.h>

#include <limits.h>
#include <string>

#include "include/tconvApp.h"

using ::testing::internal::RE;

class AppTest : public ::testing::Test {
 protected:
    void Act(int argc, const char* argv[]) {
        output_ = app_(argc, argv);
    }

    void Assert(std::string expected) {
        EXPECT_TRUE(RE::PartialMatch(output_, RE(expected)));
    }

    TConvApplication app_;
    std::string output_;
};

TEST_F(AppTest, Print_Help_Without_Arguments) {
    // Arrange
    int argc = 1;
    const char* argv[] = {"appName"};

    Act(argc, argv);

    Assert("This is a temperature convertor application\\..*");
}

TEST_F(AppTest, Check_Number_Of_Arguments) {
    // Arrange
    int argc = 3;
    const char* argv[] = {"appName", "20", "Celsius"};

    Act(argc, argv);

    Assert("ERROR: Should be 3 arguments\\..*");
}

TEST_F(AppTest, Detect_Wrong_Value_Format_for_Celsius) {
    // Arrange
    int argc = 4;
    const char* argv[] = {"appName", "-300", "Celsius", "Newton"};

    Act(argc, argv);

    Assert("ERROR!");
}

TEST_F(AppTest, Detect_Wrong_Value_Format_for_Kelvin) {
    // Arrange
    int argc = 4;
    const char* argv[] = {"appName", "-3", "Kelvin", "Newton"};

    Act(argc, argv);

    Assert("ERROR!");
}

TEST_F(AppTest, Detect_Wrong_Value_Format_for_Newton) {
    // Arrange
    int argc = 4;
    const char* argv[] = {"appName", "-100", "Newton", "Kelvin"};

    Act(argc, argv);

    Assert("ERROR!");
}

TEST_F(AppTest, Detect_Wrong_Value_Format_for_Fahrenheit) {
    // Arrange
    int argc = 4;
    const char* argv[] = {"appName", "-500", "Fahrenheit", "Newton"};

    Act(argc, argv);

    Assert("ERROR!");
}
TEST_F(AppTest, Detect_Wrong_oldUnit_Format) {
    // Arrange
    int argc = 4;
    const char* argv[] = {"appName", "50", "Unit", "Kelvin"};

    Act(argc, argv);

    Assert("ERROR!\\..*");
}

TEST_F(AppTest, Detect_Wrong_newUnit_Format) {
    // Arrange
    int argc = 4;
    const char* argv[] = {"appName", "50", "Celsius", "Unit"};

    Act(argc, argv);

    Assert("ERROR!\\..*");
}

TEST_F(AppTest, Convert_Correct_Value_Celsius_to_Kelvin) {
    // Arrange
    int argc = 4;
    const char* argv[] = {"appName", "50", "Celsius", "Kelvin"};

    Act(argc, argv);

    Assert("Result = 323.15");
}

TEST_F(AppTest, Convert_Correct_Value_Celsius_to_Fahrenheit) {
    // Arrange
    int argc = 4;
    const char* argv[] = {"appName", "50", "Celsius", "Fahrenheit"};

    Act(argc, argv);

    Assert("Result = 122.00");
}

TEST_F(AppTest, Convert_Correct_Value_Celsius_to_Newton) {
    // Arrange
    int argc = 4;
    const char* argv[] = {"appName", "50", "Celsius", "Newton"};

    Act(argc, argv);

    Assert("Result = 16.50");
}

TEST_F(AppTest, Convert_Correct_Value_Kelvin_to_Celsius) {
    // Arrange
    int argc = 4;
    const char* argv[] = {"appName", "50", "Kelvin", "Celsius"};

    Act(argc, argv);

    Assert("Result = -223.15");
}

TEST_F(AppTest, Convert_Correct_Value_Fahrenheit_to_Celsius) {
    // Arrange
    int argc = 4;
    const char* argv[] = {"appName", "50", "Fahrenheit", "Celsius"};

    Act(argc, argv);

    Assert("Result = 10.00");
}

TEST_F(AppTest, Convert_Correct_Value_Newton_to_Celsius) {
    // Arrange
    int argc = 4;
    const char* argv[] = {"appName", "50", "Newton", "Celsius"};

    Act(argc, argv);

    Assert("Result = 151.52");
}
