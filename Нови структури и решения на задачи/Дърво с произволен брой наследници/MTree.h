#pragma once
#include<iostream>
#include<vector>
#include<queue>
using std::cout;
using std::vector;
using std::queue;

template<typename T>
struct Node {
    T data;
    vector<Node*> children;
    Node(const T& _data) : data(_data), children() {}
};

// Multinary tree - each Node can have any number of children

template<typename T>
class MTree {
    Node<T>* root;

public:
    MTree() : root(nullptr) {}
    ~MTree() {
        if (root == nullptr)
            return;
        del(root);
    }

    // 'position' is the position of x's parent.
    // If the tree is empty, what is added is the root, then 'position' doesn't matter
    void add(const T& x, vector<int> position = {}) {
        if (root == nullptr) {
            root = new Node<T>(x);
            return;
        }
        Node<T>* crr = root;
        for (int i = 0; i < position.size(); i++) {
            crr = crr->children[position[i]];
        }
        crr->children.push_back(new Node<T>(x));        // Now crr is x's parent
    }

    void print_dfs() const {
        if (root == nullptr)
            return;
        print_subtree(root);
    }
    
    unsigned count_elements() const {
        if (root == nullptr)
            return 0;

        return count_elements(root);
    }

    void print_bfs() const {
        if (root == nullptr)
            return;
        
        queue<Node<T>*> q;
        q.push(root);

        while (!q.empty()) {
            Node<T>* crr = q.front();
            q.pop();
            cout << crr->data << ' ';
            for (unsigned i = 0; i < crr->children.size(); i++) {
                q.push(crr->children[i]);
            }
        }
    }

private:
    void print_subtree(const Node<T>* sub_root) const {
        cout << sub_root->data << ' ';
        for (unsigned i = 0; i < sub_root->children.size(); i++) {
            print_subtree(sub_root->children[i]);
        }
    }
    
    unsigned count_elements(const Node<T>* sub_root) const {
        unsigned count = 1;
        for (unsigned i = 0; i < sub_root->children.size(); i++) {
            count += count_elements(sub_root->children[i]);
        }
        return count;
    }

    void del(Node<T>*& sub_root) {
        for (unsigned i = 0; i < sub_root->children.size(); i++) {
            del(sub_root->children[i]);
        }
        delete sub_root;
    }
};
