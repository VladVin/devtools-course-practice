// Copyright 2014 Dmitry Kruchinin

#ifndef CODE_KRUCHININ_DMITRY_INCLUDE_STACK_H_
#define CODE_KRUCHININ_DMITRY_INCLUDE_STACK_H_

#include <string>
#include <stdexcept>

#include "include/node.h"

template <typename Type>
class Stack {
 public:
    Stack() : tail(NULL), size(0) {}

    ~Stack() {
        Node<Type>* tmp = tail;
        while (tmp) {
            tmp = tail->next;
            delete tail;
            tail = tmp;
        }
    }

    Stack<Type>(const Stack<Type>& stack) {
        Stack<Type> tmp;

        while (!stack.isEmpty()) {
            tmp.push(stack.pop());
        }
        while (!tmp.isEmpty()) {
            stack.push(tmp.top());
            this->push(tmp.pop());
        }
    }

    Stack<Type>& operator=(const Stack<Type>& stack) {
        Stack<Type> tmp;

        while (!stack.isEmpty()) {
            tmp.push(stack.pop());
        }
        while (!tmp.isEmpty()) {
            stack.push(tmp.top());
            this->push(tmp.pop());
        }

        return *this;
    }

    void push(Type element) {
        Node<Type>* tmp = new Node<Type>(element, tail);
        size++;
        tail = tmp;
    }

    Type pop() {
        if (size == 0) {
            throw std::runtime_error("Stack is empty");
        } else {
            Type Element = tail->element;
            Node<Type>* tmp = tail->next;
            delete tail;
            size--;

            tail = tmp;
            return Element;
        }
    }

    Type top() {
        if (size == 0)
            throw std::runtime_error("Stack is empty");
        else
            return tail->element;
    }

    bool isEmpty() {
        return (size == 0);
    }

 private:
    Node<Type>* tail;
    int size;
};

#endif  // CODE_KRUCHININ_DMITRY_INCLUDE_STACK_H_
