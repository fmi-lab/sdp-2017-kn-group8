#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include"ExtendedVector.h"
#include"PairHelper.h"      // Everything we need for std::pair
using std::cout;
using std::string;
using std::ostream;

template<typename KeyT>                     // The reason I moved this here will be discussed next time.
using HashFn = unsigned(*)(const KeyT&);

// This HashMap has a 'default' value that 'corresponds' to every key which is not in the hash
template<typename KeyT, typename ValueT>
class HashMap {
    struct Pair {
        KeyT key;
        ValueT value;
        Pair(const KeyT& _key, const ValueT& _value) : key(_key), value(_value) {}

        // DANGEROUS!   (Is it OK to call the pairs <"Burgas", 63> and <"Burgas", 0> equal?)
        bool operator == (const Pair& other) const {
            return key == other.key;
        }
        // Trivial but useful
        void print() const {
            cout << key << ": " << value << '\n';
        }
    };

    vector<vector<Pair>> table;
    HashFn<KeyT> f;
    ValueT default_value;

public:
    HashMap(HashFn<KeyT> _f, const ValueT& _default_value, unsigned start_size) {
        f = _f;
        table = vector<vector<Pair>>(start_size, vector<Pair>());           // table = vector of start_size empty vectors
        default_value = _default_value;
    }

    bool has_key(const KeyT& key) const {
        if (f(key) >= table.size()) {
            return false;
        }
        if (index_of(Pair(key, default_value), table[f(key)]) == -1) {      // Any value can be used here instead of 'default_value'
            return false;
        }
        return true;
    }

    ValueT operator [] (const KeyT& key) const {    // Because this is a 'const' method...
        if (has_key(key)) {
            return get_value(key);                  // ...all the methods called inside must be 'const' too.
        }                                           // So we need a 'const' version of get_value().
        return default_value;
    }

    ValueT& operator [] (const KeyT& key) {
        if (!has_key(key)) {
            add_pair(key, default_value);
        }
        return get_value(key);
    }

    double efficiency() const {
        unsigned all = 0;
        unsigned coliding = 0;

        for (unsigned i = 0; i < table.size(); i++) {
            if (!table[i].empty()) {
                all += table[i].size();
                coliding += table[i].size() - 1;
            }
        }
        if (all == 0) {
            return 1;
        }
        return double(all - coliding) / all;
    }

    // The 'solution' of the 'good function' problem was actually wrong. Sorry.
    // At least this method is correct, so I publish it nevertheless.
    bool has_collisions() const {
        for (unsigned i = 0; i < table.size(); i++) {
            if (table[i].size() >= 2) {
                return true;
            }
        }
        return false;
    }

    template<typename OtherVT>
    HashMap<KeyT, pair<ValueT, OtherVT>> operator* (const HashMap<KeyT, OtherVT>& other) const {
                                                 
        HashMap<KeyT, pair<ValueT, OtherVT>> result(f, pair<ValueT, OtherVT>(), 50);    // Hash function, default value, table size -
                                                                                        // because it's the only constructor we have...
        for (unsigned i = 0; i < table.size(); i++) {
            for (unsigned j = 0; j < table[i].size(); j++) {
                KeyT key = table[i][j].key;

                if (other.has_key(key)) {
                    result[key] = { (*this)[key], other[key] };      // (*this)[key] != *this[key]   !!!
                }
            }
        }
        return result;
    }

    template<typename KeyT, typename ValueT>
    friend ostream& operator << (ostream& out, const HashMap<KeyT, ValueT>& hm);

private:
    // Works only if the key is in the hash
    ValueT& get_value(const KeyT& key) {
        int i = index_of(Pair(key, default_value), table[f(key)]);
        return table[f(key)][i].value;
    }

    // 'const' version of get_value() - it is needed in the 'const' operator[]
    ValueT get_value(const KeyT& key) const {
        int i = index_of(Pair(key, default_value), table[f(key)]);
        return table[f(key)][i].value;
    }

    // We assume the key is not in the hash
    void add_pair(const KeyT& key, const ValueT& value) {
        if (f(key) >= table.size()) {
            resize(f(key) + 1);
        }
        table[f(key)].push_back(Pair(key, value));
    }

    void resize(unsigned new_size) {
        table.resize(new_size, vector<Pair>());
    }
};

template<typename KeyT, typename ValueT>
ostream& operator << (ostream& out, const HashMap<KeyT, ValueT>& hm) {
    for (unsigned i = 0; i < hm.table.size(); i++) {
        for (unsigned j = 0; j < hm.table[i].size(); j++) {
            hm.table[i][j].print();
        }
    }
    return out;
}

void test_hash() {
    vector<string> names = { "Pesho", "Gosho", "Gosho", "Gosho", "Elena",
                             "Pesho", "Maria", "Maria", "Anita" };

    HashMap<string, unsigned> counts([](const string& str) { return unsigned(str[0]); },  0,  50);

    for (unsigned i = 0; i < names.size(); i++) {
        counts[names[i]]++;
    }
    cout << counts;
}

// Test HashMap::operator *
void test_hash_multiplication() {
    HashMap<string, int> hm1    ([](const string& str) { return unsigned(str[0]); }, 0, 50);
    HashMap<string, string> hm2 ([](const string& str) { return unsigned(str[0]); }, "", 50);

    hm1["a"] = 11;
    hm1["b"] = 12;
    hm1["c"] = 13;

    hm2["a"] = "aa";
    hm2["c"] = "cc";
    hm2["d"] = "dd";
    cout << hm1 * hm2;
}