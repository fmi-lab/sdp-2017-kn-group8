#pragma once
#include<iostream>
#include<vector>
using std::cout;
using std::vector;

template<typename T>
int index_of(const T& x, const vector<T>& vec) {
    for (unsigned i = 0; i < vec.size(); i++) {
        if (vec[i] == x)
            return i;
    }
    return -1;
}

template<typename T>
bool has_element(const T& x, const vector<T>& vec) {
    return index_of(x, vec) != -1;
}

template<typename T>
void remove_from_vector(const T& x, vector<T>& vec) {
    int ix = index_of(x, vec);
    if (ix == -1)
        return;
    vec.erase(vec.begin() + ix);
}

template<typename T>
void push_if_needed(const T& x, vector<T>& vec) {
    if (index_of(x, vec) == -1)
        vec.push_back(x);
}

template<typename T>
void print_vector(const vector<T>& vec) {
    for (unsigned i = 0; i < vec.size(); i++)
        cout << vec[i] << ' ';
}
