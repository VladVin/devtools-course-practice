// Copyright 2014 Maxim Maximov

#include <gtest/gtest.h>

#include <limits.h>
#include <string>

#include "include/alghuffman.h"

TEST(HuffmanAlgorithmTest, Can_Merge_Nodes_With_Constructor) {
    Node leftNode, rightNode;
    leftNode._value = 2;
    rightNode._value = 3;
    Node* mergeNode = new Node(&leftNode, &rightNode);
    EXPECT_EQ(2 + 3, mergeNode->_value);
}

TEST(HuffmanAlgorithmTest, Can_Code_String_With_One_Symbol) {
    HuffmanAlgorithm huff;
    std::string result, source = "aaaa";
    result += "0000";
    EXPECT_EQ(result, huff.code(source));
}

TEST(HuffmanAlgorithmTest, Code_Is_Correct) {
    std::string source = "Hello!";
    std::string expectedResult = "11100101001110";
    HuffmanAlgorithm huff;

    std::string result = huff.code(source);

    EXPECT_EQ(expectedResult, result);
}

TEST(HuffmanAlgorithmTest, Can_Code_And_Decode_Standart_String) {
    HuffmanAlgorithm huff;
    std::string result1, result2, source = "Hello! What are you doing?";
    result1 = huff.code(source);
    result2 = huff.decode(result1);
    EXPECT_EQ(source, result2);
}

TEST(HuffmanAlgorithmTest, Exception_When_Try_To_Decode_Without_Tree) {
    HuffmanAlgorithm huff;
    EXPECT_THROW(huff.decode("10010101010011100011"), std::string);
}

TEST(HuffmanAlgorithmTest, Exception_When_Try_To_Decode_Wrong_String) {
    HuffmanAlgorithm huff;
    EXPECT_THROW(huff.decode("random string"), std::string);
}

TEST(HuffmanAlgorithmTest, Try_Construct_Object_With_Copy) {
    HuffmanAlgorithm oldhuff;
    std::string temp;
    temp = oldhuff.code("anything");
    HuffmanAlgorithm newhuff(oldhuff);
    EXPECT_EQ("anything", newhuff.decode(temp));
}

TEST(HuffmanAlgorithmTest, Try_Copy_Object) {
    HuffmanAlgorithm oldhuff, newhuff;
    std::string temp;
    temp = oldhuff.code("anything");
    newhuff = oldhuff;
    EXPECT_EQ("anything", newhuff.decode(temp));
}

TEST(HuffmanAlgorithmTest, Try_Copy_Node) {
    Node oldnode, newnode;
    oldnode._value = 42;
    newnode = oldnode;
    EXPECT_EQ(42, newnode._value);
}

TEST(HuffmanAlgorithmTest, Try_Construct_Node_With_Copy) {
    Node oldnode;
    oldnode._value = 42;
    Node newnode(oldnode);
    EXPECT_EQ(42, newnode._value);
}
