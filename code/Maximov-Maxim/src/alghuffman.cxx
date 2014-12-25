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

Node::Node(Node *left, Node *right)
    : _left(left),
      _right(right),
      _value(_left->_value + _right->_value),
      _c('\0') {
}

Node::Node()
    : _left(NULL),
      _right(NULL),
      _value(0),
      _c('\0') {
}

Node::~Node() {
    if (_left != NULL) delete _left;
    if (_right != NULL) delete _right;
}

Node::Node(Node const& copy)
    : _left(NULL),
      _right(NULL),
      _value(copy._value),
      _c(copy._c) {
        this->copyTree(&copy);
    }

Node& Node::operator=(const Node& a) {
    this->copyTree(&a);
    return *this;
    }

bool Node::operator<(const Node& a) const {
    return this->_value < a._value;
    }

void Node::copyTree(const Node* tempRoot) {
    _value = tempRoot->_value;
    _c = tempRoot->_c;
    if (tempRoot->_right != NULL) {
        _right = new Node();
        _right->copyTree(tempRoot->_right);
    }
    if (tempRoot->_left != NULL) {
        _left = new Node();
        _left->copyTree(tempRoot->_left);
    }
}

void BuildTable(Node *root, map<char, vector<bool> > *table,
    vector<bool> *key);
void BuildTable(Node *root, map<char, vector<bool> > *table,
    vector<bool> *key) {
    if (root->_left != NULL) {
        key->push_back(0);
        BuildTable(root->_left, table, key);
    }

    if (root->_right != NULL) {
        key->push_back(1);
        BuildTable(root->_right, table, key);
    }

    if (root->_c != '\0') (*table)[root->_c] = *key;

    key->pop_back();
}


HuffmanAlgorithm::HuffmanAlgorithm():_root(NULL) {}
HuffmanAlgorithm::~HuffmanAlgorithm() {
    delete _root;
}
HuffmanAlgorithm& HuffmanAlgorithm::operator=(const HuffmanAlgorithm& a) {
    if (_root ==NULL) _root = new Node();
    _root->copyTree(a._root);
    return *this;
    }

HuffmanAlgorithm::HuffmanAlgorithm(HuffmanAlgorithm const& copy)
  : _root(NULL) {
    _root = new Node();
    _root->copyTree(copy._root);
  }

std::string HuffmanAlgorithm::code(std::string source) {
    map<char, int> charfreq;
    for (unsigned int i = 0; i < source.length(); i++) {
        charfreq[source[i]]++;
    }

    // Make list of nodes

    list<Node> nodelist;

    for (map<char, int>::iterator itr = charfreq.begin(); itr != charfreq.end();
        ++itr) {
        Node p;
        p._c = itr->first;
        p._value = itr->second;
        nodelist.push_back(p);
    }

    // Build tree
    if (_root != NULL) delete _root;
    if (nodelist.size() == 1) {
        _root = new Node();
        _root->_left = new Node(nodelist.front());
    } else {
        while (nodelist.size() != 1) {
            nodelist.sort();
            Node *sonL = new Node(nodelist.front());
            nodelist.pop_front();
            Node *sonR = new Node(nodelist.front());
            nodelist.pop_front();
            Node parent(sonL, sonR);
            nodelist.push_back(parent);
        }
        _root = new Node(nodelist.front());  // Save root of our tree
    }

    // Build table with pairs "character - code"

    map<char, vector<bool> > table;
    vector<bool> key;

    BuildTable(_root, &table, &key);

    // Build final string

    std::string result;
    for (unsigned int i = 0; i < source.length(); i++) {
        vector<bool> x = table[source[i]];
        for (unsigned int n = 0; n < x.size(); n++) {
            result += (x[n]) ? "1" : "0";
        }
    }
    return(result);
}

std::string HuffmanAlgorithm::decode(std::string source) {
    Node* p = _root;
    std::string result;
    if (p == NULL)
            throw std::string("Have not coded yet");
    for (unsigned int i = 0; i < source.length(); i++) {
        if (source[i] != '1' && source[i] != '0')
            throw std::string("Wrong string");
        if (source[i] == '1')
            p = p->_right;
        else
            p = p->_left;
        if (p->_left == NULL && p->_right == NULL) {
            result += p->_c;
            p = _root;
        }
    }
    return (result);
}
