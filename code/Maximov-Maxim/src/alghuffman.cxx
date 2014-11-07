// Copyright 2014 Maxim Maximov
#include "include/alghuffman.h"
#include <stdint.h>
#include <string>
#include <map>
#include <vector>
#include <list>

using std::map;
using std::vector;
using std::list;

Node::Node(Node *_left, Node *_right)
    : left(_left),
      right(_right),
      value(_left->value + right->value),
      c('\0') {
}

Node::Node()
    : left(NULL),
      right(NULL),
      value(0),
      c('\0') {
}

void BuildTable(Node *root, map<char, vector<bool> > *table,
    vector<bool> *code);
Node* CopyTree(Node* tempRoot);
void BuildTable(Node *root, map<char, vector<bool> > *table,
    vector<bool> *code) {
    if (root->left != NULL) {
        code->push_back(0);
        BuildTable(root->left, table, code);
    }

    if (root->right != NULL) {
        code->push_back(1);
        BuildTable(root->right, table, code);
    }

    if (root->c != '\0') (*table)[root->c] = *code;

    code->pop_back();
}

Node* CopyTree(Node* tempRoot) {
    Node* result = new Node;
    result->value = tempRoot->value;
    result->c = tempRoot->c;
    if (tempRoot->right != NULL) result->right = CopyTree(tempRoot->right);
    if (tempRoot->left != NULL) result->left = CopyTree(tempRoot->left);
    return(result);
}

HuffmanAlgorithm::HuffmanAlgorithm():root(NULL) {}
HuffmanAlgorithm::~HuffmanAlgorithm() {}
HuffmanAlgorithm& HuffmanAlgorithm::operator=(const HuffmanAlgorithm& a) {
    this->root = CopyTree(a.root);
    return *this;
    }

HuffmanAlgorithm::HuffmanAlgorithm(HuffmanAlgorithm const& copy)
  : root(NULL) {
    this->root = CopyTree(copy.root);
  }

std::string HuffmanAlgorithm::Code(std::string source) {
    map<char, int> charfreq;
    root = new Node;

    for (unsigned int i = 0; i < source.length(); i++) {
        charfreq[source[i]]++;
    }

    // Make list of nodes

    list<Node*> nodelist;

    for (map<char, int>::iterator itr = charfreq.begin(); itr != charfreq.end();
        ++itr) {
        Node *p = new Node;
        p->c = itr->first;
        p->value = itr->second;
        nodelist.push_back(p);
    }

    // Build tree
    if (nodelist.size() == 1) {
        Node *leaf;
        leaf = new Node;
        leaf->left = nodelist.front();
        root = leaf;
    } else {
        while (nodelist.size() != 1) {
            nodelist.sort(MyCompare());
            Node *sonL = nodelist.front();
            nodelist.pop_front();
            Node *sonR = nodelist.front();
            nodelist.pop_front();
            Node *parent = new Node(sonL, sonR);
            nodelist.push_back(parent);
        }
        root = nodelist.front();  // Save root of our tree
    }

    // Build table with pairs "character - code"

    map<char, vector<bool> > table;
    vector<bool> code;

    BuildTable(root, &table, &code);

    // Build final string

    std::string result;
    for (unsigned int i = 0; i < source.length(); i++) {
        vector<bool> x = table[source[i]];
        for (unsigned int n = 0; n < x.size(); n++) {
            if (x[n])
                result += "1";
            else
                result += "0";
        }
    }
    return(result);
}

std::string HuffmanAlgorithm::Decode(std::string source) {
    Node* p = root;
    std::string result;
    if (p == NULL)
            throw std::string("Have not coded yet");
    for (unsigned int i = 0; i < source.length(); i++) {
        if (source[i] != '1' && source[i] != '0')
            throw std::string("Wrong string");
        if (source[i] == '1')
            p = p->right;
        else
            p = p->left;
        if (p->left == NULL && p->right == NULL) {
            result += p->c;
            p = root;
        }
    }
    return (result);
}
