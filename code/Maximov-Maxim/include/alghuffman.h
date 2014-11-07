// Copyright 2014 Maxim Maximov

#ifndef CODE_MAXIMOV_MAXIM_INCLUDE_ALGHUFFMAN_H_
#define CODE_MAXIMOV_MAXIM_INCLUDE_ALGHUFFMAN_H_
#include <string>

class Node {
 public:
    Node *left, *right;
    int value;
    char c;

    Node();
    Node(Node *_left, Node *_right);
};

struct MyCompare {
    bool operator()(const Node* l, const Node* r) {  // need more const??
       return l->value < r->value;
    }
};

class HuffmanAlgorithm {
 public:
    HuffmanAlgorithm();
    ~HuffmanAlgorithm();
    explicit HuffmanAlgorithm(HuffmanAlgorithm const& copy);
    HuffmanAlgorithm& operator=(const HuffmanAlgorithm& a);
    std::string Code(std::string source);
    std::string Decode(std::string source);
    Node *root;
};

#endif  // CODE_MAXIMOV_MAXIM_INCLUDE_ALGHUFFMAN_H_
