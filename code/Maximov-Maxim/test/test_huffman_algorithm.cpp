// Copyright 2014 Maxim Maximov

#include <gtest/gtest.h>

#include <string>

#include "include/alghuffman.h"


TEST(HuffmanAlgorithmTest, Can_Code_String_With_One_Symbol) {
    // Arrange
    HuffmanAlgorithm huff;
    std::string source = "aaaa";

    // Act
    std::string result = huff.code(source);

    // Assert
    EXPECT_EQ("0000", result);
}

TEST(HuffmanAlgorithmTest, Code_Is_Correct) {
    // Arrange
    HuffmanAlgorithm huff;
    std::string source = "Hello!";
    std::string expectedResult = "11100101001110";

    // Act
    std::string result = huff.code(source);

    // Assert
    EXPECT_EQ(expectedResult, result);
}

TEST(HuffmanAlgorithmTest, Can_Code_And_Decode_Standart_String) {
    // Arrange
    HuffmanAlgorithm huff;
    std::string source = "Hello! What are you doing?";

    // Act
    std::string result = huff.decode(huff.code(source));

    // Assert
    EXPECT_EQ(source, result);
}

TEST(HuffmanAlgorithmTest, Exception_When_Try_To_Decode_Without_Tree) {
    // Arrange
    HuffmanAlgorithm huff;
    std::string source = "10010101010011100011";

    // Act & Assert
    EXPECT_THROW(huff.decode(source), std::string);
}

TEST(HuffmanAlgorithmTest, Exception_When_Try_To_Decode_Wrong_String) {
    // Arrange
    HuffmanAlgorithm huff;
    std::string source = "random string";

    // Act & Assert
    EXPECT_THROW(huff.decode(source), std::string);
}

TEST(HuffmanAlgorithmTest, Try_Construct_Object_With_Copy) {
    // Arrange
    HuffmanAlgorithm oldhuff;
    std::string temp = oldhuff.code("anything");

    // Act
    HuffmanAlgorithm newhuff(oldhuff);

    // Assert
    EXPECT_EQ("anything", newhuff.decode(temp));
}

TEST(HuffmanAlgorithmTest, Try_Copy_Object) {
    // Arrange
    HuffmanAlgorithm oldhuff, newhuff;
    std::string temp = oldhuff.code("anything");

    // Act
    newhuff = oldhuff;

    // Assert
    EXPECT_EQ("anything", newhuff.decode(temp));
}
