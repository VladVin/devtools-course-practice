// Copyright 2014 Dmitry Kruchinin

#include <gtest/gtest.h>

#include <stdlib.h>
#include <stdint.h>
#include <string>

#include "include/stack.h"
#include "include/node.h"

class StackTest : public ::testing::Test {
 protected:
    Stack<int> stack_int;
    Stack<float> stack_float;
};

TEST_F(StackTest, LIFO_int) {
    int a[10];
    unsigned int seed = 0;
    for (int i = 0; i < 10; i++) {
        a[i] = rand_r(&seed);
        stack_int.push(a[i]);
    }
    for (int i = 9; i >= 0; i--) {
        EXPECT_EQ(a[i], stack_int.pop());
    }
}

TEST_F(StackTest, Top_int) {
    stack_int.push(375);
    EXPECT_EQ(375, stack_int.top());
}

TEST_F(StackTest, IsEmpty_int) {
    EXPECT_TRUE(stack_int.isEmpty());
    stack_int.push(25);
    EXPECT_FALSE(stack_int.isEmpty());
}

TEST_F(StackTest, Exception_When_Stack_Is_Empty_int) {
    EXPECT_THROW(stack_int.pop(), std::runtime_error);
    EXPECT_THROW(stack_int.top(), std::runtime_error);
}

TEST_F(StackTest, Elems_Realy_Removes_From_Stack_int) {
    stack_int.push(15);
    stack_int.push(28);
    stack_int.pop();
    stack_int.pop();

    EXPECT_THROW(stack_int.pop(), std::runtime_error);
    EXPECT_THROW(stack_int.top(), std::runtime_error);
}

TEST_F(StackTest, Node_Params_int) {
    Node<int> node(5, NULL);
    EXPECT_EQ(5, node.element);
    EXPECT_EQ(NULL, node.next);
}

TEST_F(StackTest, LIFO_float) {
    float a[10];
    unsigned int seed = 0;
    for (int i = 0; i < 10; i++) {
        a[i] = static_cast<float>(rand_r(&seed));
        stack_float.push(a[i]);
    }
    for (int i = 9; i >= 0; i--) {
        EXPECT_EQ(a[i], stack_float.pop());
    }
}

TEST_F(StackTest, Top_float) {
    stack_float.push(2.718281828f);
    EXPECT_EQ(2.718281828f, stack_float.top());
}

TEST_F(StackTest, IsEmpty_float) {
    EXPECT_TRUE(stack_float.isEmpty());
    float t = 25.0f;
    stack_float.push(t);
    EXPECT_FALSE(stack_float.isEmpty());
}

TEST_F(StackTest, Exception_When_Stack_Is_Empty_float) {
    EXPECT_THROW(stack_float.pop(), std::runtime_error);
    EXPECT_THROW(stack_float.top(), std::runtime_error);
}

TEST_F(StackTest, Elems_Realy_Removes_From_Stack_float) {
    stack_float.push(7.0f);
    stack_float.push(12.0f);
    stack_float.pop();
    stack_float.pop();

    EXPECT_THROW(stack_float.pop(), std::runtime_error);
    EXPECT_THROW(stack_float.top(), std::runtime_error);
}

TEST_F(StackTest, Node_Params_float) {
    Node<float> node(5.0f, NULL);
    EXPECT_EQ(5.0f, node.element);
    EXPECT_EQ(NULL, node.next);
}

struct qq_t {
    char array[1000000];
};

TEST(StressTest, PushAndPop) {
    qq_t hello;
    Stack<qq_t> stack;
    for (int i = 0; i < 1000; i++) {
        stack.push(hello);
        stack.pop();
    }
    EXPECT_TRUE(stack.isEmpty());
}
