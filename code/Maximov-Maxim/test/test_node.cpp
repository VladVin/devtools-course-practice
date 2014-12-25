// Copyright 2014 Maxim Maximov

#include <gtest/gtest.h>

#include "include/alghuffman.h"

TEST(NodeTest, Can_Merge_Nodes_With_Constructor) {
    // Arrange
    Node leftNode, rightNode;
    leftNode._value = 2;
    rightNode._value = 3;

    // Act
    Node* mergeNode = new Node(&leftNode, &rightNode);

    // Assert
    EXPECT_EQ(2 + 3, mergeNode->_value);
}

TEST(NodeTest, Try_Copy_Node) {
    // Arrange
    Node oldnode, newnode;
    oldnode._value = 42;

    // Act
    newnode = oldnode;

    // Assert
    EXPECT_EQ(42, newnode._value);
}

TEST(NodeTest, Try_Construct_Node_With_Copy) {
    // Arrange
    Node oldnode;
    oldnode._value = 42;

    // Act
    Node newnode(oldnode);

    // Assert
    EXPECT_EQ(42, newnode._value);
}
