#include"MTree.h"
#include"util.h"
#include<string>
using std::string;

void test_mtree() {
    MTree<string> tree;                     // The tree looks like this:
    tree.add("1");                          // 
    tree.add("2", {});                      //        1
    tree.add("3", {});                      //      / | \ 
    tree.add("4", {});                      //     /  |  \ 
    tree.add("100", { 1 });                 //    2   3   4
    tree.add("200", { 1 });                 //       / \   \ 
    tree.add("300", { 2 });                 //    100  200  300
    tree.add("400", { 1, 1 });              //          |
                                            //         400    
    tree.print_dfs();
    expect("1 2 3 100 200 400 4 300");

    tree.print_bfs();
    expect("1 2 3 4 100 200 300 400");
}