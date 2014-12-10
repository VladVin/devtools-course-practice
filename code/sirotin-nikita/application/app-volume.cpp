// Copyright 2014 Sirotin Nikita

#include <stdio.h>
#include <string>
#include "include/app-volume.h"

int main(int argc, const char** argv) {
  VolumeApplication app;
  std::string output = app(argc, argv);
  printf("%s\n", output.c_str());
  return 0;
}
