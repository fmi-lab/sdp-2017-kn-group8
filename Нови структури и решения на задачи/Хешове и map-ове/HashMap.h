#pragma once
#include<iostream>
#include<fstream>
#include"ExtendedVector.h"
#include"PairHelper.h"      // Everything we need for std::pair.
#include"HashFn.h"          // HashFn type and default hash functions.
using std::cout;
using std::ostream;

// This HashMap has a 'default' value that 'corresponds' to every key which is not in the hash
template<typename KeyT, typename ValueT>
class HashMap {
    struct Pair {
        KeyT key;
        ValueT value;
        Pair(const KeyT& _key, const ValueT& _value) : key(_key), value(_value) {}
        
        Pair(const KeyT& _key) : key(_key) {}       // Not written in class but easy and useful

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
    class Iterator {
        unsigned row;                           // The HashMap is, in its base, a table.
        unsigned col;                           // We can describe a 'cell' in the table with its row and column.
        const vector<vector<Pair>>* table;      // We also need a table. (The Iterator is a different object, 
                                                // it doesn't see the 'table' chlen-danna of the HashMap.)
                                                
        unsigned next_nonempty_row() {
            unsigned i = row + 1;
            while (i < table->size() && (*table)[i].empty()) {
                i++;
            }
            return i;
        }
    public:
        Iterator(const vector<vector<Pair>>& _table, unsigned _row) {
            table = &_table;
            row = _row;
            col = 0;
        }
        bool operator != (const Iterator& other) const {
            return row != other.row || col != other.col;
        }
        void operator++ () {
            col++;
            if (col >= (*table)[row].size()) {
                row = next_nonempty_row();              // It's possible that next_nonempty_row() returns table.size()
                col = 0;                                // This is ok, the iterator then 'points' to 'end()';
            }
        }
        Pair operator* () const {
            return (*table)[row][col];
        }
    };
    
    Iterator begin() const {
        unsigned i = 0;
        while (i < table.size() && table[i].empty()) {
            i++;
        }
        return Iterator(table, i);      // i is the index of the first non-empty row (or table.size(), if all rows are empty)
    }
    Iterator end() const {
        return Iterator(table, table.size());       // There is no 'table.size()'-th row
    }

    HashMap(
        const vector<Pair>& _pairs = {},
        const ValueT& _default_value = ValueT(),
        HashFn<KeyT> _f = def_hash_fn<KeyT>,
        unsigned start_size = 128
    ){
        f = _f;
        table = vector<vector<Pair>>(start_size, {});           // {} == empty vector
        default_value = _default_value;
        for (unsigned i = 0; i < _pairs.size(); i++) {
            add_pair(_pairs[i]);                                // See add_pair() in the private section.
        }
    }

    // Let the class be complete
    HashMap(const HashMap<KeyT, ValueT>& other) {
        f = other.f;
        table = other.table;
        default_value = other.default_value;
    }
    HashMap<KeyT, ValueT>& operator= (const HashMap<KeyT, ValueT>& other) {
        f = other.f;
        table = other.table;
        default_value = other.default_value;
        return *this;
    }

    void remove_key(const KeyT& key) {                          // I wrote one-argument constructor for Pair because:
        remove_from_vector(Pair(key), table[f(key)]);           // 1. The value of the temporary pair is never used
    }                                                           // 2. I think 'Pair(key, default_value)' was ugly and confusing.

    bool has_key(const KeyT& key) const {                                               // At FMI we wrote 7 lines for this method
        return f(key) < table.size()  &&  index_of(Pair(key), table[f(key)]) != -1;     // but they can be shortened easily.
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

    bool has_collisions() const {
        for (unsigned i = 0; i < table.size(); i++) {
            if (table[i].size() >= 2)
                return true;
        }
        return false;
    }

    template<typename OtherVT>
    HashMap<KeyT, pair<ValueT, OtherVT>> operator* (const HashMap<KeyT, OtherVT>& other) const {
                                                                                                        // The logical default value for the result is
        HashMap<KeyT, pair<ValueT, OtherVT>> result({}, { default_value, other.default_value }, f);     // the pair of the 2 default values. We need to
                                                                                                        // specify f, because KeyT might be a 'bad' type,
                                                                                                        // whose 'def_hash_fn' is 'return 0'.
        for (HashMap<KeyT, ValueT>::Iterator it = begin(); it != end(); ++it) {
            KeyT key = (*it).key;
            if (other.has_key(key)) {
                result[key] = { (*this)[key], other[key] };             // (*this)[key] != *this[key]   !!!
            }
        }
        return result;
    }

    template<typename KeyT, typename ValueT>
    friend ostream& operator << (ostream& out, const HashMap<KeyT, ValueT>& hm);

    template<typename OtherKT, typename OtherVT>        // Why make a class a friend to itself? Well, we don' do exactly this.
    friend class HashMap;                               // HashMap<string, int> and HashMap<string, char> are DIFFERENT classes.
                                                        // So we actually say that all the HashMap-s are friends of our HashMap.
                                                        // In operator* the HashMap needs to access the private things of another HashMap.
private:
    // Works only if the key is in the hash
    ValueT& get_value(const KeyT& key) {
        int i = index_of(Pair(key), table[f(key)]);
        return table[f(key)][i].value;
    }

    // 'const' version of get_value() - it is needed in the 'const' operator[]
    ValueT get_value(const KeyT& key) const {
        int i = index_of(Pair(key), table[f(key)]);
        return table[f(key)][i].value;
    }

    // We assume the key is not in the hash
    void add_pair(const KeyT& key, const ValueT& value) {
        if (f(key) >= table.size()) {
            resize(f(key) + 1);
        }
        table[f(key)].push_back(Pair(key, value));
    }

    void add_pair(const Pair& _pair) {              // Not written at class, but easy and useful
        add_pair(_pair.key, _pair.value);
    }

    void resize(unsigned new_size) {
        table.resize(new_size, {});         // {} == empty vector
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
