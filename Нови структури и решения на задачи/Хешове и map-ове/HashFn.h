#pragma once
#include<string>
using std::string;

template<typename KeyT>
using HashFn = unsigned(*)(const KeyT&);

// Default hash functions
template<typename KeyT>
unsigned def_hash_fn(const KeyT& key) {
    return 0;
}

template<>                                              // 'template<>' is needed syntax. Without it,
unsigned def_hash_fn<string>(const string& str) {       // def_hash_fn<string>("abc") would call the above 'return 0' function,
    return unsigned(str[0]);                            // not the 'return unsigned(str[0])' function as we want.
}

template<>
unsigned def_hash_fn(const char& ch) {
    return unsigned(ch);
}

template<>
unsigned def_hash_fn(const unsigned& x) {
    return x;                                   // Nice!
}

template<>
unsigned def_hash_fn(const int& x) {
    if (x <= 0) {
        return unsigned(-2 * x);
    }
    return unsigned(2 * x - 1);
}
