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
        CurrencyConverter::EUR, CurrencyConverter::eurForRub), eps);
}

TEST_F(ConverterTest, can_Eur_To_Usd) {
    EXPECT_NEAR(CurrencyConverter::eurForRub/CurrencyConverter::usdForRub,
        CurrencyConverter::convert(CurrencyConverter::EUR,
            CurrencyConverter::USD, 1.0), eps);
}

TEST_F(ConverterTest, can_Usd_To_Rub) {
    EXPECT_NEAR(CurrencyConverter::usdForRub, CurrencyConverter::convert
        (CurrencyConverter::USD, CurrencyConverter::RUB, 1.0), eps);
}

TEST_F(ConverterTest, can_Gbp_To_Nok) {
    EXPECT_NEAR(CurrencyConverter::gbpForRub/CurrencyConverter::nokForRub,
        CurrencyConverter::convert(CurrencyConverter::GBP,
            CurrencyConverter::NOK, 1.0), eps);
}

TEST_F(ConverterTest, can_Nok_To_Jpy) {
    EXPECT_NEAR(CurrencyConverter::nokForRub/CurrencyConverter::jpyForRub,
        CurrencyConverter::convert(CurrencyConverter::NOK,
            CurrencyConverter::JPY, 1.0), eps);
}

TEST_F(ConverterTest, can_Jpy_To_Gbp) {
    EXPECT_NEAR(CurrencyConverter::convert(CurrencyConverter::JPY,
        CurrencyConverter::GBP, 1.0), CurrencyConverter::jpyForRub/
            CurrencyConverter::gbpForRub, eps);
}

