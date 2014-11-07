// Copyright 2014 Maxim Maximov

#include <gtest/gtest.h>

#include <limits.h>
#include <string>

#include "include/alghuffman.h"

class HuffmanAlgorithmTest : public ::testing::Test {
 protected:
    // NOTE: here you can put your init/deinit code
    // virtual void SetUp() {}
    // virtual void TearDown() {}
};

TEST_F(HuffmanAlgorithmTest, Can_Merge_Nodes_With_Constructor) {
    Node leftNode, rightNode;
    leftNode.value = 2;
    rightNode.value = 3;
    Node mergeNode(&leftNode, &rightNode);

    EXPECT_EQ(2 + 3, mergeNode.value);
}

TEST_F(HuffmanAlgorithmTest, Can_Code_String_With_One_Symbol) {
    HuffmanAlgorithm huff;
    std::string result, source = "aaaa";
    result += "0000";
    EXPECT_EQ(result, huff.Code(source));
}

TEST_F(HuffmanAlgorithmTest, Can_Decode_And_Decode_Standart_String) {
    HuffmanAlgorithm huff;
    std::string result1, result2, source = "Hello! What are you doing?";
    result1 = huff.Code(source);
    result2 = huff.Decode(result1);
    EXPECT_EQ(source, result2);
}

TEST_F(HuffmanAlgorithmTest, Exception_When_Try_To_Decode_Without_Tree) {
    HuffmanAlgorithm huff;
    EXPECT_THROW(huff.Decode("10010101010011100011"), std::string);
}

TEST_F(HuffmanAlgorithmTest, Exception_When_Try_To_Decode_Wrong_String) {
    HuffmanAlgorithm huff;
    EXPECT_THROW(huff.Decode("random string"), std::string);
}

TEST_F(HuffmanAlgorithmTest, Try_Construct_Object_With_Copy) {
    HuffmanAlgorithm oldhuff;
    std::string temp;
    temp = oldhuff.Code("anything");
    HuffmanAlgorithm newhuff(oldhuff);
    EXPECT_EQ("anything", newhuff.Decode(temp));
}

TEST_F(HuffmanAlgorithmTest, Try_Copy_Object) {
    HuffmanAlgorithm oldhuff, newhuff;
    std::string temp;
    temp = oldhuff.Code("anything");
    newhuff = oldhuff;
    EXPECT_EQ("anything", newhuff.Decode(temp));
}
