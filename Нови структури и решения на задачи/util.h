#pragma once
#include<iostream>
#include<stack>
using std::cout;
using std::stack;

void expect(const char* output) {                   // Useful for short tests
    cout << "\nExpected:\n" << output << "\n\n";
}

void print_spaces(unsigned n) {
    for (unsigned i = 0; i < n; ++i) {
        cout << ' ';
    }
}

template<typename T>
T pop(stack<T>& s) {
    T top = s.top();
    s.pop();
    return top;
}