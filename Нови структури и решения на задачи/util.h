#pragma once
// The file containes some short but useful functions

#include<iostream>
#include<stack>
#include<cassert>
using std::cout;
using std::stack;

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

int apply(char operation, int x, int y) {
    switch (operation) {
    case '+': return x + y;
    case '-': return x - y;
    case '*': return x * y;
    case '/': return x / y;
    default: assert(false);     // Giving incorrect "operation" is no good idea 
    }
}