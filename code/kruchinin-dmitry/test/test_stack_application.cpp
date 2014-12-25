// Copyright 2014 Dmitry Kruchinin

#include <gtest/gtest.h>

#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <iterator>

#include "include/stack_application.h"

using ::testing::internal::RE;
using std::vector;
using std::string;

class StackAppTest : public ::testing::Test {
 protected:
    virtual void SetUp() {
        args.clear();

        FILE* f = fopen("../code/kruchinin-dmitry/test/test_file.txt", "w");
        int sum = 0;
        for (int i = 0; i < 10; i++) {
            sum += i;
            fprintf(f, "%d\n", sum);
        }
        fclose(f);
    }

    void Act(vector<string> args_) {
        vector<char*> starts(args_.size() + 1);
        starts[0] = new char[8];
        snprintf(starts[0], sizeof(starts[0][0]) * 8, "appname");

        for (size_t i = 0; i < args_.size(); i++) {
            starts[i + 1] = new char[args_[i].length()];
            snprintf(starts[i + 1],
                args_[i].length() + 1,
                "%s", args_[i].c_str());
        }
        char **argv = &starts.front();
        int argc = static_cast<int>(args_.size()) + 1;

        output_ = app_(argc, argv);

        for (size_t i = 0; i < starts.size(); i++) {
            delete[] starts[i];
        }
    }

    void Assert(std::string expected) {
        EXPECT_TRUE(RE::PartialMatch(output_, RE(expected)));
    }

    StackApplication app_;
    string output_;
    vector<string> args;
    const char* test_file = "../code/kruchinin-dmitry/test/test_file.txt";
};

TEST_F(StackAppTest, Can_Push) {
    args = { test_file, "push", "7", "12" };

    Act(args);

    Assert("7\n12\n");
}

TEST_F(StackAppTest, Can_Pop) {
    args = { test_file, "pop", "2"};

    Act(args);

    Assert("45\n36\n");
}

TEST_F(StackAppTest, Can_Pop_All) {
    args = { test_file, "pop", "-all"};

    Act(args);

    Assert("45\n36\n28\n21\n15\n10\n6\n3\n1\n0\n");
}

TEST_F(StackAppTest, Can_Top) {
    args = { test_file, "top" };

    Act(args);

    Assert("45");
}

TEST_F(StackAppTest, Without_Arguments) {
    args = { test_file };

    Act(args);

    Assert("Too few arguments*");
}

TEST_F(StackAppTest, Without_Push_Arguments) {
    args = { test_file, "push"};

    Act(args);

    Assert("Too few arguments*");
}

TEST_F(StackAppTest, Without_Pop_Arguments) {
    args = { test_file, "pop" };

    Act(args);

    Assert("Too few arguments*");
}

TEST_F(StackAppTest, Print_Warning_When_Stack_Is_Empty_Pop) {
    args = { test_file, "pop", "-all" };
    Act(args);

    args = { test_file, "pop", "2" };
    Act(args);

    Assert("Stack is empty*");
}

TEST_F(StackAppTest, Print_Warning_When_Stack_Is_Empty_Top) {
    args = { test_file, "pop", "-all" };
    Act(args);

    args = { test_file, "top" };
    Act(args);

    Assert("Stack is empty*");
}

TEST_F(StackAppTest, With_Trash_Instead_Of_Command) {
    args = { test_file, "blabla"};

    Act(args);

    Assert("Unknown command*");
}

TEST_F(StackAppTest, Print_Warning_On_Trash_In_Push) {
    args = { test_file, "push", "lala" };

    Act(args);

    Assert("Invalid argument for push (not a number)*");
}

TEST_F(StackAppTest, Print_Warning_On_Big_Number_In_Push) {
    args = { test_file, "push", "123456789012345" };

    Act(args);

    Assert("Too big number to push*");
}

TEST_F(StackAppTest, Print_Warning_On_Trash_In_Pop) {
    args = { test_file, "pop", "lala" };

    Act(args);

    Assert("Invalid argument for pop (not a number)*");
}

TEST_F(StackAppTest, Print_Warning_On_Big_Number_To_Pop) {
    args = { test_file,
            "pop", "123456789012345" };

    Act(args);

    Assert("Too big number to pop*");
}

TEST_F(StackAppTest, Print_Warning_When_Data_In_File_Is_Invalid) {
    args = { test_file, "push", "1"};

    FILE* f = fopen("../code/kruchinin-dmitry/test/test_file.txt", "w");
    fprintf(f, "a");
    fclose(f);

    Act(args);

    Assert("Bad read from file *");
}

TEST_F(StackAppTest, Print_Warning_On_Bad_Path) {
    args = { "../fasdfasdfasdf/asdfasdfas", "push" };

    Act(args);

    Assert("Cannot read from file *");
}
