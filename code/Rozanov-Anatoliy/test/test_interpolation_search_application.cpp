// Copyright 2014 Anatoliy Rozanov

#include <gtest/gtest.h>

#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <iterator>

#include "include/interpolationsearch_application.h"

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

    void Assert(std::string expected) {
        EXPECT_TRUE(RE::PartialMatch(output_, RE(expected)));
    }

    SearchApplication app_;
    string output_;
    vector<string> args;
};

TEST_F(AppTest, Do_Print_Help_Without_Arguments) {
    Act(args);

    Assert("This is a interpolation search application\\..*");
}

TEST_F(AppTest, Is_Checking_Number_Of_Arguments) {
    args = {"1"};

    Act(args);

    Assert("ERROR: Should be more than 1 arguments\\..*");
}

TEST_F(AppTest, Can_Detect_Wrong_Number_Format) {
    args = {"1", "pi", "2"};

    Act(args);

    Assert("ERROR: Wrong number format!.*");
}


TEST_F(AppTest, Can_Search) {
    args = {"2", "2", "3", "4", "5"};

    Act(args);

    Assert("Result = 0");
}

TEST_F(AppTest, Can_Search_When_Key_Not_Found) {
    args = {"-2", "1", "2", "3", "4"};

    Act(args);

    Assert("Element not found");
}

TEST_F(AppTest, Can_Detect_When_Array_Not_Sort) {
    args = {"-2", "2", "3", "1", "4"};

    Act(args);

    Assert("ERROR: Array should be sorted");
}
