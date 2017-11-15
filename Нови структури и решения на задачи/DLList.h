#pragma once

template <typename T>
struct Node {
    Node<T>* previous;
    T data;
    Node<T>* next;
    Node(const T& _data) : previous(nullptr), data(_data), next(nullptr) {}
};

// Doubly-linked list
template <typename T>
class DLList {
    Node<T>* first;
    Node<T>* last;

public:
    class Iterator {
        Node<T>* crr;
    public:
        Iterator(Node<T>* node) {
            crr = node;
        }
        bool operator != (const Iterator& other) const {
            return crr != other.crr;
        }
        void operator++ () {
            crr = crr->next;
        }
        void operator-- () {
            crr = crr->previous;
        }
        int& operator* () {
            return crr->data;
        }
        int operator*() const {
            return crr->data;
        }
    };

    Iterator begin() const {
        return Iterator(first);
    }
    Iterator last_iter() const {
        return Iterator(last);
    }
    Iterator end() const {
        return Iterator(nullptr);
    }

    DLList() : first(nullptr), last(nullptr) {}
    
    DLList(const DLList& other) : first(nullptr), last(nullptr) {
        Node<T>* node_in_other = other.first;
        while (node_in_other != nullptr) {
            push_back(node_in_other->data); 
            node_in_other = node_in_other->next;
        }
    }

    // Not written in class but the idea is familiar
    DLList& operator=(const DLList& other) {
        if (this != &other) {
            delete_all_nodes();
            Node<T>* node_in_other = other.first;
            while (node_in_other != nullptr) {
                push_back(node_in_other->data);
                node_in_other = node_in_other->next;
            }
        }
        return *this;
    }

    ~DLList() {
        delete_all_nodes();
    }

    void push_back(const T& x) {
        if (last == nullptr) {           // <==> list is empty
            first = new Node<T>(x);
            last = first;
            return;
        }
        last->next = new Node<T>(x);
        last->next->previous = last;
        last = last->next;
    }
    
    // Adds x after y. We assume y is in the list
    void add_after(const T& x, const T& y) {
        Node<T>* crr = first;
        while (crr->data != y) {
            crr = crr->next;
        }
        if (crr->next == nullptr) {       // <==> the end is reached
            push_back(x);
            return;
        }

        // Let's imagine we insert 100 after 21 in the list: 2, 7, 21, 22 
        // crr points to 21, crr->next points to 22

        Node<T>* the_new = new Node<T>(x);      // 100 is created
        crr->next->previous = the_new;          // 100 <-- 22 link is made
        the_new->next = crr->next;              // 100 --> 22 link is made

        crr->next = the_new;                    // 21 --> 100 link is made
        the_new->previous = crr;                // 21 <-- 100 link is made
    }

private:
    // Not written in class but not too complex
    void delete_all_nodes() {
        if (first == nullptr) {         // <==> list is empty
            return;
        }
        Node<T>* crr = first;
        while (crr->next != nullptr) {  // ->next, because otherwise...
            crr = crr->next;
            delete crr->previous;       // ...crr can be nullptr here!
        }
        delete crr;
    }
};