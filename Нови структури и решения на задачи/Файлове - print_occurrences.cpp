#include"main-header.h"         // TODO: replace by all includes

void print_occurrences() {
    ifstream in("file.txt");

    map<string, unsigned> counts;

    string word;

    while (!in.eof()) {
        in >> word;
        if (counts.count(word) == 1) {
            counts[word]++;
        }
        else {
            counts[word] = 1;
        }
    }

    for (map<string, unsigned>::iterator it = counts.begin(); it != counts.end();++it) {
        cout << (*it).first << ": " << (*it).second << '\n';
    }
}

int main() {
    print_occurrences();
    return 0;
}