// Copyright 2014 Bykadorov Roman

#include "include/currencyconverter.h"

#include <float.h>
#include "string"

static const double eurForRub = 53.5948527;
static const double usdForRub = 42.2600685;
static const double gbpForRub = 70.8657;
static const double jpyForRub = 0.38;
static const double nokForRub = 6.42;

double CurrencyConverter::convert(Currency from, Currency to, double value) {
double fromToRub = 0;
double rubTo = 0;
    switch (from) {
        case USD:
            fromToRub = value * usdForRub;
        break;
        case EUR:
            fromToRub = value * eurForRub;
        break;
        case RUB:
            fromToRub = value;
        break;
        case GBP:
            fromToRub = value * gbpForRub;
        break;
        case JPY:
            fromToRub = value * jpyForRub;
        break;
        case NOK:
            fromToRub = value * nokForRub;
        break;
    };
    switch (to) {
        case USD:
            rubTo = fromToRub / usdForRub;
        break;
        case EUR:
            rubTo = fromToRub / eurForRub;
        break;
        case RUB:
            rubTo = fromToRub;
        break;
        case GBP:
            rubTo = fromToRub / gbpForRub;
        break;
        case JPY:
            rubTo = fromToRub / jpyForRub;
        break;
        case NOK:
            rubTo = fromToRub / nokForRub;
        break;
    };
return rubTo;
}

