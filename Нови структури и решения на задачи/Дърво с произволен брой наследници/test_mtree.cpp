#include"MTree.h"
#include"util.h"
#include<string>
using std::string;

void test_mtree() {
    MTree<string> tree;
    tree.add("1", {});
    tree.add("2", {});
    tree.add("3", {});
    tree.add("4", {});
    tree.add("100", { 1 });
    tree.add("200", { 1 });
    tree.add("300", { 2 });
    tree.add("400", { 1, 1 });
    tree.print_dfs();
    expect("1 2 3 100 200 400 4 300");

    tree.print_bfs();
    expect("1 2 3 4 100 200 300 400");
}

int main() {
    test_mtree();
    return 0;
}