// Copyright 2014 Sirotin Nikita

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <string>
#include <sstream>

#include "include/volumefigures.h"
#include "include/app-volume.h"

VolumeApplication::VolumeApplication() : message_("") {}

void VolumeApplication::help(const char* appname) {
message_ += std::string("This is an app which calculation volume figures.\n\n")
  + "Please provide arguments in the following format:\n\n"
  + " $ " + appname + " <number figures> <argument1> (<argument2>)\n\n"
  + "Where number figures: 1 - cube, 2 - sphere, 3 - pyramid, 4 - cylinder"
  + "if user input 1 or 2, then program takes one argument"
  + "else 3 or 4 takes two argument.\n";
}

double parseDouble(const char* arg);

int64_t parseInt(const char* arg);

double parseDouble(const char* arg) {
  char* end;
  double value = strtod(arg, &end);
  if (end[0]) {
    throw "Wrong number format!";
  }
  return value;
}

volArg parseArg(const  char* arg) {
  volArg avol;
  if (strcmp(arg, "cube") == 0) {
    avol = cube;
  } else if (strcmp(arg, "sphere") == 0) {
    avol = sphere;
  } else if (strcmp(arg, "pyramid") == 0) {
    avol = pyramid;
  } else if (strcmp(arg, "cylinder") == 0) {
    avol = cylinder;
  } else {
    throw std::string("Wrong arg volume format!");
  }
  return avol;
}

bool VolumeApplication::parseArguments(int argc, const char** argv,
Expression* expr) {
  if (argc == 1) {
    help(argv[0]);
    return false;
  }
  volArg avol;
  avol = static_cast<volArg>(parseArg(argv[1]));
  if ((avol == cube && argc != 3) ||
    (avol == sphere && argc != 3)) {
    message_ = "ERROR: Should be 3 arguments.\n\n";
    help(argv[0]);
    return false;
  }
  if ((avol == pyramid && argc != 4) ||
    (avol == cylinder && argc != 4)) {
    message_ = "ERROR: Should be 4 arguments.\n\n";
    help(argv[0]);
    return false;
  }
  try {
    expr->figure = static_cast<volArg>(parseArg(argv[1]));
    expr->arg1 = static_cast<double>(parseDouble(argv[2]));
    if (expr->figure == cube || expr->figure == sphere)
      expr->arg2 = 0;
    else
      expr->arg2 = static_cast<double>(parseDouble(argv[3]));
  }
  catch(...) {
      message_ = "Wrong number format!\n";
      return false;
  }
  return true;
}

std::string VolumeApplication::operator()(int argc, const char** argv) {
  Expression expr;
  bool returnCode = parseArguments(argc, argv, &expr);
  if (returnCode != true)
    return message_;
  Volume vol;
  std::ostringstream stream;
  stream << "Result = ";
  switch (expr.figure) {
    case cube:
    stream << vol.cube(expr.arg1); break;
    case sphere:
    stream << vol.sphere(expr.arg1); break;
    case pyramid:
    stream << vol.pyramid(expr.arg1, expr.arg2); break;
    case cylinder:
    stream << vol.cylinder(expr.arg1, expr.arg2); break;
  }
  message_ = stream.str();
  return message_;
}
