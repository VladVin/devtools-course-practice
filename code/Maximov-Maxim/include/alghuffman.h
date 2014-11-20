// Copyright 2014 Maxim Maximov

#ifndef CODE_MAXIMOV_MAXIM_INCLUDE_ALGHUFFMAN_H_
#define CODE_MAXIMOV_MAXIM_INCLUDE_ALGHUFFMAN_H_
#include <string>

#pragma pack(push, 1)
class Node {
 public:
    Node *_left, *_right;
    int _value;
    char _c;

    Node();
    Node(Node *left, Node *right);
    ~Node();
    explicit Node(Node const& copy);
    Node& operator=(const Node& a);
};
#pragma pack(pop)

struct MyCompare {
    bool operator()(const Node* l, const Node* r) {
       return l->_value < r->_value;
    }
};

class HuffmanAlgorithm {
 public:
    HuffmanAlgorithm();
    ~HuffmanAlgorithm();
    explicit HuffmanAlgorithm(HuffmanAlgorithm const& copy);
    HuffmanAlgorithm& operator=(const HuffmanAlgorithm& a);
    std::string code(std::string source);
    std::string decode(std::string source);
    Node *_root;
};

#endif  // CODE_MAXIMOV_MAXIM_INCLUDE_ALGHUFFMAN_H_
