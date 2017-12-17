// Not exactly unit tests, but still not bad for checking whether the functions work

#include<iostream>
#include"rec-vs-stack.h"

void test_calculator() {
    cout << calculate("((3+((5-1)*9))-(2+6))");  // Expected: 31
    cout << '\n';
}

void test_print_digits() {
    print_digits_rec(18102017);
    cout << '\n';
    print_digits_stack(18102017);
    cout << '\n';
    print_digits_rec(8);
    cout << '\n';
    print_digits_stack(8);
    cout << '\n'; 
    print_digits_rec(0);
    cout << '\n';
    print_digits_stack(0);
    cout << '\n';
}

void test_k() {
    print_k_rec(0);
    print_k_stack(0);
    print_k_rec(4);
    print_k_stack(4);
}

int main() {
    test_calculator();
    test_print_digits();
    test_k();
    return 0;
}