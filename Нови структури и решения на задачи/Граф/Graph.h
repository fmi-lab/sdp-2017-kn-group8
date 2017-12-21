#pragma once
#include<iostream>
#include"ExtendedVector.h"      // <vector> is included in this header
using std::cout;

template<typename T>
class Graph {
    vector<T> vertexes;
    vector<vector<T>> lists;

public:
    Graph(const vector<T>& vec = {})
        : vertexes(vec),
        lists(vec.size(), vector<T>()) {}

    int index_of_vertex(const T& v) {
        return index_of(v, vertexes);
    }

    void add_vertex(const T& v) {
        if (index_of_vertex(v) == -1) {
            vertexes.push_back(v);
            lists.push_back(vector<T>());
        }
    }

    void add_edge(const T& a, const T& b) {
        add_vertex(a);
        add_vertex(b);
        push_if_needed(b, lists[index_of_vertex(a)]);
    }

    // The bug here was in the argument type - 'const T&' is not always safe...
    void remove_vertex(T v) {
        int iv = index_of_vertex(v);
        if (iv == -1) {
            return;
        }
        vertexes.erase(vertexes.begin() + iv);
        lists.erase(lists.begin() + iv);

        for (unsigned i = 0; i < lists.size(); i++) {
            remove_from_vector(v, lists[i]);
        }
    }

    void remove_edge(const T& a, const T& b) {
        int ia = index_of_vertex(a);
        if (ia == -1) {
            return;
        }
        remove_from_vector(b, lists[ia]);
    }

    void print() {
        for (unsigned i = 0; i < vertexes.size(); i++) {
            cout << vertexes[i] << ": ";
            for (unsigned j = 0; j < lists[i].size(); j++) {
                cout << lists[i][j] << ' ';
            }
            cout << '\n';
        }
    }

    void map (T (*f)(const T&)) {
        for (unsigned i = 0; i < vertexes.size(); i++) {
            vertexes[i] = f(vertexes[i]);
        }
        for (unsigned i = 0; i < lists.size(); i++) {
            for (unsigned j = 0; j < lists[i].size(); j++) {
                lists[i][j] = f(lists[i][j]);
            }
        }
    }

    void filter(bool (*pred)(const T&)) {
        unsigned i = 0;
        while (i < vertexes.size()) {
            if (pred(vertexes[i])) {
                i++;
            }
            else {
                remove_vertex(vertexes[i]);
            }
        }
    }
};

// Just for the protocol, putting the test function here is not the best practice.
// But we already do bad things, like keeping the methods' definitions inside the class and testing with 'cout'...
void test_graph() {
    Graph<int> g2({ 1, 2, 3,  4, 6, 7,  8, 9, 15 });

    g2.add_edge(1, 2);
    g2.add_edge(1, 3);
    g2.add_edge(1, 6);
    g2.add_edge(1, 7);

    g2.add_edge(2, 3);
    g2.add_edge(2, 8);
    g2.add_edge(2, 9);

    g2.add_edge(3, 6);
    g2.add_edge(4, 4);
    g2.add_edge(7, 2);
    g2.add_edge(7, 15);

    cout << "Before filter:\n";
    g2.print();
    cout << '\n';

    g2.filter([](const int& x) { return x % 2 == 1; });
    cout << "After filter:\n";
    g2.print();
}