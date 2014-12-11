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
message_ += std::string("This is a app which calculation volume figures.\n\n")
  + "Please provide arguments in the following format:\n\n"
  + " $ " + appname + " <number figures> <argument1> (<argument2>)\n\n"
  + "Where number figures: 1 - cube, 2 - sphere, 3 - pyramid, 4 - cylinder"
  + "if user input 1 or 2, then programm takes one argument"
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

int64_t parseInt(const char* arg) {
  char* end;
  int64_t value = strtol(arg, &end, 10);
  return value;
}

bool VolumeApplication::parseArguments(int argc, const char** argv,
Expression* expr) {
  if (argc == 1) {
    help(argv[0]);
    return false;
  }
  if ((static_cast<int64_t>(parseInt(argv[1])) == 1 && argc != 3) ||
    (static_cast<int64_t>(parseInt(argv[1])) == 2 && argc != 3)) {
    message_ = "ERROR: Should be 3 arguments.\n\n";
    help(argv[0]);
    return false;
  }
  if ((static_cast<int64_t>(parseInt(argv[1])) == 3 && argc != 4) ||
    (static_cast<int64_t>(parseInt(argv[1])) == 4 && argc != 4)) {
    message_ = "ERROR: Should be 4 arguments.\n\n";
    help(argv[0]);
    return false;
  }
  try {
    expr->figure = (parseInt(argv[1]));
    expr->arg1 = static_cast<double>(parseDouble(argv[2]));
    if (expr->figure == 1 || expr->figure == 2)
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
    case 1:
    // stream << expr.arg1; break;
    stream << vol.cube(expr.arg1); break;
    case 2:
    stream << vol.sphere(expr.arg1); break;
    case 3:
    stream << vol.pyramid(expr.arg1, expr.arg2); break;
    case 4:
    stream << vol.cylinder(expr.arg1, expr.arg2); break;
  }
  message_ = stream.str();
  return message_;
}
