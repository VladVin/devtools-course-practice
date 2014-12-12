// Copyright 2014 Dmitry Kruchinin

#ifndef CODE_KRUCHININ_DMITRY_INCLUDE_NODE_H_
#define CODE_KRUCHININ_DMITRY_INCLUDE_NODE_H_

template <typename Type>
struct Node {
    Type element;
    Node* next;
    Node(Type element_, Node* next_):
        element(element_), next(next_) {}
};

#endif  // CODE_KRUCHININ_DMITRY_INCLUDE_NODE_H_
