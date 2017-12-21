#pragma once

// I don't write professional unit tests as we don't really need them now.  (I like the KISS programming principle. :)
// But, we need some tests.

#include<string>
#include<vector>
#include"HashMap.h"
#include"UnorderedSet.h"
#include"OrderedSet.h"
#include"util.h"        // For expect()
using std::string;
using std::vector;

void test_hash() {
    vector<string> names = { "Pesho", "Gosho", "Gosho", "Gosho", "Elena",
                             "Pesho", "Maria", "Maria", "Anita" };

    HashMap<string, unsigned> counts;

    for (unsigned i = 0; i < names.size(); i++) {
        counts[names[i]]++;
    }
    cout << counts;
    expect(
        "Anita: 1\n"          // Did you know that this way you can write a
        "Elena: 1\n"          // string on several lines? What happens is
        "Gosho: 3\n"          // that all the parts are joined in a single
        "Maria: 2\n"          // string, it would be the same if I had written:
        "Pesho: 2\n"          // "Anita: 1\nElena: 1\nGosho: 3\nMaria: 2\nPesho: 2\n"
    );
}

void test_hash_multiplication() {
    HashMap<string, int> hm1;
    HashMap<string, string> hm2;

    hm1["a"] = 11;
    hm1["b"] = 12;
    hm1["c"] = 13;

    hm2["a"] = "aa";
    hm2["c"] = "cc";
    hm2["d"] = "dd";
    
    cout << hm1 * hm2;
    expect(
        "a: { 11, aa }\n"
        "c: { 13, cc }\n"
    );

    cout << (HashMap<int, string>({ {2, "Martin"}, {3, "Display"}, {4, "Panel"} })
             *
             HashMap<int, string>({ {2, "Tita"}, {5, "Antilopa"} }));
    expect("2: { Martin, Tita }");
}

void test_hash_iterator() {
    vector<string> names = { "Pesho", "Gosho", "Gosho", "Gosho", "Elena",
                             "Pesho", "Maria", "Maria", "Anita", "Pavel", "Pavel", "Geri" };

    HashMap<string, unsigned> hm;

    for (unsigned i = 0; i < names.size(); i++) {
        hm[names[i]]++;
    }
    for (HashMap<string, unsigned>::Iterator it = hm.begin(); it != hm.end(); ++it) {
        (*it).print();
    }
    expect(
        "Anita: 1\n"
        "Elena: 1\n"
        "Gosho: 3\n"
        "Geri: 1\n"
        "Maria: 2\n"
        "Pesho: 2\n"
        "Pavel: 2\n"
    );
}

void test_hash_copying() {
    HashMap<char, string> hm({ { 'a', "aa" },{ 'b', "bb" },{ 'c', "cc" } });
    HashMap<char, string> hm1 = hm;
    hm = hm1;
    cout << hm1;
    cout << hm;
    expect(
        "a: aa\n"
        "b: bb\n"
        "c: cc (twice)\n"
    );
}

void test_unordered_set() {
    UnorderedSet<string> s({ "1", "3", "5", "3" });
    s.add("4");
    s.add("4");
    s.add("2");
    s.remove("5");
    s.print();
    expect("1 2 3 4");
}

void test_ordered_set() {
    OrderedSet<string> os({ "a", "kakva", "si", "antilopa", "gazela", "antilopa" });
    os.add("display");
    os.add("panel");
    os.print();
    expect("a antilopa display gazela kakva panel si");

    os.remove("display");
    os.remove("panel");
    os.remove("tita");
    os.print();
    expect("a antilopa gazela kakva si");
}

void run_tests() {
    test_hash();
    test_hash_multiplication();
    test_hash_iterator();
    test_hash_copying();
    test_unordered_set();
    test_ordered_set();
}
