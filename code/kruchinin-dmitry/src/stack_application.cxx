// Copyright 2014 Dmitry Kruchinin

#include <stdio.h>
#include <string>
#include <vector>
#include <stdexcept>

#include "include/stack.h"
#include "include/stack_application.h"

StackApplication::StackApplication() : message() {}

void StackApplication::help() {
    message += std::string("Stack of integer numbers\n\n") +
                "Usage: <file> <command> <cmnd_options>\n" +
                "\t file must contain the numbers in rows,\n" +
                "\t the top of the stack is the last element\n" +
                "\t push [number1, number2, ...]\n" +
                "\t pop [option]\n" +
                "\t top\n\n" +
                "Pop options:\n" +
                "\t number of elements to pop\n" +
                "\t -all\n";
}

static bool get_int(const std::string &str,
                    const char *exc_type, const char *exc_size,
                    int &number, std::string *output) {
    try {
        number = static_cast<int>(std::stoi(str));
    }
    catch(const std::invalid_argument) {
        *output += exc_type + std::string("\n");
        return false;
    }
    catch(const std::out_of_range) {
        *output += exc_size + std::string("\n");
        return false;
    }
    return true;
}

static bool read_file(const char *path, Stack<int> *stack,
                      std::string *output) {
    FILE* f;
    if (!(f = fopen(path, "r"))) {
        *output += std::string("Cannot read from file ") +
                    std::string(path) + "\n";
        return false;
    }

    int n = 0;
    int count = fscanf(f, "%d", &n);
    while (count != EOF) {
        if (count == 0) {
            *output += std::string("Bad read from file ") +
                        std::string(path) + "\n";
            return false;
        }
        stack->push(n);
        count = fscanf(f, "%d", &n);
    }

    fclose(f);
    return true;
}

static void write_file(const char *path, Stack<int> *stack) {
    FILE* f = fopen(path, "w");

    Stack<int> tmp;
    while (!stack->isEmpty()) {
        tmp.push(stack->pop());
    }
    while (!tmp.isEmpty()) {
        fprintf(f, "%d\n", tmp.pop());
    }

    fclose(f);
}

void StackApplication::parseCommand_and_Run(int argc, char *argv[]) {
    if (argc <= 2) {
        message += "Too few arguments\n";
        help();
        return;
    }

    Stack<int> stack;
    const char *path = argv[1];
    if (!read_file(path, &stack, &message)) {
        help();
        return;
    }

    const uint len = static_cast<uint>(argc - 2);
    std::vector<std::string> args(len);
    for (uint i = 0; i < len; i++) {
        args[i] = argv[i + 2];
    }

    const std::string keywords[] = {
        "push", "pop", "-all", "top"
    };
    enum {
        PUSH, POP, ALL, TOP
    };

    if (keywords[PUSH].compare(args[0]) == 0) {
        if (args.size() == 1) {
            message += std::string("Too few arguments\n");
            help();
            return;
        }

        for (uint i = 1; i < args.size(); i++) {
            int n = 0;
            if (get_int(
                    args[i],
                    "Invalid argument for push (not a number)",
                    "Too big number to push",
                    n, &message) == false) {
                help();
                return;
            }

            stack.push(n);
            message += std::to_string(stack.top()) + std::string("\n");
        }
    } else if (keywords[POP].compare(args[0]) == 0) {
        if (args.size() == 1) {
            message += std::string("Too few arguments\n");
            help();
            return;
        }

        if (keywords[ALL].compare(args[1]) == 0) {
            while (!stack.isEmpty()) {
                message += std::to_string(stack.pop()) + "\n";
            }
            message += std::string("\n");
            write_file(path, &stack);
            return;
        }

        int n = 0;
        if (get_int(
                args[1],
                "Invalid argument for pop (not a number)",
                "Too big number to pop",
                n, &message) == false) {
            help();
            return;
        }
        for (int i = 0; i < n; i++) {
            try {
                message += std::to_string(stack.pop()) + "\n";
            }
            catch(const std::runtime_error) {
                message += std::string("Stack is empty\n");
                return;
            }
        }
        message += std::string("\n");

    } else if (keywords[TOP].compare(args[0]) == 0) {
        try {
            message += std::to_string(stack.top()) + "\n";
        }
        catch(const std::runtime_error) {
            message += std::string("Stack is empty\n");
            return;
        }

    } else {
        message += std::string("Unknown command\n");
    }

    write_file(path, &stack);
}

std::string StackApplication::operator()(int argc, char *argv[]) {
    parseCommand_and_Run(argc, argv);
    return message;
}
