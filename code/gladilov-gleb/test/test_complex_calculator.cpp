// Copyright 2014 Gladilov Gleb

#include <gtest/gtest.h>

#include <string>

#include "include/complexcalculator.h"

class ComplexTest : public ::testing::Test {
 protected:
    double epsilon = 0.001;
};

TEST_F(ComplexTest, Can_Create_With_Real_And_Imaginary) {
    // Arrange & Act
    Complex test(26, 20);

    // Assert
    EXPECT_EQ(26, test.getReal());
    EXPECT_EQ(20, test.getImaginary());
}
TEST_F(ComplexTest, Can_Create_Via_Copying) {
    // Arrange
    Complex test(26, 20);

    // Act
    Complex tested = test;

    // Assert
    EXPECT_EQ(26, tested.getReal());
    EXPECT_EQ(20, tested.getImaginary());
}
TEST_F(ComplexTest, Can_Set_Real) {
    // Arrange
    Complex test;

    // Act
    test.setReal(26);

    // Assert
    EXPECT_EQ(26, test.getReal());
}

TEST_F(ComplexTest, Can_Set_Imaginary) {
    // Arrange
    Complex test;

    // Act
    test.setImaginary(26);

    // Assert
    EXPECT_EQ(26, test.getImaginary());
}
TEST_F(ComplexTest, Can_Add_Complex) {
    // Arrange
    Complex test(26, 14);
    Complex tested(1, 7);

    // Act
    tested.add(test);

    // Assert
    EXPECT_EQ(27, tested.getReal());
    EXPECT_EQ(21, tested.getImaginary());
}

TEST_F(ComplexTest, Can_Difference_Complex) {
    // Arrange
    Complex test(26, 14);
    Complex tested(1, 1);

    // Act
    tested.difference(test);

    // Assert
    EXPECT_EQ(-25, tested.getReal());
    EXPECT_EQ(-13, tested.getImaginary());
}

TEST_F(ComplexTest, Can_Multiplication_Complex) {
    // Arrange
    Complex test(5, 3);
    Complex tested(4, 6);

    // Act
    tested.multiplication(test);

    // Assert
    EXPECT_EQ(2, tested.getReal());
    EXPECT_EQ(42, tested.getImaginary());
}
TEST_F(ComplexTest, Can_Division_Complex) {
    // Arrange
    Complex test(15, 20);
    Complex tested(27, 30);

    // Act
    tested.division(test);

    // Assert
    EXPECT_NEAR(1.608, tested.getReal(), ComplexTest::epsilon);
    EXPECT_NEAR(-0.144, tested.getImaginary(), ComplexTest::epsilon);
}

TEST_F(ComplexTest, Can_Division_By_Complex_With_Zero_Real) {
    // Arrange
    Complex test(0, 1);
    Complex tested(15, 10);

    // Act
    tested.division(test);

    // Assert
    EXPECT_EQ(10, tested.getReal());
    EXPECT_EQ(-15, tested.getImaginary());
}
TEST_F(ComplexTest, Can_Division_By_Complex_With_Zero_Imaginary) {
    // Arrange
    Complex test(1, 0);
    Complex tested(15, 10);

    // Act
    tested.division(test);

    // Assert
    EXPECT_EQ(15, tested.getReal());
    EXPECT_EQ(10, tested.getImaginary());
}
TEST_F(ComplexTest, Do_Throw_When_Division_By_Zero) {
    // Arrange
    Complex test(0, 0);
    Complex tested(26, 14);

    // Act & Assert
    EXPECT_THROW(tested.division(test), std::string);
}
