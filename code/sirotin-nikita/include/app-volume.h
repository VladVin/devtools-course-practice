// Copyright 2014 Sirotin Nikita

#ifndef  CODE_SIROTIN_NIKITA_INCLUDE_APP_VOLUME_H_
#define  CODE_SIROTIN_NIKITA_INCLUDE_APP_VOLUME_H_

#include <string>
#include "include/volumefigures.h"

#pragma pack(push, 1)
typedef struct {
volArg figure;
double arg1;
double arg2;
} Expression;

#pragma pack(pop)

class VolumeApplication {
  public:
VolumeApplication();
std::string operator()(int argc, const char** argv);
  private:
std::string message_;
void help(const char* appname);
bool parseArguments(int argc, const char** argv, Expression* expr);
};

#endif  // CODE_SIROTIN_NIKITA_INCLUDE_APP_VOLUME_H_
