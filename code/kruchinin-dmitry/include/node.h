// Copyright 2014 Dmitry Kruchinin

#ifndef CODE_KRUCHININ_DMITRY_INCLUDE_NODE_H_
#define CODE_KRUCHININ_DMITRY_INCLUDE_NODE_H_

#pragma pack(push, 1)
template <typename Type>
struct Node {
    Node* next;
    Type element;
    Node(Type element_, Node* next_):
        next(next_), element(element_) {}
};
#pragma pack(pop)

#endif  // CODE_KRUCHININ_DMITRY_INCLUDE_NODE_H_
