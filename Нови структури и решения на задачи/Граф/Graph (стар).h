#pragma once
#include<iostream>
#include<queue>
#include<set>
#include"ExtendedVector.h"
using std::cout;
using std::queue;
using std::set;

template<typename T>
class Graph {
    vector<T> vertexes;
    vector<vector<T>> lists;

public:
    Graph(const vector<T>& vec = {})
        : vertexes(vec),
        lists(vec.size(), vector<T>()) {}

    int index_of_vertex(const T& v) const {
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

    bool has_vertex(const T& v) const {
        return index_of_vertex(v) != -1;
    }
    bool has_edge(const T& a, const T& b) const {
        return has_vertex(a) && has_vertex(b) &&
            index_of(b, neighbours_of(a)) != -1;
    }
    vector<T> neighbours_of(const T& v) const {
        return lists[index_of_vertex(v)];
    }

    // I changed 'visited' to be a set. This doesn't change the algorithm a lot
    bool has_path(const T& a, const T& b) const {
        set<T> visited;
        return has_path(a, b, visited);
    }
    bool has_path(const T& a, const T& b, set<T>& visited) const {
        if (a == b) {
            return true;
        }
        visited.insert(a);
        vector<T> neighbours = neighbours_of(a);
        for (int i = 0; i < neighbours.size(); i++) {
            if (visited.count(neighbours[i]) == 0 && has_path(neighbours[i], b))
                return true;
        }
        return false;
    }

    void print_bfs(const T& start) const {
        set<T> visited;
        visited.insert(start);

        queue<T> q;
        q.push(start);

        while (!q.empty()) {
            T crr = q.front();
            q.pop();
            cout << crr << ' ';

            vector<T> neighbours = neighbours_of(crr);
            
            for (unsigned i = 0; i < neighbours.size(); i++) {
                if (!visited.count(neighbours[i]) == 1) {         // if neighbours[i] is visited
                    q.push(neighbours[i]);
                    visited.insert(neighbours[i]);                // I had to move the insertion here,
                }                                                 // we'll see why today (18.01.2018)
            }
        }
    }
    
    void print_dfs(const T& start) {
        set<T> visited;
        visited.insert(start);
        print_dfs(start, visited);
    }
    void print_dfs(const T& start, set<T>& visited) {
        cout << start << ' ';
        vector<T> neighbours = neighbours_of(start);

        for (unsigned i = 0; i < neighbours.size(); i++) {
            if (!visited.count(neighbours[i]) == 1) {            // if neighbours[i] is visited
                visited.insert(neighbours[i]);
                print_dfs(neighbours[i], visited);
            }
        }
    }
};

#include"util.h"            // expect()
#include"string"
using std::string;

void test_graph() {
    Graph<string> g({ "Montana", "Lovech",  "Ruse"              // Everything is connected
                      "Sofia",   "Tarnovo", "Varna",            // to what is just under it
                      "Dupnica", "Plovdiv", "Burgas" });        // or just right to it

    g.add_edge("Montana", "Sofia");      g.add_edge("Lovech", "Tarnovo");       
    g.add_edge("Montana", "Lovech");     g.add_edge("Lovech", "Ruse");         g.add_edge("Ruse", "Varna");

    g.add_edge("Sofia", "Dupnica");      g.add_edge("Tarnovo", "Plovdiv");
    g.add_edge("Sofia", "Tarnovo");      g.add_edge("Tarnovo", "Varna");       g.add_edge("Varna", "Burgas");
         
    g.add_edge("Dupnica", "Plovdiv");    g.add_edge("Plovdiv", "Burgas");


    cout << "has_path:\n\n"
         << g.has_path("Lovech", "Plovdiv")
         << g.has_path("Montana", "Burgas")
         << g.has_path("Sofia", "Ruse");
    expect("110");

    cout << "BFS:\n\n";
    g.print_bfs("Montana");
    expect("Montana Sofia Lovech Dupnica Tarnovo Ruse Plovdiv Varna Burgas");

    cout << "DFS:\n\n";
    g.print_dfs("Montana");
    expect("Montana Sofia Dupnica Plovdiv Burgas Tarnovo Varna Lovech Ruse");
}
