#pragma once

template <typename T>
struct Node {
    T data;
    Node<T>* next;
    Node(const T& _data) : data(_data), next(nullptr) {}
};

template <typename T>
class Queue {
    Node<T>* first;
    Node<T>* last;
public:
    Queue() : first(nullptr), last(nullptr) {}

    // Not written in class but trivial
    ~Queue() {
        while (first != nullptr) {
            Node<T>* popped = first;
            first = first->next;
            delete popped;
        }
    }

    void push(const T& x) {
        if (last == nullptr) {
            first = new Node<T>(x);
            last = first;
            return;
        }
        last->next = new Node<T>(x);
        last = last->next;
    }
    void pop() {
        if (first == nullptr) {
            return;
        }
        Node<T>* popped = first;
        first = first->next;
        delete popped;
        if (first == nullptr) {
            last = nullptr;
        }
    }
    bool empty() const {
        return first == nullptr;
    }
    T get_first() const {
        return first->data;
    }
};