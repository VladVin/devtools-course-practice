// Copyright 2014 Bykadorov Roman

#include <gtest/gtest.h>

#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <iterator>

#include "include/currencyconverter_application.h"
#include "include/currencyconverter.h"

using ::testing::internal::RE;
using std::vector;
using std::string;

class AppTest : public ::testing::Test {
 protected:
    virtual void SetUp() {
        args.clear();
    }

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

    ConverterApplication app_;
    string output_;
    vector<string> args;
};

TEST_F(AppTest, Do_Print_Help_Without_Arguments) {
    Act(args);

    Assert("This is a simple currency converter\\..*");
}

TEST_F(AppTest, Is_Checking_Number_Of_Arguments) {
    args = {"1", "2"};

    Act(args);

    Assert("ERROR: Should be 3 arguments\\..*");
}

TEST_F(AppTest, Can_Detect_Wrong_Value_Format) {
    args = {"1", "2", "wrong"};

    Act(args);

    Assert("Wrong value format!.*");
}

TEST_F(AppTest, Can_Detect_Wrong_Currency_Format) {
    args = {"1", "wrong", "1"};

    Act(args);

    Assert("Wrong currency format!.*");
}

TEST_F(AppTest, Can_Convert_From_One_Currency_To_Same_Currency) {
    args = {"1", "1", "2"};

    Act(args);

    Assert("Result = 2");
}

TEST_F(AppTest, Can_Convert_From_One_Currency_To_USD) {
    std::ostringstream usdStream;
    usdStream << usdForRub;
    std::string usd = usdStream.str();
    args = {"3", "1", usd};

    Act(args);

    Assert("Result = 1");
}

TEST_F(AppTest, Can_Convert_Large_Negative_Values) {
    std::ostringstream usdToEurStream;
    usdToEurStream << "Result = " <<
        -300000*usdForRub/eurForRub;
    std::string usdToEur = usdToEurStream.str();
    args = {"1", "2", "-300000"};

    Act(args);

    Assert(usdToEur);
}

