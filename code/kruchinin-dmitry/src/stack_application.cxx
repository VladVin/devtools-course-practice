// Copyright 2013 Dmitry Kruchinin

#include <stdio.h>
#include <string>
#include <vector>
#include <stdexcept>

#include "include/stack.h"
#include "include/stack_application.h"

#define str_size_type std::basic_string<char>::size_type

StackApplication::StackApplication() {}

void StackApplication::help() {
    std::string message = std::string("Stack of integer numbers\n") +
                "Usage:\n" +
                "\t push [number1, number2, ...]\n" +
                "\t pop [option]\n" +
                "\t top\n" +
                "\t exit\n\n" +
                "Pop options:\n" +
                "\t number of elements to pop\n" +
                "\t -all\n";
    printf("%s\n", message.c_str());
}

static void separator(std::string str, std::vector<std::string> *split_str) {
    int j = 0;
    for (int i = 0; static_cast<uint>(i) < str.length(); i++) {
        if (str[static_cast<str_size_type>(i)] == ' ') {
            if (i == j) {
                j++;
                continue;
            }

            split_str->push_back(
                str.substr(static_cast<str_size_type>(j),
                        static_cast<str_size_type>(i - j)));
            j = i + 1;
        }
    }
    split_str->push_back(str.substr(
        static_cast<str_size_type>(j),
        str.size() - static_cast<str_size_type>(j)));
}

bool StackApplication::get_int(const std::string &str,
                    const char *exc_type, const char *exc_size,
                    int &number) {
    try {
        number = static_cast<int>(std::stoi(str));
    }
    catch(const std::invalid_argument &exc) {
        printf("%s\n", exc_type);
        help();
        return false;
    }
    catch(const std::out_of_range &exc) {
        printf("%s\n", exc_size);
        help();
        return false;
    }
    return true;
}

bool StackApplication::parseCommand(Stack<int> *stack) {
    char *lineptr = NULL;
    size_t dd = 0;
    int len = static_cast<int>(getline(&lineptr, &dd, stdin)) - 1;
    std::string line(lineptr, static_cast<str_size_type>(len));
    free(lineptr);

    std::vector<std::string> split_str;
    separator(line, &split_str);

    const std::string keywords[] = {
        "push", "pop", "-all", "top", "exit"
    };

    if (keywords[0].compare(split_str[0]) == 0) {
        if (split_str.size() == 1) {
            printf("Too few arguments\n");
            return true;
        }

        for (uint i = 1; i < split_str.size(); i++) {
            int n = 0;
            if (get_int(
                    split_str[i],
                    "Invalid argument for push (not a number)",
                    "Too big number to push",
                    n) == false) {
                return true;
            }

            stack->push(n);
        }

    } else if (keywords[1].compare(split_str[0]) == 0) {
        if (split_str.size() == 1) {
            printf("Too few arguments\n");
            return true;
        }

        int n = 0;
        if (keywords[2].compare(split_str[1]) == 0) {
            while (!stack->isEmpty()) {
                printf("%d\n", stack->pop());
            }
            printf("\n");
            return true;
        }
        if (get_int(
                split_str[1],
                "Invalid argument for pop (not a number)",
                "Too big number to pop",
                n) == false) {
            return true;
        }

        for (int i = 0; i < n; i++) {
            try {
                printf("%d\n", stack->pop());
            }
            catch(const std::runtime_error &exc) {
                printf("Stack is empty\n");
                return true;
            }
        }
        printf("\n");

    } else if (keywords[3].compare(split_str[0]) == 0) {
        try {
            printf("%d\n", stack->top());
        }
        catch(const std::runtime_error &exc) {
            printf("Stack is empty\n");
            return true;
        }

    } else if (keywords[4].compare(split_str[0]) == 0) {
        printf("--------------Bye!--------------\n");
        return false;

    } else {
        printf("Unknown command\n");
    }

    return true;
}

void StackApplication::run() {
    Stack<int> stack;
    help();
    while (parseCommand(&stack)) {}
}
