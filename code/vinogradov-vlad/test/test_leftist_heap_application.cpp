// Copyright 2014 Vlad Vinogradov

#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "include/leftistheap_application.h"

using ::testing::internal::RE;
using std::vector;
using std::string;

class AppTest : public ::testing::Test {
 protected:
    void Arrange(vector<string> args) {
        args_ = args;
    }
    void Act() {
        vector<const char*> params;
        params.push_back("appname");

        for (unsigned int i = 0; i < args_.size(); ++i) {
            params.push_back(args_[i].c_str());
        }
        int argc = static_cast<int>(params.size());
        const char** argv = &params.front();

        output_ = app_(argc, argv);
    }

    void Assert(string expected) {
        EXPECT_TRUE(RE::PartialMatch(output_, RE(expected)));
    }

    LeftistheapApplication app_;
    vector<string> args_;
    string output_;
};

TEST_F(AppTest, Do_Print_Help_Without_Arguments) {
    Arrange({});

    Act();

    Assert("This is a leftistheap application sample*");
}

TEST_F(AppTest, Can_Detect_Wrong_Arguments) {
    // Arrange
    Arrange({"123", "87hi"});

    Act();

    Assert("Parameters aren't valid values.");
}

TEST_F(AppTest, Can_Find_Min) {
    Arrange({"-1", "99", "-805", "1001"});

    Act();

    Assert("Min value = -805");
}
