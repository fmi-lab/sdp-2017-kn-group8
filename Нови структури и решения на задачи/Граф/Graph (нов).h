#pragma once
#include"ExtendedVector.h"
#include"HashMap.h"
#include<set>
using std::set;

template<typename T>
class Graph {
    vector<T> vertexes;                         // Vector of all the vertexes.

    HashMap<T, int> ids;                        // Each vertex has an ID - its index in 'vertexes'.
                                                // If a vertex is not in the graph its ID will be -1.

    vector<set<unsigned>> sets;                 // Each vertex has a set of neighbours.
                                                // In the sets, vertexes are represented by their IDs.
public:
    Graph(const vector<T>& vec) : vertexes(vec), sets(vec.size(), {}), ids({}, -1) {      // The constructor creates graph with
        for (unsigned i = 0; i < vertexes.size(); i++) {                                  // the given vertexes and no edges,
            ids[vertexes[i]] = i;                                                         // setting each vertex's ID.
        }
    }
    
    void add_vertex(const T& v) {
        if (!has_vertex(v)) {
            vertexes.push_back(v);
            sets.push_back({});
            ids[v] = vertexes.size() - 1;
        }
    }

    void add_edge(const T& a, const T& b) {
        add_vertex(a);
        add_vertex(b);
        set_of(a).insert(ids[b]);               // <=> set_of(a).insert(index_of(b, vertexes));
    }

    void remove_vertex(const T& v) {
        if (!has_vertex(v)) {
            return;
        }
        set_of(v) = {};
        for (unsigned i = 0; i < sets.size(); i++) {
            sets[i].erase(ids[v]);
        }
        ids[v] = -1;
    }

    void remove_edge(const T& a, const T& b) {
        set_of(a).erase(ids[b]);
    }

    bool has_vertex(const T& v) const {
        return ids[v] != -1;
    }

    bool has_edge(const T& a, const T& b) const {
        return has_vertex(a) && has_vertex(b) && set_of(a).count(ids[b]) == 1;      // set_of(a).count(ids[b]) == 1 <=>
    }                                                                               // sef_of(a) has element ids[b]

    void print_vertexes() {
        for (unsigned i = 0; i < vertexes.size(); i++) {
            if (has_vertex(vertexes[i]))
                cout << vertexes[i] << ' ';
        }
    }

    void print() {
        for (unsigned i = 0; i < vertexes.size(); i++) {
            T v = vertexes[i];
            if (has_vertex(v)) {
                cout << v << " -> ";
                for (set<unsigned>::iterator it = set_of(v).begin(); it != set_of(v).end(); ++it) {
                    cout << vertexes[*it] << ' ';
                }
                cout << '\n';
            }
        }
    }

private:
    set<unsigned>& set_of(const T& v) {
        return sets[index_of(v, vertexes)];
    }
    set<unsigned> set_of(const T& v) const {
        return sets[index_of(v, vertexes)];
    }
};

// I changed the test a little so that it tests every method
void test_graph() {
    Graph<string> g({ "Sofia", "Varna", "Plovdiv" });

    g.add_vertex("Burgas");
    g.add_vertex("Burgas");

    g.add_edge("Sofia", "Sofia");
    g.add_edge("Sofia", "Varna");
    
    g.remove_vertex("Varna");
    
    g.add_edge("Burgas",  "M.Tarnovo");
    g.add_edge("Sofia",   "Burgas");
    g.add_edge("Plovdiv", "Burgas");
    
    g.remove_edge("Plovdiv", "Burgas");
    
    g.print_vertexes();
    expect("Sofia Plovdiv Burgas M.Tarnovo");

    g.print();
    expect(
        "Sofia -> Sofia Burgas\n"           // This is a way to write a string on multiple lines.
        "Plovdiv ->\n"                      // "When" "You" "Write" "This" "Way", it is the same as
        "Burgas -> M.Tarnovo\n"             // "WhenYouWriteThisWay" - the compiler unites
        "M.Tarnovo ->\n"                    // everything into a single char*.
    );

    for (string city : { "Sofia", "Plovdiv", "Varna", "Burgas", "M.Tarnovo", "Kiustendil" }) {      // Try to understand
        cout << g.has_vertex(city);                                                                 // what I do here
    }                                                                                               // without knowing
    expect("110110");                                                                               // the syntax. :)

    cout << g.has_edge("Burgas", "M.Tarnovo")
         << g.has_edge("Plovdiv", "Burgas")
         << g.has_edge("Sofia", "Kiustendil");
    expect("100");
};