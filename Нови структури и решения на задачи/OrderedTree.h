// WARNING: Not tested code.
// Probably contains small mistakes.

#pragma once
#include<iostream>
#include"util.h"
using std::cout;

template<typename T>
struct Node {
    T data;
    Node<T>* left;
    Node<T>* right;
    int balance_factor;              // The additional variable does not break anything in the big class...

    Node(const T& _data)
        : data(_data), left(nullptr), right(nullptr), balance_factor(0) {}    // ...although we use it here

    bool childless() const {
        return left == nullptr && right == nullptr;
    }
};


template<typename T>
class OrderedTree {
    Node<T>* root;
    
public:
    OrderedTree() : root(nullptr) {}
    ~OrderedTree() {
        del(root);
    }
    
    void print_ordered() const {
        print_ordered(root);
    }
    void print_hierarchy() const {
        print_hierarchy(root, 0);
    }

    void add(const T& x) {
        add_to_subtree(x, root);
    }

    void remove(const T& x) {
        remove(x, root);
    }

private:
    void add_to_subtree(const T& x, Node<T>*& sub_root) {
        if (sub_root == nullptr) {
            sub_root = new Node<T>(x);
            return;
        }
        if (x < sub_root->data) {
            add_to_subtree(sub_root->left);
            return;
        }
        add_to_subtree(sub_root->right);
    }
    
    void remove_from_subtree(const T& x, Node<T>*& sub_root) {
        if (sub_root == nullptr) {
            return;
        }
        if (x == sub_root->data) {
            remove_node(sub_root);      // 30-lines long cases - in a separate function!
            return;
        }
        if (x < sub_root->data) {
            remove_from_subtree(x, sub_root->left);
            return;
        }
        remove_from_subtree(x, sub_root->right);
    }


    // Removes node, keeping the tree ordered
    // I kept the name 'sub_root' because we need to work with the whole subtree
    void remove_node(Node<T>*& sub_root) {

        // Case 1:   Empty tree in one direction
        // Solution: We put the non-empty tree at the deleted node's place
        if (sub_root->left == nullptr) {
            Node<T>* old = sub_root;
            sub_root = sub_root->right;
            delete old;
            return;
        }
        if (sub_root->right == nullptr) {
            Node<T>* old = sub_root;
            sub_root = sub_root->left;
            delete old;
            return;
        }

        // Case 2:   Non-empty left subtree, whose right subtree is empty   (whether or not 'whose' is grammatically correct)
        // Solution: Left root easily becomes root of the whole subtree
        if (sub_root->left->right == nullptr) {
            Node<T>* new_root = sub_root->left;
            new_root->right = sub_root->right;
            delete sub_root;
            sub_root = new_root;
            return;
        }

        // Case 3:   Left subtree has max element > left root
        // Solution: We choose this element for root of the whole subtree
        Node<T>* iter = sub_root->left;
        while (iter->right->right != nullptr) {     // After the loop, max will be in iter->right
            iter = iter->right;
        }
        sub_root->data = iter->right->data;
        delete iter->right;
        iter->right = nullptr;
    }


    // We'll see how exactly to use rotations later
    void rotate_left(Node<T>*& sub_root) {
        Node<T>* temp = sub_root->right;
        sub_root->right = temp->left;
        temp->left = sub_root;
        sub_root = temp;
    }

    void del(Node<T>*& sub_root) {
        if (sub_root == nullptr) {
            return;
        }
        del(sub_root->left);
        del(sub_root->right);
        delete sub_root;
    }
    void print_ordered(Node<T>* sub_root) const {
        if (sub_root == nullptr) {
            return;
        }
        print_ordered(sub_root->left);
        cout << sub_root->data << " ";
        print_ordered(sub_root->right);
    }
    void print_hierarchy(Node<T>* sub_root, unsigned spaces) const {
        if (sub_root == nullptr) {
            return;
        }
        print_spaces(spaces);
        cout << sub_root->data << '\n';
        print_hierarchy(sub_root->left, spaces + 2);
        print_hierarchy(sub_root->right, spaces + 2);
    }
    unsigned height(Node<T>* sub_root) const {
        if (sub_root == nullptr) {
            return 0;
        }
        unsigned left = height(sub_root->left);
        unsigned right = height(sub_root->right);
        return 1 + (left > right ? left : right);
    }
};