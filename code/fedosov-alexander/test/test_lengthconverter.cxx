// Copyright 2014 Fedosov Alexander
#include <gtest/gtest.h>
#include <float.h>
#include <cstdlib>
#include <string>
#include <map>
#include <utility>
#include "include/lengthconverter.hpp"

class lengthconverterTest : public ::testing::Test {
 protected:
    // NOTE: here you can put your init/deinit code
    // virtual void SetUp() {}
    // virtual void TearDown() {}
    LengthConverter converter;
    std::map<LengthConverter::Type, std::string> types = {
    {LengthConverter::TYPE_METER, "meters"},
    {LengthConverter::TYPE_INCH, "inches"},
    {LengthConverter::TYPE_FOOT, "feet"},
    {LengthConverter::TYPE_YARD, "yards"},
    {LengthConverter::TYPE_MILE, "miles"}
};
};

TEST_F(lengthconverterTest, conversion_test1) {
    EXPECT_NEAR(converter.convert(LengthConverter::TYPE_METER,
        100.0, LengthConverter::TYPE_INCH), 3937.01, 0.01);
}
TEST_F(lengthconverterTest, conversion_test2) {
    EXPECT_NEAR(converter.convert(LengthConverter::TYPE_METER,
        100.0, LengthConverter::TYPE_FOOT), 328.08, 0.01);
}
TEST_F(lengthconverterTest, conversion_test3) {
    EXPECT_NEAR(converter.convert(LengthConverter::TYPE_METER,
        100.0, LengthConverter::TYPE_YARD), 109.36, 0.01);
}
TEST_F(lengthconverterTest, conversion_test4) {
    EXPECT_NEAR(converter.convert(LengthConverter::TYPE_METER,
        100.0, LengthConverter::TYPE_MILE), 0.06214, 0.01);
}

TEST_F(lengthconverterTest, conversion_test5) {
    EXPECT_NEAR(converter.convert(LengthConverter::TYPE_INCH,
        100.0, LengthConverter::TYPE_METER), 2.54, 0.01);
}
TEST_F(lengthconverterTest, conversion_test6) {
    EXPECT_NEAR(converter.convert(LengthConverter::TYPE_INCH,
        100.0, LengthConverter::TYPE_FOOT), 8.33, 0.01);
}
TEST_F(lengthconverterTest, conversion_test7) {
    EXPECT_NEAR(converter.convert(LengthConverter::TYPE_INCH,
        100.0, LengthConverter::TYPE_YARD), 2.78, 0.01);
}
TEST_F(lengthconverterTest, conversion_test8) {
    EXPECT_NEAR(converter.convert(LengthConverter::TYPE_INCH,
        100.0, LengthConverter::TYPE_MILE), 0.0016, 0.01);
}

TEST_F(lengthconverterTest, conversion_test9) {
    EXPECT_NEAR(converter.convert(LengthConverter::TYPE_FOOT,
        100.0, LengthConverter::TYPE_METER), 30.48, 0.01);
}
TEST_F(lengthconverterTest, conversion_test10) {
    EXPECT_NEAR(converter.convert(LengthConverter::TYPE_FOOT,
        100.0, LengthConverter::TYPE_INCH), 1200.0, 0.01);
}
TEST_F(lengthconverterTest, conversion_test11) {
    EXPECT_NEAR(converter.convert(LengthConverter::TYPE_FOOT,
        100.0, LengthConverter::TYPE_YARD), 33.3333, 0.01);
}
TEST_F(lengthconverterTest, conversion_test12) {
    EXPECT_NEAR(converter.convert(LengthConverter::TYPE_FOOT,
        100.0, LengthConverter::TYPE_MILE), 0.019, 0.01);
}

TEST_F(lengthconverterTest, conversion_test13) {
    EXPECT_NEAR(converter.convert(LengthConverter::TYPE_YARD,
        100.0, LengthConverter::TYPE_METER), 91.44, 0.01);
}
TEST_F(lengthconverterTest, conversion_test14) {
    EXPECT_NEAR(converter.convert(LengthConverter::TYPE_YARD,
        100.0, LengthConverter::TYPE_INCH), 3600.00, 0.01);
}
TEST_F(lengthconverterTest, conversion_test15) {
    EXPECT_NEAR(converter.convert(LengthConverter::TYPE_YARD,
        100.0, LengthConverter::TYPE_FOOT), 300.0, 0.01);
}
TEST_F(lengthconverterTest, conversion_test16) {
    EXPECT_NEAR(converter.convert(LengthConverter::TYPE_YARD,
        100.0, LengthConverter::TYPE_MILE), 0.05682, 0.01);
}

TEST_F(lengthconverterTest, conversion_test17) {
    EXPECT_NEAR(converter.convert(LengthConverter::TYPE_MILE,
        100.0, LengthConverter::TYPE_METER), 160934.4, 0.01);
}
TEST_F(lengthconverterTest, conversion_test18) {
    EXPECT_NEAR(converter.convert(LengthConverter::TYPE_MILE,
        100.0, LengthConverter::TYPE_INCH), 6336000.0, 0.01);
}
TEST_F(lengthconverterTest, conversion_test19) {
    EXPECT_NEAR(converter.convert(LengthConverter::TYPE_MILE,
        100.0, LengthConverter::TYPE_FOOT), 528000.0, 0.01);
}
TEST_F(lengthconverterTest, conversion_test20) {
    EXPECT_NEAR(converter.convert(LengthConverter::TYPE_MILE,
        100.0, LengthConverter::TYPE_YARD), 176000.0, 0.01);
}

TEST_F(lengthconverterTest, conversion_test21) {
    EXPECT_THROW(converter.convert(LengthConverter::TYPE_MILE,
        -100.0, LengthConverter::TYPE_METER), std::string);
}

TEST_F(lengthconverterTest, conversion_test22) {
    EXPECT_NEAR(converter.convert(LengthConverter::TYPE_METER,
        100.0, LengthConverter::TYPE_METER), 100.0, 0.01);
}

TEST_F(lengthconverterTest, conversion_test23) {
    EXPECT_NEAR(converter.convert(LengthConverter::TYPE_MILE,
        100.0, LengthConverter::TYPE_MILE), 100.0, 0.01);
}

TEST_F(lengthconverterTest, typechecking_correct_test) {
    for (std::map<LengthConverter::Type, std::string>::iterator
        iter = types.begin(); iter != types.end(); ++iter) {
        EXPECT_EQ(converter.checkType(((*iter).second).c_str()),
            (*iter).first);
    }
}

TEST_F(lengthconverterTest, typechecking_wrong_test) {
     EXPECT_THROW(converter.checkType("wrongname"), std::string);
}
