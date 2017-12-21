#pragma once
#include"OrderedTree.h"

// Similar class in standard library: std::set (<set>)

template<typename T>
class OrderedSet {
    OrderedTree<T> tree;

public:
    OrderedSet(const vector<T>& vec = {}) : tree(vec) {}

    // TODO:  write OrderedTree::has_element()
    bool has_element(const T& x) const {
        // return tree.has_element();
        return false;
    }

    void add(const T& x) {
        tree.add(x);
    }
    void remove(const T& x) {
        tree.remove(x);
    }
    void print() const {
        tree.print_ordered();
        cout << '\n';
    }
};