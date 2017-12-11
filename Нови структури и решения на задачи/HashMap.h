#pragma once
#include"ExtendedVector.h"
#include<string>
using std::string;

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
    };

    using HashFn = unsigned(*)(const KeyT&);

    vector<vector<Pair>> table;
    HashFn f;
    ValueT default_value;

public:
    HashMap(HashFn _f, const ValueT& _default_value, unsigned start_size) {
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
 
    ValueT operator [] (const KeyT& key) const {
        if (has_key(key)) {
            return get_value(key);
        }
        return default_value;
    }

    ValueT& operator [] (const KeyT& key) {
        if (!has_key(key)) {
            add_pair(key, default_value);
        }
        return get_value(key);
    }

private:
    // Works only if the key is in the hash
    ValueT& get_value(const KeyT& key) {
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


void test_hash() {
    vector<string> names = { "Pesho", "Gosho", "Gosho", "Gosho", "Elena",
                             "Pesho", "Maria", "Maria", "Anita" };

    HashMap<string, unsigned> counts( [](const string& str) { return unsigned(str[0]); },  0,  50 );

    for (unsigned i = 0; i < names.size(); i++) {
        counts[names[i]]++;
    }

    cout << "Name    People with the name\n";
    for (unsigned i = 0; i < names.size(); i++) {
        cout << names[i] << "   " << counts[names[i]] << '\n';
    }
    cout << "Boyan   " << counts["Boyan"] << '\n';
}
