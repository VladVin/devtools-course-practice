// Copyright 2014 Sirotin Nikita

#include <gtest/gtest.h>

#include <limits.h>
#include <string>
#include "include/app-volume.h"

using ::testing::internal::RE;

class AppTest: public ::testing::Test {
  protected:
  VolumeApplication application;
  std::string info;

  void Act(int argc, const char* argv[]) {
  info = application(argc, argv);
  }

  void Assert(std::string expect) {
  EXPECT_TRUE(RE::PartialMatch(info, RE(expect)));
  }
};

TEST_F(AppTest, Print_Help_Without_Arguments) {
  // Arrange
  int argc = 1;
  const char* argv[] = {"appName"};

  Act(argc, argv);

  Assert("This is a app which calculation volume figures\\..*");
  }

TEST_F(AppTest, Check_Number_Of_Arguments_For_Cube) {
  // Arrange
  int argc = 4;
  const char* argv[] = {"appName", "1", "3.", "5."};

  Act(argc, argv);

  Assert("ERROR: Should be 3 arguments\\..*");
}

TEST_F(AppTest, Check_Number_Of_Arguments_For_Sphere) {
  // Arrange
  int argc = 4;
  const char* argv[] = {"appName", "2", "3.", "5."};

  Act(argc, argv);

  Assert("ERROR: Should be 3 arguments\\..*");
}

TEST_F(AppTest, Check_Number_Of_Arguments_For_Piramid) {
  // Arrange
  int argc = 3;
  const char* argv[] = {"appName", "3", "3."};

  Act(argc, argv);

  Assert("ERROR: Should be 4 arguments\\..*");
}

TEST_F(AppTest, Check_Number_Of_Arguments_For_Cylinder) {
  // Arrange
  int argc = 3;
  const char* argv[] = {"appName", "4", "3."};

  Act(argc, argv);

  Assert("ERROR: Should be 4 arguments\\..*");
}

TEST_F(AppTest, Detect_Wrong_Number_Format_Double) {
  // Arrange
  int argc = 4;
  const char* argv[] = {"appName", "3", "2.", "o"};

  Act(argc, argv);

  Assert("Wrong number format!.*");
}


TEST_F(AppTest, Correct_Calculation_Volume_Cube) {
  // Arrange
  int argc = 3;
  const char* argv[] = {"appName", "1", "2.0"};

  Act(argc, argv);

  Assert("Result = 8");
}

TEST_F(AppTest, Correct_Calculation_Volume_Sphere) {
  // Arrange
  int argc = 3;
  const char* argv[] = {"appName", "2", "2.1215688358"};

  Act(argc, argv);

  Assert("Result = 40");
}

TEST_F(AppTest, Correct_Calculation_Volume_Pyramid) {
  // Arrange
  int argc = 4;
  const char* argv[] = {"appName", "3", "5", "6"};

  Act(argc, argv);

  Assert("Result = 10");
}

TEST_F(AppTest, Correct_Calculation_Volume_Cylinder) {
  // Arrange
  int argc = 4;
  const char* argv[] = {"appName", "4", "0.3183098861", "6"};

  Act(argc, argv);

  Assert("Result = 36");
}
