#pragma once
#include<vector>
using std::vector;

template<typename ValueT>
class Trie {
    struct Node {
        char symbol;
        ValueT* value;
        vector<Node*> children;
        Node(char _symbol, const ValueT& _value) {
            symbol = _symbol;
            value = new ValueT(_value);
            children = {};
        }
        Node(char _symbol) {
            symbol = _symbol;
            value = nullptr;
            children = {};
        }
    };

    Node* root;
public:
    Trie() {
        root = new Node('\0');
    }

    ValueT operator [](const string& key) const {
        // ...
    }
    ValueT& operator [](const string& key) {
        // ...
    }
};