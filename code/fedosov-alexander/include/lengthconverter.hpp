// Copyright 2014 Fedosov Alexander

#ifndef CODE_FEDOSOV_ALEXANDER_INCLUDE_LENGTHCONVERTER_HPP_
#define CODE_FEDOSOV_ALEXANDER_INCLUDE_LENGTHCONVERTER_HPP_
class LengthConverter {
 public:
    enum Type {
        TYPE_METER = 1,
        TYPE_INCH = 2,
        TYPE_FOOT = 3,
        TYPE_YARD = 4,
        TYPE_MILE = 5
    };
    LengthConverter();
    ~LengthConverter();
    double convertToMeters(Type type, double length);
    double convertMetersTo(Type type, double length);
    double convert(Type from, double length, Type to);
    Type checkType(const char* type);

 private:
    static double checkLength(double length);
};
#endif
