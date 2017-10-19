#pragma once
// The file contains a number of functions implemented with recursion or stack

#include<iostream>
#include"util.h"
using std::cout;

unsigned fact_rec(unsigned n) {
    if (n == 0) {
        return 1;
    }
    return n * fact_rec(n - 1);
}

unsigned fact_stack(unsigned n) {
    stack<unsigned> st;
    st.push(n);
    while (!st.empty()) {
        if (st.top() == 0) {
            st.pop();
            unsigned result = 1;
            while (!st.empty()) {
                result *= pop(st);
            }
            return result;
        }
        st.push(st.top() - 1);
    }
}

void print_digits_rec(unsigned n) {
    if (n == 0) {
        return;
    }
    print_digits_rec(n / 10);
    cout << " " << n % 10;
}

void print_digits_stack(unsigned n) {
    stack<unsigned> st;

    while (n > 0) {
        st.push(n % 10);
        n /= 10;
    }
    while (!st.empty()) {
        cout << " " << pop(st);
    }
}

void print_k_rec(unsigned size) {
    if (size == 0) {
        cout << "**\n";
        return;
    }
    cout << "*";
    print_spaces(size);
    cout << "*\n";

    print_k_rec(size - 1);

    cout << "*";
    print_spaces(size);
    cout << "*\n";
}

void print_k_stack(unsigned size) {
    stack<unsigned> st;
    
    while (size > 0) {
        cout << "*";
        print_spaces(size);
        cout << "*\n";
        st.push(size);
        --size;
    }
    cout << "**\n";
    while (!st.empty()) {
        cout << "*";
        print_spaces(pop(st));
        cout << "*\n";
    }
}

// Calculates simple computations like: ((3+((5-1)*9))-(2+6))
int calculate(char* str) {
    stack<char> st;
    char left, operation, right;

    for (unsigned i = 0; str[i] != '\0'; ++i) {
        if (str[i] >= '0' && str[i] <= '9') {
            st.push(str[i] - '0');
        }
        else if (str[i] == ')') {
            right = pop(st);
            operation = pop(st);
            left = pop(st);
            st.push(apply(operation, left, right));
        }
        else if (str[i] == '+' || str[i] == '-' || str[i] == '*') {
            st.push(str[i]);
        }
    }
    return st.top();
}
