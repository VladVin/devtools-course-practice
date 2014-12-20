
// Copyright 2014 Fedosov Alexander

#include <float.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <cstdlib>
#include <string>
#include <set>
#include "include/lengthconverter.hpp"

LengthConverter::LengthConverter() {}
LengthConverter::~LengthConverter() {}

double LengthConverter::checkLength(double length) {
if (length < 0.0) {
        throw std::string("Length can't be below zero!");
    }
return length;
}

double LengthConverter::convertToMeters(Type type, double length) {
        if (type == LengthConverter::TYPE_METER) {return checkLength(length);}
        else if (type == LengthConverter::TYPE_INCH) {
            length*=0.0254; return(checkLength(length));}
        else if (type == LengthConverter::TYPE_FOOT) {
            length*=0.3048; return(checkLength(length));}
        else if (type ==  LengthConverter::TYPE_YARD) {
            length*=0.9144; return(checkLength(length));}
        else if (type ==  LengthConverter::TYPE_MILE) {
            length*=1609.344; return(checkLength(length));} else {
    throw std::string("Unknown type");}
}
double LengthConverter::convertMetersTo(Type type, double length) {
        if (type == LengthConverter::TYPE_METER) {return checkLength(length);}
        else if (type == LengthConverter::TYPE_INCH) {
            length*=39.37007874; return(checkLength(length));}
        else if (type == LengthConverter::TYPE_FOOT) {
            length*=3.28083989; return(checkLength(length));}
        else if (type ==  LengthConverter::TYPE_YARD) {
            length*=1.09361329; return(checkLength(length));}
        else if (type ==  LengthConverter::TYPE_MILE) {
            length*=0.00062137; return(checkLength(length));} else {
    throw std::string("Unknown type");}
}
double LengthConverter::convert(Type from, double length, Type to) {
    if (from == to) {
        return checkLength(length);
    } else {
    return (convertMetersTo(to, (convertToMeters(from, length))));
    }
}
LengthConverter::Type LengthConverter::checkType(const char* type) {
    LengthConverter::Type typeToReturn;
    if (!strcmp(type, "meters")) {
            typeToReturn = LengthConverter::TYPE_METER;
        } else if (!strcmp(type, "inches")) {
            typeToReturn = LengthConverter::TYPE_INCH;
        } else if (!strcmp(type, "feet")) {
            typeToReturn = LengthConverter::TYPE_FOOT;

        } else if (!strcmp(type, "yards")) {
            typeToReturn = LengthConverter::TYPE_YARD;
        } else if (!strcmp(type, "miles")) {
            typeToReturn = LengthConverter::TYPE_MILE;
        } else {
            throw std::string("Unknown type");
        }
    return typeToReturn;
}
