#pragma once
// Everything we need for std::pair

#include<utility>
#include<fstream>
using std::pair;
using std::ostream;

// Useful operator, which is not defined in the library
template<typename X, typename Y>
ostream& operator << (ostream& out, const pair<X, Y>& _pair) {
    out << "{ " << _pair.first << ", " << _pair.second << " }";
    return out;
}