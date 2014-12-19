// Copyright 2014 Shochin Alexandr

#include "include/tconv.h"

#include <limits.h>
#include <string>

TemperatureConvertor::TemperatureConvertor() {}

TemperatureConvertor::~TemperatureConvertor() {}

double TemperatureConvertor::Convert(Temperature temp, Unit unit) {
    if (Check(temp) == -1) {
            throw std::string("Incorrect value for the first argument!");
    } else {
        if (temp.unit == Celsius) {
            return ConvertFromCelsius(temp, unit);
        } else {
            return ConvertToCelsius(temp);
        }
    }
}

double TemperatureConvertor::auxiliaryArrayOne[4] = {0, -273.15, -32, 0};
double TemperatureConvertor::auxiliaryArrayTwo[4] = {1, 1, 5.0/9.0, 100.0/33};

int TemperatureConvertor::Check(Temperature temp) {
    if ((temp.unit == Celsius) && (temp.value < -273.15)) {
        return -1;
    } else if ((temp.unit == Kelvin) && (temp.value < 0)) {
        return -1;
    } else if ((temp.unit == Fahrenheit) && (temp.value < -459.67)) {
        return -1;
    } else if ((temp.unit == Newton) && (temp.value < -90.14)) {
        return -1;
    } else {
        return 0;
    }
}

double TemperatureConvertor::ConvertFromCelsius(Temperature temp, Unit unit) {
    if (temp.unit == Celsius && unit == Kelvin) {
        return temp.value - auxiliaryArrayOne[unit];
    } else {
        return (1 / auxiliaryArrayTwo[unit] *
        temp.value - auxiliaryArrayOne[unit]);
    }
}

double TemperatureConvertor::ConvertToCelsius(Temperature temp) {
    return ((auxiliaryArrayOne[temp.unit] +
    temp.value) * auxiliaryArrayTwo[temp.unit]);
}
