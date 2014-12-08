// Copyright 2014 Bykadorov Roman

#ifndef CODE_BYKADOROV_ROMAN_INCLUDE_CURRENCYCONVERTER_H_
#define CODE_BYKADOROV_ROMAN_INCLUDE_CURRENCYCONVERTER_H_

class CurrencyConverter {
 public:
    static const double eurForRub = 65.72;
    static const double usdForRub = 53.11;
    static const double gbpForRub = 83.14;
    static const double jpyForRub = 0.44;
    static const double nokForRub = 7.5;

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
