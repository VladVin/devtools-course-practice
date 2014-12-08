// Copyright 2014 Bykadorov Roman

#ifndef CODE_BYKADOROV_ROMAN_INCLUDE_CURRENCYCONVERTER_H_
#define CODE_BYKADOROV_ROMAN_INCLUDE_CURRENCYCONVERTER_H_

class CurrencyConverter {
 public:
    static constexpr double eurForRub = 65.72;
    static constexpr double usdForRub = 53.11;
    static constexpr double gbpForRub = 83.14;
    static constexpr double jpyForRub = 0.44;
    static constexpr double nokForRub = 7.5;

    enum Currency {
        USD = 1,
        EUR = 2,
        RUB = 3,
        // Фунты-стерлингов
        GBP = 4,
        // Японская иена
        JPY = 5,
        // Норвежская крона
        NOK = 6
    };
    static double convert(Currency from, Currency to, double value);
};
#endif  // CODE_BYKADOROV_ROMAN_INCLUDE_CURRENCYCONVERTER_H_
