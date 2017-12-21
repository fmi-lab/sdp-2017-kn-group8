#pragma once
#include"HashFn.h"
#include"HashMap.h"

// Similar class in standard library: std::unordered_set (<unordered_set>)

template<typename T>
class UnorderedSet {
    HashMap<T, bool> hm;
public:
    UnorderedSet(const vector<T>& vec = {}, HashFn<T> _f = def_hash_fn<T>) {
        hm = HashMap<T, bool>({}, false, _f);
        for (unsigned i = 0; i < vec.size(); i++) {
            add(vec[i]);
        }
    }

    void add(const T& x) {
        hm[x] = true;
    }
    void remove(const T& x) {
        hm.remove_key(x);
    }
    bool has_element(const T& x) const {
        return hm[x] == true;
    }
    void print() const {
        for (HashMap<T, bool>::Iterator it = hm.begin(); it != hm.end(); ++it) {
            cout << (*it).key << ' ';
        }
        cout << '\n';
    }
};