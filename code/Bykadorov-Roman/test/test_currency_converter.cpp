// Copyright 2014 Bykadorov Roman

#include <gtest/gtest.h>

#include <float.h>
#include <string>

#include "include/currencyconverter.h"

class ConverterTest : public ::testing::Test {
 protected:
    const double eps = 1e-5;
};

TEST_F(ConverterTest, can_Rub_To_Eur) {
    EXPECT_NEAR(1.0, CurrencyConverter::convert(CurrencyConverter::RUB,
        CurrencyConverter::EUR, 53.5948527), eps);
}

TEST_F(ConverterTest, can_Eur_To_Usd) {
    EXPECT_NEAR(53.5948527/42.2600685, CurrencyConverter::convert
        (CurrencyConverter::EUR, CurrencyConverter::USD, 1.0), eps);
}

TEST_F(ConverterTest, can_Usd_To_Rub) {
    EXPECT_NEAR(42.2600685, CurrencyConverter::convert
        (CurrencyConverter::USD, CurrencyConverter::RUB, 1.0), eps);
}

TEST_F(ConverterTest, can_Gbp_To_Nok) {
    EXPECT_NEAR(70.8657/6.42, CurrencyConverter::convert
        (CurrencyConverter::GBP, CurrencyConverter::NOK, 1.0), eps);
}

TEST_F(ConverterTest, can_Nok_To_Jpy) {
    EXPECT_NEAR(6.42/0.38, CurrencyConverter::convert
        (CurrencyConverter::NOK, CurrencyConverter::JPY, 1.0), eps);
}

TEST_F(ConverterTest, can_Jpy_To_Gbp) {
    EXPECT_NEAR(CurrencyConverter::convert(CurrencyConverter::JPY,
        CurrencyConverter::GBP, 1.0), 0.38/70.8657, eps);
}

