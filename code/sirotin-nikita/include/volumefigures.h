// Copyright 2014 Sirotin Nikita

#ifndef CODE_SIROTIN_NIKITA_INCLUDE_VOLUMEFIGURES_H_
#define CODE_SIROTIN_NIKITA_INCLUDE_VOLUMEFIGURES_H_

enum volArg {cube, sphere, pyramid, cylinder};

class Volume {
 public:
  static double cube(const double side);
  static double sphere(const double radius);
  static double pyramid(const double height, const double area);
  static double cylinder(const double height, const double radius);
};

#endif  // CODE_SIROTIN_NIKITA_INCLUDE_VOLUMEFIGURES_H_
