// Copyright 2014 Alexey Kokoshnikov

#include <gtest/gtest.h>

#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <iterator>

#include "include/simplecalculator_application.h"

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
        output_ =  app_(argc, argv);
    }

    void Assert(std::string expected) {
        EXPECT_TRUE(RE::PartialMatch(output_, RE(expected)));
    }

    CalculatorApplication app_;
    string output_;
    vector<string> args;
};

TEST_F(AppTest, Do_Print_Help_Without_Arguments) {
    Act(args);

    Assert("This is a simple calculator application\\..*");
}

TEST_F(AppTest, Is_Checking_Number_Of_Arguments) {
    args = {"1", "2"};

    Act(args);

    Assert("ERROR: Should be 3 arguments\\..*");
}

TEST_F(AppTest, Can_Detect_Wrong_System1_Format) {
    args = {"1", "3", "2"};
    Act(args);
    Assert("Wrong system\\.*");
}

TEST_F(AppTest, Can_Detect_Wrong_System2_Format) {
    args = {"1", "2", "3"};
    Act(args);
    Assert("Wrong system\\.*");
}

TEST_F(AppTest, Can_Detect_Wrong_Number_Format) {
    args = {"pi", "2", "8"};
    Act(args);
    Assert("Wrong number format\\.*");
}


TEST_F(AppTest, Can_No_Translate) {
    args = {"1", "2", "2"};

    Act(args);

    Assert("1");
}

TEST_F(AppTest, Can_Translate_From_Bin) {
    args = {"1", "2", "8"};

    Act(args);

    Assert("1");
}

TEST_F(AppTest, Can_Translate_From_Bin_2) {
    args = {"1", "2", "16"};

    Act(args);

    Assert("1");
}

TEST_F(AppTest, Can_Translate_To_Bin) {
    args = {"1", "8", "2"};

    Act(args);

    Assert("1");
}

TEST_F(AppTest, Can_Translate_To_Bin_2) {
    args = {"1", "16", "2"};

    Act(args);

    Assert("1");
}

TEST_F(AppTest, Can_Translate_Oct_To_Hex) {
    args = {"1", "8", "16"};

    Act(args);

    Assert("1");
}

TEST_F(AppTest, Can_Translate_Hex_To_Oct) {
    args = {"1", "16", "8"};

    Act(args);

    Assert("1");
}

